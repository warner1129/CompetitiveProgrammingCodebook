#!/bin/bash
set -ex

DOCKER=docker
if type podman &> /dev/null; then
  DOCKER=podman
fi

cd "$(dirname "$BASH_SOURCE")"
$DOCKER build -f Dockerfile -t icpc ..
