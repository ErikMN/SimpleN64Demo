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
ARCHIVE="n64chain.tar.gz"
OUT_DIR="$SCRIPT_DIR/n64chain"

echo "${FMT_GREEN}${FMT_BOLD}*** Export N64 toolchain from Docker${FMT_RESET}"

if ! command -v docker >/dev/null 2>&1; then
  echo "${FMT_RED}*** Docker is not installed${FMT_RESET}"
  exit 1
fi

echo "${FMT_BLUE}*** Building Docker image${FMT_RESET}"
docker build -t "${IMAGE_NAME}" "${SCRIPT_DIR}" >/dev/null

echo "${FMT_BLUE}*** Extracting toolchain archive${FMT_RESET}"
docker run --rm "${IMAGE_NAME}" cat /n64chain.tar.gz >"${SCRIPT_DIR}/${ARCHIVE}"

if [ -d "${OUT_DIR}" ]; then
  echo "${FMT_YELLOW}*** Removing existing n64chain directory${FMT_RESET}"
  # Make sure we can delete previously exported tree:
  chmod -R u+w "${OUT_DIR}" || true
  rm -rf "${OUT_DIR}"
fi

echo "${FMT_BLUE}*** Unpacking toolchain${FMT_RESET}"
tar -xzf "${SCRIPT_DIR}/${ARCHIVE}" -C "${SCRIPT_DIR}"

echo "${FMT_BLUE}*** Cleaning up archive${FMT_RESET}"
rm -f "${SCRIPT_DIR}/${ARCHIVE}"

echo "${FMT_GREEN}${FMT_BOLD}*** N64 toolchain exported successfully${FMT_RESET}"
echo "${FMT_BLUE}Location: ${OUT_DIR}${FMT_RESET}"
