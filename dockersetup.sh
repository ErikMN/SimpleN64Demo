#!/usr/bin/env bash
#
# Export n64chain built inside Docker to host workspace.
#
set -eu

# Print colors:
FMT_GREEN=$(printf '\033[32m')
FMT_BLUE=$(printf '\033[34m')
FMT_YELLOW=$(printf '\033[33m')
FMT_RED=$(printf '\033[31m')
FMT_BOLD=$(printf '\033[1m')
FMT_RESET=$(printf '\033[0m')

SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

IMAGE_NAME="n64_tool_chain_img"
OUT_DIR="$SCRIPT_DIR/n64chain"

echo "${FMT_GREEN}${FMT_BOLD}*** Export N64 toolchain from Docker${FMT_RESET}"

if ! command -v docker >/dev/null 2>&1; then
  echo "${FMT_RED}*** Docker is not installed${FMT_RESET}"
  exit 1
fi

# Remove previous export if it exists:
if [ -d "${OUT_DIR}" ]; then
  echo "${FMT_YELLOW}*** Removing existing n64chain directory${FMT_RESET}"
  rm -rf "${OUT_DIR}"
fi

echo "${FMT_BLUE}*** Building and exporting toolchain using Docker${FMT_RESET}"

docker build \
  --output type=local,dest="${SCRIPT_DIR}" \
  -t "${IMAGE_NAME}" \
  "${SCRIPT_DIR}"

echo "${FMT_GREEN}${FMT_BOLD}*** N64 toolchain exported successfully${FMT_RESET}"
echo "${FMT_BLUE}Location: ${OUT_DIR}${FMT_RESET}"
