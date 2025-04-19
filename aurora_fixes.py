import re
from pathlib import Path

REPLACEMENTS = [
    # includes
    # (re.compile(r'^#include ["<]dolphin/gx/GX\w*\.h[">]', re.MULTILINE), '#include <dolphin/gx.h>'),
    # (re.compile(r'^#include ["<]dolphin/os/OS\.h[">]', re.MULTILINE), '#include <dolphin/os.h>'),

    # Panic and return values on unimplemented functions
    (re.compile(r'^(\w+)::(~?)\1([^{]*) {\s+/\* Nonmatching \*/\s+}', re.MULTILINE), r'\1::\2\1\3 {\n    NOT_IMPLEMENTED;\n}'),
    (re.compile(r'^(void) ([^{]*){\s+/\* Nonmatching \*/\s+}', re.MULTILINE), r'\1 \2{\n    NOT_IMPLEMENTED;\n}'),
    (re.compile(r'^(static )?(const )?(int|float|bool|s8|u8|s16|u16|s32|u32|f32|BOOL|cPhs_State|fpc_ProcID|[\w:]+\s*\*)\s*([^{]*) {\s+/\* Nonmatching \*/\s+}', re.MULTILINE), r'\1\2\3 \4 {\n    NOT_IMPLEMENTED;\n    return 0;\n}'),

    # GX enums
    # (re.compile(r'GX_BL_SRC_COLOR', re.MULTILINE), 'GX_BL_SRCCLR'),
    # (re.compile(r'GX_BL_DST_COLOR', re.MULTILINE), 'GX_BL_DSTCLR'),
    # (re.compile(r'GX_BL_INV_SRC_COLOR', re.MULTILINE), 'GX_BL_INVSRCCLR'),
    # (re.compile(r'GX_BL_INV_DST_COLOR', re.MULTILINE), 'GX_BL_INVDSTCLR'),
    # (re.compile(r'GX_BL_SRC_ALPHA', re.MULTILINE), 'GX_BL_SRCALPHA'),
    # (re.compile(r'GX_BL_INV_SRC_ALPHA', re.MULTILINE), 'GX_BL_INVSRCALPHA'),
    # (re.compile(r'GX_BL_DST_ALPHA', re.MULTILINE), 'GX_BL_DSTALPHA'),
    # (re.compile(r'GX_BL_INV_DST_ALPHA', re.MULTILINE), 'GX_BL_INVDSTALPHA'),
]
CHECK_NOT_IMPLEMENTED = re.compile(r'NOT_IMPLEMENTED;', re.MULTILINE)
GLOBAL_H = re.compile(r'^#include ["<]global.h[">]', re.MULTILINE)
FIRST_INCLUDE = re.compile(r'(#include ["<][^">]*[">][^\n]*)')


def patch_file(filename: Path):
    content = filename.read_text(encoding='utf-8')
    modified = False
    for regex, replace in REPLACEMENTS:
        content, count = regex.subn(replace, content)
        if count > 0:
            modified = True

    if CHECK_NOT_IMPLEMENTED.search(content) and not GLOBAL_H.search(content):
        content = FIRST_INCLUDE.sub(r'\1\n#include "global.h"', content, 1)
        modified = True

    if modified:
        print(f'Writing "{filename}"')
        filename.write_text(content, encoding='utf-8')


EXCLUDE_DIRS = {
    Path('include/dolphin'),
    Path('src/dolphin'),
    Path('src/port'),
    Path('src/PowerPC_EABI_Support'),
}

EXTENSIONS = {
    '.h',
    '.cpp',
    '.inc',
}


def walk_directory(path: Path):
    files = files = list[Path]()
    if path in EXCLUDE_DIRS:
        return files
    for item in path.iterdir():
        if item.is_dir():
            files.extend(walk_directory(item))
        else:
            if item.suffix in EXTENSIONS:
                files.append(item)
    return files


def main():
    files = list[Path]()
    files.extend(walk_directory(Path('include')))
    files.extend(walk_directory(Path('src')))
    for file in files:
        patch_file(file)


if __name__ == '__main__':
    main()
