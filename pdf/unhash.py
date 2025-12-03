#!/usr/bin/env python3
import sys, subprocess, pathlib, re
from concurrent.futures import ThreadPoolExecutor


SPLIT_HASH = '/* SPLIT-HASH */'
HASH_RE = r'/* \d{6} | \d{6} */'

def unhashfile(file: pathlib.PosixPath):
    code = file.read_text()
    hashfile = file.parent / (file.name + '.hash')
    hashfile.remove()

    code_wo_hash = re.sub(code, HASH_RE, SPLIT_HASH)
    file.write_text(code_wo_hash)

if __name__ == '__main__':
    with ThreadPoolExecutor() as executor:
        executor.map(hashfile, pathlib.Path('code').glob('**/*.cpp'))
