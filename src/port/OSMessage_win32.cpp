
#include "dolphin/os/OSMessage.h"

#include <condition_variable>
#include <mutex>
#include <unordered_map>

// ==========================================================================
// Message Queue (thread-safe implementation)
// ==========================================================================

// Side-table for native synchronization per OSMessageQueue
struct PCMessageQueueData {
    std::mutex mtx;
    std::condition_variable cvSend;    // Notified when space becomes available
    std::condition_variable cvReceive; // Notified when a message arrives
};

static std::mutex& GetMsgQueueMapMutex() {
    static std::mutex mtx;
    return mtx;
}

static std::unordered_map<OSMessageQueue*, std::unique_ptr<PCMessageQueueData>>& GetMsgQueueMap() {
    static std::unordered_map<OSMessageQueue*, std::unique_ptr<PCMessageQueueData>> map;
    return map;
}

static PCMessageQueueData& GetMsgQueueData(OSMessageQueue* mq) {
    std::lock_guard<std::mutex> lock(GetMsgQueueMapMutex());
    auto& map = GetMsgQueueMap();
    auto it = map.find(mq);
    if (it == map.end()) {
        auto result = map.emplace(mq, std::make_unique<PCMessageQueueData>());
        return *result.first->second;
    }
    return *it->second;
}

static void ClearMsgQueueMap() {
    std::lock_guard<std::mutex> lock(GetMsgQueueMapMutex());
    auto& map = GetMsgQueueMap();
    for (auto& [_, value] : map) {
        value->cvReceive.notify_all();
        value->cvSend.notify_all();
    }
    map.clear();
}

// ============================================================================
// C API functions
// ============================================================================

void OSInitMessageQueue(OSMessageQueue* mq, OSMessage* messages, s32 message_count) {
    if (!mq) {
        return;
    }

    OSInitThreadQueue(&mq->sending_queue);
    OSInitThreadQueue(&mq->receiving_queue);
    mq->message_array = messages;
    mq->num_messages = message_count;
    mq->first_index = 0;
    mq->num_used = 0;
    GetMsgQueueData(mq); // Ensure side-table entry exists
}

BOOL OSSendMessage(OSMessageQueue* mq, OSMessage message, s32 flags) {
    if (!mq) {
        return false;
    }

    PCMessageQueueData& data = GetMsgQueueData(mq);
    std::unique_lock<std::mutex> lock(data.mtx);

    while (mq->num_messages <= mq->num_used) {
        if ((flags & OS_MESSAGE_BLOCK) == 0) {
            return false;
        }
        data.cvSend.wait(lock, [mq] { return mq->num_used < mq->num_messages; });
    }
    int index = (mq->first_index + mq->num_used) % mq->num_messages;
    mq->message_array[index] = message;
    mq->num_used++;

    data.cvReceive.notify_one();
    return true;
}

BOOL OSReceiveMessage(OSMessageQueue* mq, OSMessage* message, s32 flags) {
    if (!mq) {
        return false;
    }

    PCMessageQueueData& data = GetMsgQueueData(mq);
    std::unique_lock<std::mutex> lock(data.mtx);
    while (mq->num_used == 0) {
        if ((flags & OS_MESSAGE_BLOCK) == 0) {
            return false;
        }
        data.cvReceive.wait(lock, [mq] { return mq->num_used > 0; });
    }
    if (message) {
        *message = mq->message_array[mq->first_index];
    }
    mq->first_index = (mq->first_index + 1) % mq->num_messages;
    mq->num_used--;

    data.cvSend.notify_one();
    return true;
}