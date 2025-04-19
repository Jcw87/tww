cmake_minimum_required(VERSION 3.20.0)
project(tww VERSION 0.1.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
    add_compile_definitions(
        _CRT_SECURE_NO_WARNINGS=1 D_SCL_SECURE_NO_WARNINGS=1
        _SCL_SECURE_NO_DEPRECATE=1 _CRT_NONSTDC_NO_WARNINGS=1
        _USE_MATH_DEFINES=1
    )
    add_compile_options(
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4018>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4800>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4005>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4311>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4068>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4267>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4244>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4200>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4305>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4067>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4146>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4309>
          $<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/wd4805>
    )
endif()

add_library(dolphin_sdk STATIC
    src/dolphin/os/OSAlloc.c
    src/dolphin/os/OSArena.c
    src/dolphin/os/OSFont.c
    src/dolphin/mtx/mtx.c
    src/dolphin/mtx/mtxvec.c
    src/dolphin/mtx/mtx44.c
    src/dolphin/mtx/vec.c
    src/dolphin/mtx/quat.c
)
target_include_directories(dolphin_sdk PUBLIC include src assets/GZLE01 build/GZLE01/include)
target_compile_definitions(dolphin_sdk PUBLIC
    TARGET_PC
    VERSION=2
)
set_property(TARGET dolphin_sdk PROPERTY CXX_STANDARD 23)

add_executable(tww
    src/m_Do/m_Do_main.cpp
    src/m_Do/m_Do_printf.cpp
    src/m_Do/m_Do_audio.cpp
    src/m_Do/m_Do_controller_pad.cpp
    src/m_Do/m_Do_graphic.cpp
    src/m_Do/m_Do_machine.cpp
    src/m_Do/m_Do_mtx.cpp
    src/m_Do/m_Do_ext.cpp
    src/m_Do/m_Do_lib.cpp
    src/m_Do/m_Do_hostIO.cpp
    src/m_Do/m_Do_Reset.cpp
    src/m_Do/m_Do_dvd_thread.cpp
    src/m_Do/m_Do_DVDError.cpp
    src/m_Do/m_Do_MemCard.cpp
    src/m_Do/m_Do_MemCardRWmng.cpp
    src/m_Do/m_Do_gba_com.cpp
    src/m_Do/m_Do_machine_exception.cpp
    src/c/c_damagereaction.cpp
    src/c/c_dylink.cpp
    src/f_ap/f_ap_game.cpp
    src/f_op/f_op_actor.cpp
    src/f_op/f_op_actor_iter.cpp
    src/f_op/f_op_actor_tag.cpp
    src/f_op/f_op_actor_mng.cpp
    src/f_op/f_op_camera.cpp
    src/f_op/f_op_camera_mng.cpp
    src/f_op/f_op_overlap.cpp
    src/f_op/f_op_overlap_mng.cpp
    src/f_op/f_op_overlap_req.cpp
    src/f_op/f_op_scene.cpp
    src/f_op/f_op_scene_iter.cpp
    src/f_op/f_op_scene_mng.cpp
    src/f_op/f_op_scene_req.cpp
    src/f_op/f_op_scene_tag.cpp
    src/f_op/f_op_view.cpp
    src/f_op/f_op_kankyo.cpp
    src/f_op/f_op_msg.cpp
    src/f_op/f_op_kankyo_mng.cpp
    src/f_op/f_op_msg_mng.cpp
    src/f_op/f_op_draw_iter.cpp
    src/f_op/f_op_draw_tag.cpp
    src/f_op/f_op_scene_pause.cpp
    src/f_pc/f_pc_base.cpp
    src/f_pc/f_pc_create_iter.cpp
    src/f_pc/f_pc_create_req.cpp
    src/f_pc/f_pc_create_tag.cpp
    src/f_pc/f_pc_creator.cpp
    src/f_pc/f_pc_delete_tag.cpp
    src/f_pc/f_pc_deletor.cpp
    src/f_pc/f_pc_draw_priority.cpp
    src/f_pc/f_pc_executor.cpp
    src/f_pc/f_pc_layer.cpp
    src/f_pc/f_pc_leaf.cpp
    src/f_pc/f_pc_layer_iter.cpp
    src/f_pc/f_pc_layer_tag.cpp
    src/f_pc/f_pc_line.cpp
    src/f_pc/f_pc_load.cpp
    src/f_pc/f_pc_manager.cpp
    src/f_pc/f_pc_method.cpp
    src/f_pc/f_pc_node.cpp
    src/f_pc/f_pc_node_req.cpp
    src/f_pc/f_pc_priority.cpp
    src/f_pc/f_pc_profile.cpp
    src/f_pc/f_pc_searcher.cpp
    src/f_pc/f_pc_line_tag.cpp
    src/f_pc/f_pc_line_iter.cpp
    src/f_pc/f_pc_method_iter.cpp
    src/f_pc/f_pc_method_tag.cpp
    src/f_pc/f_pc_pause.cpp
    src/f_pc/f_pc_draw.cpp
    src/f_pc/f_pc_fstcreate_req.cpp
    src/f_pc/f_pc_stdcreate_req.cpp
    src/d/d_stage.cpp
    src/d/d_map.cpp
    src/d/d_com_inf_game.cpp
    src/d/d_com_lib_game.cpp
    src/d/d_com_static.cpp
    src/d/d_lib.cpp
    src/d/d_save.cpp
    src/d/d_save_init.cpp
    src/d/d_shop.cpp
    src/d/d_jnt_hit.cpp
    src/d/d_chain.cpp
    src/d/d_cloth_packet.cpp
    src/d/d_a_obj.cpp
    src/d/d_a_obj_tribox_static.cpp
    src/d/d_a_ship_static.cpp
    src/d/d_a_boko_static.cpp
    src/d/d_a_bomb_static.cpp
    src/d/d_a_branch_static.cpp
    src/d/d_a_mgameboard_static.cpp
    src/d/d_a_itembase_static.cpp
    src/d/d_a_item_static.cpp
    src/d/d_a_shop_item_static.cpp
    src/d/d_a_race_item_static.cpp
    src/d/d_a_leaflift_static.cpp
    src/d/d_demo.cpp
    src/d/d_door.cpp
    src/d/d_resorce.cpp
    src/d/d_material.cpp
    src/d/d_event.cpp
    src/d/d_event_data.cpp
    src/d/d_event_manager.cpp
    src/d/d_magma.cpp
    src/d/d_boss_magma.cpp
    src/d/d_grass.cpp
    src/d/d_tree.cpp
    src/d/d_particle.cpp
    src/d/d_particle_name.cpp
    src/d/d_path.cpp
    src/d/d_drawlist.cpp
    src/d/d_kankyo_data.cpp
    src/d/d_kankyo_wether.cpp
    src/d/d_kankyo_rain.cpp
    src/d/d_kankyo_demo.cpp
    src/d/d_detect.cpp
    src/d/d_vibration.cpp
    src/d/d_vib_pattern.cpp
    src/d/d_attention.cpp
    src/d/d_att_dist.cpp
    src/d/d_bg_s.cpp
    src/d/d_bg_s_acch.cpp
    src/d/d_bg_s_func.cpp
    src/d/d_bg_s_lin_chk.cpp
    src/d/d_bg_s_movebg_actor.cpp
    src/d/d_bg_s_spl_grp_chk.cpp
    src/d/d_bg_s_wtr_chk.cpp
    src/d/d_bg_w.cpp
    src/d/d_bg_w_deform.cpp
    src/d/d_bg_w_hf.cpp
    src/d/d_bg_w_sv.cpp
    src/d/d_cc_d.cpp
    src/d/d_cc_mass_s.cpp
    src/d/d_cc_s.cpp
    src/d/d_cc_uty.cpp
    src/d/d_cam_param.cpp
    src/d/d_cam_type.cpp
    src/d/d_cam_style.cpp
    src/d/d_cam_type2.cpp
    src/d/d_ev_camera.cpp
    src/d/d_wood.cpp
    src/d/d_flower.cpp
    src/d/d_item_data.cpp
    src/d/d_seafightgame.cpp
    src/d/d_spline_path.cpp
    src/d/d_s_actor_data_mng.cpp
    src/d/d_item.cpp
    src/d/d_2dnumber.cpp
    src/d/d_a_npc_cb1_static.cpp
    src/d/d_a_npc_mk_static.cpp
    src/d/d_salvage.cpp
    src/d/d_snap.cpp
    src/d/d_point_wind.cpp
    src/d/actor/d_a_agb.cpp
    src/d/actor/d_a_arrow.cpp
    src/d/actor/d_a_bg.cpp
    src/d/actor/d_a_bomb.cpp
    src/d/actor/d_a_bomb2.cpp
    src/d/actor/d_a_boomerang.cpp
    src/d/actor/d_a_dai_item.cpp
    src/d/actor/d_a_demo00.cpp
    src/d/actor/d_a_disappear.cpp
    src/d/actor/d_a_esa.cpp
    src/d/actor/d_a_grid.cpp
    src/d/actor/d_a_himo2.cpp
    src/d/actor/d_a_hookshot.cpp
    src/d/actor/d_a_ib.cpp
    src/d/actor/d_a_item.cpp
    src/d/actor/d_a_itembase.cpp
    src/d/actor/d_a_nh.cpp
    src/d/actor/d_a_npc_fa1.cpp
    src/d/actor/d_a_obj_search.cpp
    src/d/actor/d_a_player.cpp
    src/d/actor/d_a_player_main.cpp
    src/d/actor/d_a_player_npc.cpp
    src/d/actor/d_a_sea.cpp
    src/d/actor/d_a_spc_item01.cpp
    src/d/actor/d_a_vrbox.cpp
    src/d/actor/d_a_vrbox2.cpp
    src/d/d_auction_screen.cpp
    src/d/d_place_name.cpp
    src/d/d_camera.cpp
    src/d/d_envse.cpp
    src/d/d_file_error.cpp
    src/d/d_file_select.cpp
    src/d/d_gameover.cpp
    src/d/d_kankyo.cpp
    src/d/d_kyeff.cpp
    src/d/d_kyeff2.cpp
    src/d/d_ky_thunder.cpp
    src/d/d_letter.cpp
    src/d/d_level_se.cpp
    src/d/d_menu_cloth.cpp
    src/d/d_menu_collect.cpp
    src/d/d_menu_dmap.cpp
    src/d/d_menu_fmap.cpp
    src/d/d_menu_fmap2.cpp
    src/d/d_menu_item.cpp
    src/d/d_menu_option.cpp
    src/d/d_menu_save.cpp
    src/d/d_menu_window.cpp
    src/d/d_mesg.cpp
    src/d/d_message.cpp
    src/d/d_message_paper.cpp
    src/d/d_meter.cpp
    src/d/d_minigame_starter.cpp
    src/d/d_minigame_terminater.cpp
    src/d/d_msg.cpp
    src/d/d_name.cpp
    src/d/d_npc.cpp
    src/d/d_operate_wind.cpp
    src/d/d_metronome.cpp
    src/d/d_ovlp_fade.cpp
    src/d/d_ovlp_fade2.cpp
    src/d/d_ovlp_fade3.cpp
    src/d/d_ovlp_fade4.cpp
    src/d/d_picture_box.cpp
    src/d/d_s_logo.cpp
    src/d/d_s_menu.cpp
    src/d/d_s_name.cpp
    src/d/d_s_open.cpp
    src/d/d_s_open_sub.cpp
    src/d/d_s_play.cpp
    src/d/d_s_room.cpp
    src/d/d_s_title.cpp
    src/d/d_scope.cpp
    src/d/d_throwstone.cpp
    src/d/d_timer.cpp
    src/d/d_water_mark.cpp
    src/d/d_wind_arrow.cpp
    src/d/d_wpillar.cpp
    src/d/d_wpot_water.cpp
    src/DynamicLink.cpp
)
target_link_libraries(tww
    SComponent
    SStandard
    JFramework
    J3DU
    JPALoader
    JPABase
    JPADraw
    JStage
    JStudio
    JStudio_JStage
    JStudio_JAudio
    JStudio_JParticle
    JStudio_JMessage
    JStudioToolLibrary
    JAudio
    JMessage
    JAZelAudio
    gf
    JKernel
    JSupport
    JGadget
    JUtility
    J2DGraph
    JRenderer
    J3DGraphBase
    J3DGraphAnimator
    J3DGraphLoader
    JMath
    tww_rel
    dolphin_sdk
)
target_precompile_headers(tww PRIVATE "include/d/dolzel.h")

if (MSVC)
    target_link_options(tww PRIVATE
        /LARGEADDRESSAWARE
    )
endif()

add_library(SComponent STATIC
    src/SSystem/SComponent/c_malloc.cpp
    src/SSystem/SComponent/c_API.cpp
    src/SSystem/SComponent/c_API_graphic.cpp
    src/SSystem/SComponent/c_cc_d.cpp
    src/SSystem/SComponent/c_cc_s.cpp
    src/SSystem/SComponent/c_counter.cpp
    src/SSystem/SComponent/c_list.cpp
    src/SSystem/SComponent/c_list_iter.cpp
    src/SSystem/SComponent/c_node.cpp
    src/SSystem/SComponent/c_node_iter.cpp
    src/SSystem/SComponent/c_tree.cpp
    src/SSystem/SComponent/c_tree_iter.cpp
    src/SSystem/SComponent/c_phase.cpp
    src/SSystem/SComponent/c_request.cpp
    src/SSystem/SComponent/c_tag.cpp
    src/SSystem/SComponent/c_tag_iter.cpp
    src/SSystem/SComponent/c_xyz.cpp
    src/SSystem/SComponent/c_sxyz.cpp
    src/SSystem/SComponent/c_math.cpp
    src/SSystem/SComponent/c_bg_s.cpp
    src/SSystem/SComponent/c_bg_s_chk.cpp
    src/SSystem/SComponent/c_bg_s_gnd_chk.cpp
    src/SSystem/SComponent/c_bg_s_lin_chk.cpp
    src/SSystem/SComponent/c_bg_w.cpp
    src/SSystem/SComponent/c_m2d.cpp
    src/SSystem/SComponent/c_m2d_g_box.cpp
    src/SSystem/SComponent/c_m3d.cpp
    src/SSystem/SComponent/c_m3d_g_aab.cpp
    src/SSystem/SComponent/c_m3d_g_cyl.cpp
    src/SSystem/SComponent/c_m3d_g_pla.cpp
    src/SSystem/SComponent/c_m3d_g_sph.cpp
    src/SSystem/SComponent/c_m3d_g_tri.cpp
    src/SSystem/SComponent/c_lib.cpp
    src/SSystem/SComponent/c_angle.cpp
    src/SSystem/SComponent/c_data_tbl.cpp
)
target_link_libraries(SComponent dolphin_sdk)

add_library(SStandard STATIC
    src/SSystem/SStandard/s_basic.cpp
)
target_link_libraries(SStandard dolphin_sdk)

add_library(JFramework STATIC
    src/JSystem/JFramework/JFWDisplay.cpp
    src/JSystem/JFramework/JFWSystem.cpp
)
target_link_libraries(JFramework dolphin_sdk)
target_precompile_headers(JFramework PRIVATE "include/JSystem/JSystem.h")

add_library(J3DU STATIC
    src/JSystem/J3DU/J3DUClipper.cpp
    src/JSystem/J3DU/J3DUMotion.cpp
    src/JSystem/J3DU/J3DUDL.cpp
)
target_link_libraries(J3DU dolphin_sdk)
target_precompile_headers(J3DU PRIVATE "include/JSystem/JSystem.h")

add_library(JPALoader STATIC
    src/JSystem/JParticle/JPABaseShape.cpp
    src/JSystem/JParticle/JPAExtraShape.cpp
    src/JSystem/JParticle/JPASweepShape.cpp
    src/JSystem/JParticle/JPAExTexShape.cpp
    src/JSystem/JParticle/JPADynamicsBlock.cpp
    src/JSystem/JParticle/JPAFieldBlock.cpp
    src/JSystem/JParticle/JPAKeyBlock.cpp
    src/JSystem/JParticle/JPATexture.cpp
    src/JSystem/JParticle/JPAResourceManager.cpp
    src/JSystem/JParticle/JPAEmitterLoader.cpp
)
target_link_libraries(JPALoader dolphin_sdk)
target_precompile_headers(JPALoader PRIVATE "include/JSystem/JSystem.h")

add_library(JPABase STATIC
    src/JSystem/JParticle/JPAMath.cpp
    src/JSystem/JParticle/JPAField.cpp
    src/JSystem/JParticle/JPAEmitter.cpp
    src/JSystem/JParticle/JPAParticle.cpp
    src/JSystem/JParticle/JPAEmitterManager.cpp
)
target_link_libraries(JPABase dolphin_sdk)
target_precompile_headers(JPABase PRIVATE "include/JSystem/JSystem.h")

add_library(JPADraw STATIC
    src/JSystem/JParticle/JPADrawVisitor.cpp
    src/JSystem/JParticle/JPADraw.cpp
    src/JSystem/JParticle/JPADrawSetupTev.cpp
)
target_link_libraries(JPADraw dolphin_sdk)
target_precompile_headers(JPADraw PRIVATE "include/JSystem/JSystem.h")

add_library(JStage STATIC
    src/JSystem/JStage/JSGActor.cpp
    src/JSystem/JStage/JSGAmbientLight.cpp
    src/JSystem/JStage/JSGCamera.cpp
    src/JSystem/JStage/JSGFog.cpp
    src/JSystem/JStage/JSGLight.cpp
    src/JSystem/JStage/JSGObject.cpp
    src/JSystem/JStage/JSGSystem.cpp
)
target_link_libraries(JStage dolphin_sdk)
target_precompile_headers(JStage PRIVATE "include/JSystem/JSystem.h")

add_library(JStudio STATIC
    src/JSystem/JStudio/JStudio/jstudio-control.cpp
    src/JSystem/JStudio/JStudio/jstudio-data.cpp
    src/JSystem/JStudio/JStudio/jstudio-math.cpp
    src/JSystem/JStudio/JStudio/jstudio-object.cpp
    src/JSystem/JStudio/JStudio/functionvalue.cpp
    src/JSystem/JStudio/JStudio/fvb.cpp
    src/JSystem/JStudio/JStudio/fvb-data.cpp
    src/JSystem/JStudio/JStudio/fvb-data-parse.cpp
    src/JSystem/JStudio/JStudio/object-id.cpp
    src/JSystem/JStudio/JStudio/stb.cpp
    src/JSystem/JStudio/JStudio/stb-data.cpp
    src/JSystem/JStudio/JStudio/stb-data-parse.cpp
)
target_link_libraries(JStudio dolphin_sdk)
target_precompile_headers(JStudio PRIVATE "include/JSystem/JSystem.h")

add_library(JStudio_JStage STATIC
    src/JSystem/JStudio/JStudio_JStage/control.cpp
    src/JSystem/JStudio/JStudio_JStage/object.cpp
    src/JSystem/JStudio/JStudio_JStage/object-actor.cpp
    src/JSystem/JStudio/JStudio_JStage/object-ambientlight.cpp
    src/JSystem/JStudio/JStudio_JStage/object-camera.cpp
    src/JSystem/JStudio/JStudio_JStage/object-fog.cpp
    src/JSystem/JStudio/JStudio_JStage/object-light.cpp
)
target_link_libraries(JStudio_JStage dolphin_sdk)
target_precompile_headers(JStudio_JStage PRIVATE "include/JSystem/JSystem.h")

add_library(JStudio_JAudio STATIC
    src/JSystem/JStudio/JStudio_JAudio/control.cpp
    src/JSystem/JStudio/JStudio_JAudio/object-sound.cpp
)
target_link_libraries(JStudio_JAudio dolphin_sdk)
target_precompile_headers(JStudio_JAudio PRIVATE "include/JSystem/JSystem.h")

add_library(JStudio_JParticle STATIC
    src/JSystem/JStudio/JStudio_JParticle/control.cpp
    src/JSystem/JStudio/JStudio_JParticle/object-particle.cpp
)
target_link_libraries(JStudio_JParticle dolphin_sdk)
target_precompile_headers(JStudio_JParticle PRIVATE "include/JSystem/JSystem.h")

add_library(JStudio_JMessage STATIC
    src/JSystem/JStudio/JStudio_JMessage/control.cpp
    src/JSystem/JStudio/JStudio_JMessage/object-message.cpp
)
target_link_libraries(JStudio_JMessage dolphin_sdk)
target_precompile_headers(JStudio_JMessage PRIVATE "include/JSystem/JSystem.h")

add_library(JStudioToolLibrary STATIC
    src/JSystem/JStudio/JStudioToolLibrary/console.cpp
)
target_link_libraries(JStudioToolLibrary dolphin_sdk)
target_precompile_headers(JStudioToolLibrary PRIVATE "include/JSystem/JSystem.h")

add_library(JAudio STATIC
    src/JSystem/JAudio/JASCalc.cpp
    src/JSystem/JAudio/JASAiCtrl.cpp
    src/JSystem/JAudio/JASDvdThread.cpp
    src/JSystem/JAudio/JASCallback.cpp
    src/JSystem/JAudio/JASRate.cpp
    src/JSystem/JAudio/JASHardStream.cpp
    src/JSystem/JAudio/JASHeapCtrl.cpp
    src/JSystem/JAudio/JASResArcLoader.cpp
    src/JSystem/JAudio/JASProbe.cpp
    src/JSystem/JAudio/JASKernelDebug.cpp
    src/JSystem/JAudio/JASCmdStack.cpp
    src/JSystem/JAudio/JASSystemHeap.cpp
    src/JSystem/JAudio/JASNoteMgr.cpp
    src/JSystem/JAudio/JASOuterParam.cpp
    src/JSystem/JAudio/JASPlayer_impl.cpp
    src/JSystem/JAudio/JASRegisterParam.cpp
    src/JSystem/JAudio/JASSeqCtrl.cpp
    src/JSystem/JAudio/JASSeqParser.cpp
    src/JSystem/JAudio/JASTrack.cpp
    src/JSystem/JAudio/JASTrackInterrupt.cpp
    src/JSystem/JAudio/JASTrackPort.cpp
    src/JSystem/JAudio/JASBank.cpp
    src/JSystem/JAudio/JASWaveBank.cpp
    src/JSystem/JAudio/JASBasicBank.cpp
    src/JSystem/JAudio/JASBasicInst.cpp
    src/JSystem/JAudio/JASDrumSet.cpp
    src/JSystem/JAudio/JASBasicWaveBank.cpp
    src/JSystem/JAudio/JASSimpleWaveBank.cpp
    src/JSystem/JAudio/JASInstEffect.cpp
    src/JSystem/JAudio/JASInstSense.cpp
    src/JSystem/JAudio/JASInstRand.cpp
    src/JSystem/JAudio/JASWSParser.cpp
    src/JSystem/JAudio/JASBNKParser.cpp
    src/JSystem/JAudio/JASWaveArcLoader.cpp
    src/JSystem/JAudio/JASWaveBankMgr.cpp
    src/JSystem/JAudio/JASBankMgr.cpp
    src/JSystem/JAudio/JASAudioThread.cpp
    src/JSystem/JAudio/JASDSPBuf.cpp
    src/JSystem/JAudio/JASDSPChannel.cpp
    src/JSystem/JAudio/JASDSPInterface.cpp
    src/JSystem/JAudio/JASDriverIF.cpp
    src/JSystem/JAudio/JASChGlobal.cpp
    src/JSystem/JAudio/JASChAllocQueue.cpp
    src/JSystem/JAudio/JASChannel.cpp
    src/JSystem/JAudio/JASChannelMgr.cpp
    src/JSystem/JAudio/JASOscillator.cpp
    src/JSystem/JAudio/JASDriverTables.cpp
    src/JSystem/JAudio/dspproc.c
    src/JSystem/JAudio/dsptask.c
    src/JSystem/JAudio/osdsp.c
    src/JSystem/JAudio/osdsp_task.c
    src/JSystem/JAudio/JAIAnimation.cpp
    src/JSystem/JAudio/JAIBasic.cpp
    src/JSystem/JAudio/JAIBankWave.cpp
    src/JSystem/JAudio/JAIConst.cpp
    src/JSystem/JAudio/JAIDummyObject.cpp
    src/JSystem/JAudio/JAIFx.cpp
    src/JSystem/JAudio/JAIGlobalParameter.cpp
    src/JSystem/JAudio/JAIInitData.cpp
    src/JSystem/JAudio/JAISeMgr.cpp
    src/JSystem/JAudio/JAISequenceHeap.cpp
    src/JSystem/JAudio/JAISequenceMgr.cpp
    src/JSystem/JAudio/JAISound.cpp
    src/JSystem/JAudio/JAISoundTable.cpp
    src/JSystem/JAudio/JAIStreamMgr.cpp
    src/JSystem/JAudio/JAISystemInterface.cpp
)
set_source_files_properties(
    src/JSystem/JAudio/dspproc.c
    src/JSystem/JAudio/dsptask.c
    src/JSystem/JAudio/osdsp.c
    src/JSystem/JAudio/osdsp_task.c
    PROPERTIES LANGUAGE CXX
)
target_link_libraries(JAudio dolphin_sdk)
target_precompile_headers(JAudio PRIVATE "include/JSystem/JSystem.h")

add_library(JMessage STATIC
    src/JSystem/JMessage/data.cpp
    src/JSystem/JMessage/control.cpp
    src/JSystem/JMessage/processor.cpp
    src/JSystem/JMessage/resource.cpp
)
target_link_libraries(JMessage dolphin_sdk)
target_precompile_headers(JMessage PRIVATE "include/JSystem/JSystem.h")

add_library(JAZelAudio STATIC
    src/JAZelAudio/JAIZelBasic.cpp
    src/JAZelAudio/JAIZelAnime.cpp
    src/JAZelAudio/JAIZelAtmos.cpp
    src/JAZelAudio/JAIZelInst.cpp
    src/JAZelAudio/JAIZelParam.cpp
    src/JAZelAudio/JAIZelCharVoiceTable.cpp
    src/JAZelAudio/JAIZelScene.cpp
    src/JAZelAudio/JAIZelSound.cpp
)
target_link_libraries(JAZelAudio dolphin_sdk)

add_library(gf STATIC
    src/dolphin/gf/GFGeometry.cpp
    src/dolphin/gf/GFLight.cpp
    src/dolphin/gf/GFPixel.cpp
    src/dolphin/gf/GFTev.cpp
    src/dolphin/gf/GFTransform.cpp
)
target_link_libraries(gf dolphin_sdk)

add_library(JKernel STATIC
    src/JSystem/JKernel/JKRHeap.cpp
    src/JSystem/JKernel/JKRStdHeap.cpp
    src/JSystem/JKernel/JKRExpHeap.cpp
    src/JSystem/JKernel/JKRSolidHeap.cpp
    src/JSystem/JKernel/JKRDisposer.cpp
    src/JSystem/JKernel/JKRThread.cpp
    src/JSystem/JKernel/JKRAram.cpp
    src/JSystem/JKernel/JKRAramHeap.cpp
    src/JSystem/JKernel/JKRAramBlock.cpp
    src/JSystem/JKernel/JKRAramPiece.cpp
    src/JSystem/JKernel/JKRAramStream.cpp
    src/JSystem/JKernel/JKRFileLoader.cpp
    src/JSystem/JKernel/JKRFileFinder.cpp
    src/JSystem/JKernel/JKRFileCache.cpp
    src/JSystem/JKernel/JKRArchivePub.cpp
    src/JSystem/JKernel/JKRArchivePri.cpp
    src/JSystem/JKernel/JKRMemArchive.cpp
    src/JSystem/JKernel/JKRAramArchive.cpp
    src/JSystem/JKernel/JKRDvdArchive.cpp
    src/JSystem/JKernel/JKRCompArchive.cpp
    src/JSystem/JKernel/JKRFile.cpp
    src/JSystem/JKernel/JKRDvdFile.cpp
    src/JSystem/JKernel/JKRDvdRipper.cpp
    src/JSystem/JKernel/JKRDvdAramRipper.cpp
    src/JSystem/JKernel/JKRDecomp.cpp
)
target_link_libraries(JKernel dolphin_sdk)
target_precompile_headers(JKernel PRIVATE "include/JSystem/JSystem.h")

add_library(JSupport STATIC
    src/JSystem/JSupport/JSUList.cpp
    src/JSystem/JSupport/JSUInputStream.cpp
    src/JSystem/JSupport/JSUMemoryStream.cpp
    src/JSystem/JSupport/JSUFileStream.cpp
)
target_link_libraries(JSupport dolphin_sdk)
target_precompile_headers(JSupport PRIVATE "include/JSystem/JSystem.h")

add_library(JGadget STATIC
    src/JSystem/JGadget/binary.cpp
    src/JSystem/JGadget/linklist.cpp
    src/JSystem/JGadget/std-vector.cpp
)
target_link_libraries(JGadget dolphin_sdk)
target_precompile_headers(JGadget PRIVATE "include/JSystem/JSystem.h")

add_library(JUtility STATIC
    src/JSystem/JUtility/JUTCacheFont.cpp
    src/JSystem/JUtility/JUTResource.cpp
    src/JSystem/JUtility/JUTTexture.cpp
    src/JSystem/JUtility/JUTPalette.cpp
    src/JSystem/JUtility/JUTNameTab.cpp
    src/JSystem/JUtility/JUTGraphFifo.cpp
    src/JSystem/JUtility/JUTFont.cpp
    src/JSystem/JUtility/JUTResFont.cpp
    src/JSystem/JUtility/JUTDbPrint.cpp
    src/JSystem/JUtility/JUTGamePad.cpp
    src/JSystem/JUtility/JUTException.cpp
    src/JSystem/JUtility/JUTDirectPrint.cpp
    src/JSystem/JUtility/JUTAssert.cpp
    src/JSystem/JUtility/JUTVideo.cpp
    src/JSystem/JUtility/JUTXfb.cpp
    src/JSystem/JUtility/JUTFader.cpp
    src/JSystem/JUtility/JUTProcBar.cpp
    src/JSystem/JUtility/JUTConsole.cpp
    src/JSystem/JUtility/JUTDirectFile.cpp
    src/JSystem/JUtility/JUTGba.cpp
    src/JSystem/JUtility/JUTFontData_Ascfont_fix12.cpp
)
target_link_libraries(JUtility dolphin_sdk)
target_precompile_headers(JUtility PRIVATE "include/JSystem/JSystem.h")

add_library(J2DGraph STATIC
    src/JSystem/J2DGraph/J2DGrafContext.cpp
    src/JSystem/J2DGraph/J2DOrthoGraph.cpp
    src/JSystem/J2DGraph/J2DPrint.cpp
    src/JSystem/J2DGraph/J2DPane.cpp
    src/JSystem/J2DGraph/J2DScreen.cpp
    src/JSystem/J2DGraph/J2DWindow.cpp
    src/JSystem/J2DGraph/J2DPicture.cpp
    src/JSystem/J2DGraph/J2DTextBox.cpp
)
target_link_libraries(J2DGraph dolphin_sdk)
target_precompile_headers(J2DGraph PRIVATE "include/JSystem/JSystem.h")

add_library(JRenderer STATIC
    src/JSystem/JRenderer/JRenderer.cpp
)
target_link_libraries(JRenderer dolphin_sdk)
target_precompile_headers(JRenderer PRIVATE "include/JSystem/JSystem.h")

add_library(J3DGraphBase STATIC
    src/JSystem/J3DGraphBase/J3DGD.cpp
    src/JSystem/J3DGraphBase/J3DSys.cpp
    src/JSystem/J3DGraphBase/J3DVertex.cpp
    src/JSystem/J3DGraphBase/J3DTransform.cpp
    src/JSystem/J3DGraphBase/J3DPacket.cpp
    src/JSystem/J3DGraphBase/J3DShapeMtx.cpp
    src/JSystem/J3DGraphBase/J3DShape.cpp
    src/JSystem/J3DGraphBase/J3DMaterial.cpp
    src/JSystem/J3DGraphBase/J3DMatBlock.cpp
    src/JSystem/J3DGraphBase/J3DTevs.cpp
    src/JSystem/J3DGraphBase/J3DDrawBuffer.cpp
)
target_link_libraries(J3DGraphBase dolphin_sdk)
target_precompile_headers(J3DGraphBase PRIVATE "include/JSystem/JSystem.h")

add_library(J3DGraphAnimator STATIC
    src/JSystem/J3DGraphAnimator/J3DModelData.cpp
    src/JSystem/J3DGraphAnimator/J3DModel.cpp
    src/JSystem/J3DGraphAnimator/J3DAnimation.cpp
    src/JSystem/J3DGraphAnimator/J3DMaterialAnm.cpp
    src/JSystem/J3DGraphAnimator/J3DVisibility.cpp
    src/JSystem/J3DGraphAnimator/J3DCluster.cpp
    src/JSystem/J3DGraphAnimator/J3DJoint.cpp
    src/JSystem/J3DGraphAnimator/J3DNode.cpp
    src/JSystem/J3DGraphAnimator/J3DMaterialAttach.cpp
)
target_link_libraries(J3DGraphAnimator dolphin_sdk)
target_precompile_headers(J3DGraphAnimator PRIVATE "include/JSystem/JSystem.h")

add_library(J3DGraphLoader STATIC
    src/JSystem/J3DGraphLoader/J3DMaterialFactory.cpp
    src/JSystem/J3DGraphLoader/J3DMaterialFactory_v21.cpp
    src/JSystem/J3DGraphLoader/J3DClusterLoader.cpp
    src/JSystem/J3DGraphLoader/J3DModelLoader.cpp
    src/JSystem/J3DGraphLoader/J3DModelLoaderCalcSize.cpp
    src/JSystem/J3DGraphLoader/J3DJointFactory.cpp
    src/JSystem/J3DGraphLoader/J3DShapeFactory.cpp
    src/JSystem/J3DGraphLoader/J3DAnmLoader.cpp
)
target_link_libraries(J3DGraphLoader dolphin_sdk)
target_precompile_headers(J3DGraphLoader PRIVATE "include/JSystem/JSystem.h")

add_library(JMath STATIC
    src/JSystem/JMath/JMath.cpp
    src/JSystem/JMath/random.cpp
)
target_link_libraries(JMath dolphin_sdk)
target_precompile_headers(JMath PRIVATE "include/JSystem/JSystem.h")

add_library(tww_rel STATIC
    src/f_pc/f_pc_profile_lst.cpp
    src/d/actor/d_a_agbsw0.cpp
    src/d/actor/d_a_andsw0.cpp
    src/d/actor/d_a_andsw2.cpp
    src/d/actor/d_a_att.cpp
    src/d/actor/d_a_bflower.cpp
    src/d/actor/d_a_bita.cpp
    src/d/actor/d_a_branch.cpp
    src/d/actor/d_a_bridge.cpp
    src/d/actor/d_a_coming2.cpp
    src/d/actor/d_a_coming3.cpp
    src/d/actor/d_a_demo_dk.cpp
    src/d/actor/d_a_demo_kmm.cpp
    src/d/actor/d_a_door10.cpp
    src/d/actor/d_a_dr.cpp
    src/d/actor/d_a_dr2.cpp
    src/d/actor/d_a_ep.cpp
    src/d/actor/d_a_floor.cpp
    src/d/actor/d_a_grass.cpp
    src/d/actor/d_a_hitobj.cpp
    src/d/actor/d_a_hot_floor.cpp
    src/d/actor/d_a_ikari.cpp
    src/d/actor/d_a_jbo.cpp
    src/d/actor/d_a_kaji.cpp
    src/d/actor/d_a_kanban.cpp
    src/d/actor/d_a_ki.cpp
    src/d/actor/d_a_knob00.cpp
    src/d/actor/d_a_kui.cpp
    src/d/actor/d_a_kytag00.cpp
    src/d/actor/d_a_kytag01.cpp
    src/d/actor/d_a_kytag02.cpp
    src/d/actor/d_a_kytag03.cpp
    src/d/actor/d_a_kytag04.cpp
    src/d/actor/d_a_kytag05.cpp
    src/d/actor/d_a_kytag06.cpp
    src/d/actor/d_a_kytag07.cpp
    src/d/actor/d_a_lamp.cpp
    src/d/actor/d_a_lod_bg.cpp
    src/d/actor/d_a_lwood.cpp
    src/d/actor/d_a_magma.cpp
    src/d/actor/d_a_majuu_flag.cpp
    src/d/actor/d_a_mdoor.cpp
    src/d/actor/d_a_msw.cpp
    src/d/actor/d_a_mtoge.cpp
    src/d/actor/d_a_obj_AjavW.cpp
    src/d/actor/d_a_obj_Ygush00.cpp
    src/d/actor/d_a_obj_akabe.cpp
    src/d/actor/d_a_obj_barrel.cpp
    src/d/actor/d_a_obj_barrel2.cpp
    src/d/actor/d_a_obj_bscurtain.cpp
    src/d/actor/d_a_obj_cafelmp.cpp
    src/d/actor/d_a_obj_coming.cpp
    src/d/actor/d_a_obj_demo_barrel.cpp
    src/d/actor/d_a_obj_doguu.cpp
    src/d/actor/d_a_obj_doguu_demo.cpp
    src/d/actor/d_a_obj_gryw00.cpp
    src/d/actor/d_a_obj_hfuck1.cpp
    src/d/actor/d_a_obj_hole.cpp
    src/d/actor/d_a_obj_ice.cpp
    src/d/actor/d_a_obj_ikada.cpp
    src/d/actor/d_a_obj_kanat.cpp
    src/d/actor/d_a_obj_leaves.cpp
    src/d/actor/d_a_obj_lpalm.cpp
    src/d/actor/d_a_obj_monument.cpp
    src/d/actor/d_a_obj_movebox.cpp
    src/d/actor/d_a_obj_mshokki.cpp
    src/d/actor/d_a_obj_ohatch.cpp
    src/d/actor/d_a_obj_otble.cpp
    src/d/actor/d_a_obj_pbco.cpp
    src/d/actor/d_a_obj_pirateship.cpp
    src/d/actor/d_a_obj_quake.cpp
    src/d/actor/d_a_obj_rcloud.cpp
    src/d/actor/d_a_obj_roten.cpp
    src/d/actor/d_a_obj_shelf.cpp
    src/d/actor/d_a_obj_shmrgrd.cpp
    src/d/actor/d_a_obj_swpush.cpp
    src/d/actor/d_a_obj_table.cpp
    src/d/actor/d_a_obj_tenmado.cpp
    src/d/actor/d_a_obj_tide.cpp
    src/d/actor/d_a_obj_timer.cpp
    src/d/actor/d_a_obj_toripost.cpp
    src/d/actor/d_a_obj_tousekiki.cpp
    src/d/actor/d_a_obj_warpt.cpp
    src/d/actor/d_a_obj_wood.cpp
    src/d/actor/d_a_pirate_flag.cpp
    src/d/actor/d_a_race_item.cpp
    src/d/actor/d_a_rd.cpp
    src/d/actor/d_a_rectangle.cpp
    src/d/actor/d_a_salvage.cpp
    src/d/actor/d_a_sbox.cpp
    src/d/actor/d_a_sk.cpp
    src/d/actor/d_a_sk2.cpp
    src/d/actor/d_a_spotbox.cpp
    src/d/actor/d_a_ssk.cpp
    src/d/actor/d_a_stone.cpp
    src/d/actor/d_a_stone2.cpp
    src/d/actor/d_a_swc00.cpp
    src/d/actor/d_a_swhit0.cpp
    src/d/actor/d_a_swtdoor.cpp
    src/d/actor/d_a_tag_attention.cpp
    src/d/actor/d_a_tag_ba1.cpp
    src/d/actor/d_a_tag_event.cpp
    src/d/actor/d_a_tag_evsw.cpp
    src/d/actor/d_a_tag_ghostship.cpp
    src/d/actor/d_a_tag_hint.cpp
    src/d/actor/d_a_tag_kb_item.cpp
    src/d/actor/d_a_tag_kk1.cpp
    src/d/actor/d_a_tag_light.cpp
    src/d/actor/d_a_tag_msg.cpp
    src/d/actor/d_a_tag_photo.cpp
    src/d/actor/d_a_tag_waterlevel.cpp
    src/d/actor/d_a_tama.cpp
    src/d/actor/d_a_tbox.cpp
    src/d/actor/d_a_tpota.cpp
    src/d/actor/d_a_tsubo.cpp
    src/d/actor/d_a_warpdm20.cpp
    src/d/actor/d_a_warphr.cpp
    src/d/actor/d_a_wbird.cpp
    src/d/actor/d_a_ykgr.cpp
    src/d/actor/d_a_alldie.cpp
    src/d/actor/d_a_am.cpp
    src/d/actor/d_a_am2.cpp
    src/d/actor/d_a_amiprop.cpp
    src/d/actor/d_a_arrow_iceeff.cpp
    src/d/actor/d_a_arrow_lighteff.cpp
    src/d/actor/d_a_beam.cpp
    src/d/actor/d_a_boko.cpp
    src/d/actor/d_a_canon.cpp
    src/d/actor/d_a_cc.cpp
    src/d/actor/d_a_dai.cpp
    src/d/actor/d_a_demo_item.cpp
    src/d/actor/d_a_door12.cpp
    src/d/actor/d_a_fallrock.cpp
    src/d/actor/d_a_ff.cpp
    src/d/actor/d_a_gy_ctrl.cpp
    src/d/actor/d_a_himo3.cpp
    src/d/actor/d_a_hmlif.cpp
    src/d/actor/d_a_hys.cpp
    src/d/actor/d_a_kamome.cpp
    src/d/actor/d_a_kamome2.cpp
    src/d/actor/d_a_kantera.cpp
    src/d/actor/d_a_kn.cpp
    src/d/actor/d_a_kokiie.cpp
    src/d/actor/d_a_ks.cpp
    src/d/actor/d_a_kt.cpp
    src/d/actor/d_a_mflft.cpp
    src/d/actor/d_a_npc_cb1.cpp
    src/d/actor/d_a_npc_md.cpp
    src/d/actor/d_a_npc_so.cpp
    src/d/actor/d_a_nzg.cpp
    src/d/actor/d_a_obj_aygr.cpp
    src/d/actor/d_a_obj_balancelift.cpp
    src/d/actor/d_a_obj_barrier.cpp
    src/d/actor/d_a_obj_bemos.cpp
    src/d/actor/d_a_obj_canon.cpp
    src/d/actor/d_a_obj_eff.cpp
    src/d/actor/d_a_obj_magmarock.cpp
    src/d/actor/d_a_obj_majyuu_door.cpp
    src/d/actor/d_a_obj_stair.cpp
    src/d/actor/d_a_obj_swflat.cpp
    src/d/actor/d_a_obj_swhammer.cpp
    src/d/actor/d_a_obj_swheavy.cpp
    src/d/actor/d_a_obj_swlight.cpp
    src/d/actor/d_a_oq.cpp
    src/d/actor/d_a_pedestal.cpp
    src/d/actor/d_a_saku.cpp
    src/d/actor/d_a_seatag.cpp
    src/d/actor/d_a_shand.cpp
    src/d/actor/d_a_ship.cpp
    src/d/actor/d_a_shop_item.cpp
    src/d/actor/d_a_sie_flag.cpp
    src/d/actor/d_a_sitem.cpp
    src/d/actor/d_a_ss.cpp
    src/d/actor/d_a_sss.cpp
    src/d/actor/d_a_syan.cpp
    src/d/actor/d_a_tag_md_cb.cpp
    src/d/actor/d_a_tag_mk.cpp
    src/d/actor/d_a_tag_so.cpp
    src/d/actor/d_a_tornado.cpp
    src/d/actor/d_a_warpf.cpp
    src/d/actor/d_a_wind_tag.cpp
    src/d/actor/d_a_acorn_leaf.cpp
    src/d/actor/d_a_atdoor.cpp
    src/d/actor/d_a_auction.cpp
    src/d/actor/d_a_bb.cpp
    src/d/actor/d_a_bdk.cpp
    src/d/actor/d_a_bdkobj.cpp
    src/d/actor/d_a_bgn.cpp
    src/d/actor/d_a_bgn2.cpp
    src/d/actor/d_a_bgn3.cpp
    src/d/actor/d_a_bigelf.cpp
    src/d/actor/d_a_bk.cpp
    src/d/actor/d_a_bl.cpp
    src/d/actor/d_a_bmd.cpp
    src/d/actor/d_a_bmdfoot.cpp
    src/d/actor/d_a_bmdhand.cpp
    src/d/actor/d_a_bo.cpp
    src/d/actor/d_a_boss_item.cpp
    src/d/actor/d_a_bpw.cpp
    src/d/actor/d_a_bst.cpp
    src/d/actor/d_a_btd.cpp
    src/d/actor/d_a_bwd.cpp
    src/d/actor/d_a_bwdg.cpp
    src/d/actor/d_a_bwds.cpp
    src/d/actor/d_a_daiocta.cpp
    src/d/actor/d_a_daiocta_eye.cpp
    src/d/actor/d_a_deku_item.cpp
    src/d/actor/d_a_dk.cpp
    src/d/actor/d_a_dummy.cpp
    src/d/actor/d_a_fallrock_tag.cpp
    src/d/actor/d_a_fan.cpp
    src/d/actor/d_a_fganon.cpp
    src/d/actor/d_a_fgmahou.cpp
    src/d/actor/d_a_fire.cpp
    src/d/actor/d_a_fm.cpp
    src/d/actor/d_a_gm.cpp
    src/d/actor/d_a_gnd.cpp
    src/d/actor/d_a_goal_flag.cpp
    src/d/actor/d_a_gy.cpp
    src/d/actor/d_a_icelift.cpp
    src/d/actor/d_a_kb.cpp
    src/d/actor/d_a_kddoor.cpp
    src/d/actor/d_a_kita.cpp
    src/d/actor/d_a_klft.cpp
    src/d/actor/d_a_kmon.cpp
    src/d/actor/d_a_komore.cpp
    src/d/actor/d_a_lbridge.cpp
    src/d/actor/d_a_leaflift.cpp
    src/d/actor/d_a_lstair.cpp
    src/d/actor/d_a_machine.cpp
    src/d/actor/d_a_mant.cpp
    src/d/actor/d_a_mbdoor.cpp
    src/d/actor/d_a_mgameboard.cpp
    src/d/actor/d_a_mmusic.cpp
    src/d/actor/d_a_mo2.cpp
    src/d/actor/d_a_mozo.cpp
    src/d/actor/d_a_mt.cpp
    src/d/actor/d_a_npc_ac1.cpp
    src/d/actor/d_a_npc_ah.cpp
    src/d/actor/d_a_npc_aj1.cpp
    src/d/actor/d_a_npc_auction.cpp
    src/d/actor/d_a_npc_ba1.cpp
    src/d/actor/d_a_npc_bj1.cpp
    src/d/actor/d_a_npc_bm1.cpp
    src/d/actor/d_a_npc_bmcon1.cpp
    src/d/actor/d_a_npc_bms1.cpp
    src/d/actor/d_a_npc_bmsw.cpp
    src/d/actor/d_a_npc_bs1.cpp
    src/d/actor/d_a_npc_btsw.cpp
    src/d/actor/d_a_npc_btsw2.cpp
    src/d/actor/d_a_npc_co1.cpp
    src/d/actor/d_a_npc_de1.cpp
    src/d/actor/d_a_npc_ds1.cpp
    src/d/actor/d_a_npc_gk1.cpp
    src/d/actor/d_a_npc_gp1.cpp
    src/d/actor/d_a_npc_hi1.cpp
    src/d/actor/d_a_npc_ho.cpp
    src/d/actor/d_a_npc_hr.cpp
    src/d/actor/d_a_npc_jb1.cpp
    src/d/actor/d_a_npc_ji1.cpp
    src/d/actor/d_a_npc_kamome.cpp
    src/d/actor/d_a_npc_kf1.cpp
    src/d/actor/d_a_npc_kg1.cpp
    src/d/actor/d_a_npc_kg2.cpp
    src/d/actor/d_a_npc_kk1.cpp
    src/d/actor/d_a_npc_km1.cpp
    src/d/actor/d_a_npc_ko1.cpp
    src/d/actor/d_a_npc_kp1.cpp
    src/d/actor/d_a_npc_ls1.cpp
    src/d/actor/d_a_npc_mk.cpp
    src/d/actor/d_a_npc_mn.cpp
    src/d/actor/d_a_npc_mt.cpp
    src/d/actor/d_a_npc_nz.cpp
    src/d/actor/d_a_npc_ob1.cpp
    src/d/actor/d_a_npc_os.cpp
    src/d/actor/d_a_npc_p1.cpp
    src/d/actor/d_a_npc_p2.cpp
    src/d/actor/d_a_npc_people.cpp
    src/d/actor/d_a_npc_pf1.cpp
    src/d/actor/d_a_npc_photo.cpp
    src/d/actor/d_a_npc_pm1.cpp
    src/d/actor/d_a_npc_roten.cpp
    src/d/actor/d_a_npc_rsh1.cpp
    src/d/actor/d_a_npc_sarace.cpp
    src/d/actor/d_a_npc_sv.cpp
    src/d/actor/d_a_npc_tc.cpp
    src/d/actor/d_a_npc_tt.cpp
    src/d/actor/d_a_npc_uk.cpp
    src/d/actor/d_a_npc_ym1.cpp
    src/d/actor/d_a_npc_yw1.cpp
    src/d/actor/d_a_npc_zk1.cpp
    src/d/actor/d_a_npc_zl1.cpp
    src/d/actor/d_a_nz.cpp
    src/d/actor/d_a_obj_Itnak.cpp
    src/d/actor/d_a_obj_Vds.cpp
    src/d/actor/d_a_obj_Vteng.cpp
    src/d/actor/d_a_obj_YLzou.cpp
    src/d/actor/d_a_obj_Yboil.cpp
    src/d/actor/d_a_obj_adnno.cpp
    src/d/actor/d_a_obj_ajav.cpp
    src/d/actor/d_a_obj_apzl.cpp
    src/d/actor/d_a_obj_ashut.cpp
    src/d/actor/d_a_obj_auzu.cpp
    src/d/actor/d_a_obj_buoyflag.cpp
    src/d/actor/d_a_obj_buoyrace.cpp
    src/d/actor/d_a_obj_correct.cpp
    src/d/actor/d_a_obj_dmgroom.cpp
    src/d/actor/d_a_obj_dragonhead.cpp
    src/d/actor/d_a_obj_drift.cpp
    src/d/actor/d_a_obj_eayogn.cpp
    src/d/actor/d_a_obj_ebomzo.cpp
    src/d/actor/d_a_obj_ekskz.cpp
    src/d/actor/d_a_obj_eskban.cpp
    src/d/actor/d_a_obj_ferris.cpp
    src/d/actor/d_a_obj_figure.cpp
    src/d/actor/d_a_obj_firewall.cpp
    src/d/actor/d_a_obj_flame.cpp
    src/d/actor/d_a_obj_ftree.cpp
    src/d/actor/d_a_obj_ganonbed.cpp
    src/d/actor/d_a_obj_gaship.cpp
    src/d/actor/d_a_obj_gaship2.cpp
    src/d/actor/d_a_obj_gnnbtltaki.cpp
    src/d/actor/d_a_obj_gnndemotakie.cpp
    src/d/actor/d_a_obj_gnndemotakis.cpp
    src/d/actor/d_a_obj_gong.cpp
    src/d/actor/d_a_obj_gtaki.cpp
    src/d/actor/d_a_obj_hami2.cpp
    src/d/actor/d_a_obj_hami3.cpp
    src/d/actor/d_a_obj_hami4.cpp
    src/d/actor/d_a_obj_hat.cpp
    src/d/actor/d_a_obj_hbrf1.cpp
    src/d/actor/d_a_obj_hcbh.cpp
    src/d/actor/d_a_obj_hha.cpp
    src/d/actor/d_a_obj_hlift.cpp
    src/d/actor/d_a_obj_homen.cpp
    src/d/actor/d_a_obj_homensmoke.cpp
    src/d/actor/d_a_obj_hsehi1.cpp
    src/d/actor/d_a_obj_htetu1.cpp
    src/d/actor/d_a_obj_iceisland.cpp
    src/d/actor/d_a_obj_jump.cpp
    src/d/actor/d_a_obj_kanoke.cpp
    src/d/actor/d_a_obj_ladder.cpp
    src/d/actor/d_a_obj_light.cpp
    src/d/actor/d_a_obj_mkie.cpp
    src/d/actor/d_a_obj_mkiek.cpp
    src/d/actor/d_a_obj_mknjd.cpp
    src/d/actor/d_a_obj_mmrr.cpp
    src/d/actor/d_a_obj_msdan.cpp
    src/d/actor/d_a_obj_msdan2.cpp
    src/d/actor/d_a_obj_msdan_sub.cpp
    src/d/actor/d_a_obj_msdan_sub2.cpp
    src/d/actor/d_a_obj_mtest.cpp
    src/d/actor/d_a_obj_nest.cpp
    src/d/actor/d_a_obj_ojtree.cpp
    src/d/actor/d_a_obj_ospbox.cpp
    src/d/actor/d_a_obj_paper.cpp
    src/d/actor/d_a_obj_pbka.cpp
    src/d/actor/d_a_obj_pfall.cpp
    src/d/actor/d_a_obj_plant.cpp
    src/d/actor/d_a_obj_rflw.cpp
    src/d/actor/d_a_obj_rforce.cpp
    src/d/actor/d_a_obj_smplbg.cpp
    src/d/actor/d_a_obj_tapestry.cpp
    src/d/actor/d_a_obj_tntrap.cpp
    src/d/actor/d_a_obj_tower.cpp
    src/d/actor/d_a_obj_trap.cpp
    src/d/actor/d_a_obj_tribox.cpp
    src/d/actor/d_a_obj_try.cpp
    src/d/actor/d_a_obj_usovmc.cpp
    src/d/actor/d_a_obj_vfan.cpp
    src/d/actor/d_a_obj_vgnfd.cpp
    src/d/actor/d_a_obj_vmc.cpp
    src/d/actor/d_a_obj_vmsdz.cpp
    src/d/actor/d_a_obj_vmsms.cpp
    src/d/actor/d_a_obj_volcano.cpp
    src/d/actor/d_a_obj_vtil.cpp
    src/d/actor/d_a_obj_vyasi.cpp
    src/d/actor/d_a_obj_xfuta.cpp
    src/d/actor/d_a_obj_zouK.cpp
    src/d/actor/d_a_oship.cpp
    src/d/actor/d_a_ph.cpp
    src/d/actor/d_a_pt.cpp
    src/d/actor/d_a_pw.cpp
    src/d/actor/d_a_pz.cpp
    src/d/actor/d_a_sail.cpp
    src/d/actor/d_a_salvage_tbox.cpp
    src/d/actor/d_a_scene_change.cpp
    src/d/actor/d_a_shutter.cpp
    src/d/actor/d_a_shutter2.cpp
    src/d/actor/d_a_st.cpp
    src/d/actor/d_a_steam_tag.cpp
    src/d/actor/d_a_swattack.cpp
    src/d/actor/d_a_switem.cpp
    src/d/actor/d_a_swpropeller.cpp
    src/d/actor/d_a_swtact.cpp
    src/d/actor/d_a_tag_etc.cpp
    src/d/actor/d_a_tag_island.cpp
    src/d/actor/d_a_tag_kf1.cpp
    src/d/actor/d_a_tag_ret.cpp
    src/d/actor/d_a_tag_volcano.cpp
    src/d/actor/d_a_title.cpp
    src/d/actor/d_a_tn.cpp
    src/d/actor/d_a_toge.cpp
    src/d/actor/d_a_tori_flag.cpp
    src/d/actor/d_a_wall.cpp
    src/d/actor/d_a_warpfout.cpp
    src/d/actor/d_a_warpgn.cpp
    src/d/actor/d_a_warpls.cpp
    src/d/actor/d_a_warpmj.cpp
    src/d/actor/d_a_waterfall.cpp
    src/d/actor/d_a_windmill.cpp
    src/d/actor/d_a_wz.cpp
    src/d/actor/d_a_ygcwp.cpp
    src/d/actor/d_a_yougan.cpp
    src/d/actor/d_a_ghostship.cpp
    src/d/actor/d_a_movie_player.cpp
)
target_link_libraries(tww_rel dolphin_sdk)
target_precompile_headers(tww_rel PRIVATE "include/d/dolzel_rel.h")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tww)
