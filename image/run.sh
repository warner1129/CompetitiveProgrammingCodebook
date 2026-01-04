#!/bin/bash
set -ex

DOCKER=docker
use_podman=0
if type podman &> /dev/null; then
    DOCKER=podman
    use_podman=1
fi

$DOCKER run -it --rm \
  -w '/code' -v "$PWD:/code${use_podman:+:z}" \
  --security-opt=seccomp=unconfined \
  -h icpc icpc
