#!/usr/bin/env python3
import sys, subprocess
fn = sys.argv[1]

SPLIT_HASH = '/* SPLIT-HASH */'

def hash(code):
    return subprocess.check_output("cpp-15 -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6", shell=True, input=code.encode()).decode().strip()

with open(fn, 'r') as f:
    code = f.read()

output = f"[{hash(code)}]"

if SPLIT_HASH in code:
    codes = code.split(SPLIT_HASH)
    hashes = [hash(c) for c in codes]
    output = f"{output} ({'|'.join(hashes)})"

print(output)
