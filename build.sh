#!/usr/bin/env bash
set -eu

# Docker installs n64chain in /opt
if [ -d "/opt/n64chain" ]; then
  SCRIPT_DIR="/opt"
else
  SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
fi

if [ ! -d "$SCRIPT_DIR/n64chain" ]; then
  echo "Error: n64chain not found"
  exit 1
fi

# Init the build environment:
source "$SCRIPT_DIR/init_n64_env.sh"

# Execute build commands here:
make -C SimpleN64Demo clean && make -j"$(nproc)" -C SimpleN64Demo run
# make -C SimpleN64DemoNusys clean && make -j"$(nproc)" -C SimpleN64DemoNusys run
