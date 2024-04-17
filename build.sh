#!/usr/bin/env bash
set -eu

if [ ! -f "/opt/init_n64_env.sh" ]; then
  echo "Please run from Docker"
  exit 1
fi

# Init the build environment:
source /opt/init_n64_env.sh

# Execute build commands here:
make -C SimpleN64Demo clean && make -C SimpleN64Demo
make -C SimpleN64DemoNusys clean && make -C SimpleN64DemoNusys
