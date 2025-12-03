#!/usr/bin/env python3
import pathlib, re
from concurrent.futures import ThreadPoolExecutor


SPLIT_HASH = '/* SPLIT-HASH */'
HASH_RE = r'/\* [a-f\d]{6} \| [a-f\d]{6} \*/'

def unhashfile(file: pathlib.PosixPath):
    code = file.read_text()

    code_wo_hash = re.sub(HASH_RE, SPLIT_HASH, code)
    file.write_text(code_wo_hash)

    hashfile = file.parent / (file.name + '.hash')
    hashfile.remove()

if __name__ == '__main__':
    with ThreadPoolExecutor() as executor:
        executor.map(unhashfile, pathlib.Path('code').glob('**/*.cpp'))
