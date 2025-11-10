#!/usr/bin/env python3
import sys, subprocess, pathlib
from concurrent.futures import ThreadPoolExecutor

SPLIT_HASH = '/* SPLIT-HASH */'

def hash(code):
    suffix = '-15' if sys.platform == 'darwin' else ''
    return subprocess.check_output(f"cpp{suffix} -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6", shell=True, input=code.encode()).decode().strip()


#  with open(fn, 'r') as f:
#      code = f.read()

#  output = f"[{hash(code)}]"

#  if SPLIT_HASH in code:
#      codes = code.split(SPLIT_HASH)
#      hashes = [hash(c) for c in codes]
#      output = f"{output} ({'|'.join(hashes)})"

#  print(output)

def hashfile(file: pathlib.PosixPath):
    code = file.read_text()
    hashfile = file.parent / (file.name + '.hash')
    hashfile.write_text(f"[{hash(code)}]")

    if SPLIT_HASH in code:
        codes = code.split(SPLIT_HASH)
        hashes = [hash(c) for c in codes]
        code_w_hash = ''
        for i, c in enumerate(codes):
            if i:
                code_w_hash += f'/* {hashes[i-1]} | {hashes[i]} */'
            code_w_hash += c
        file.write_text(code_w_hash)

if __name__ == '__main__':
    with ThreadPoolExecutor() as executor:
        executor.map(hashfile, pathlib.Path('code').glob('**/*.cpp'))
