#!/bin/bash
set -x
cp -v --update=none /opt/* .
setarch `uname -m` -R /bin/tmux
