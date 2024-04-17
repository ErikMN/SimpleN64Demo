#!/usr/bin/env bash
# Source me!

# Print colors:
FMT_GREEN=$(printf '\033[32m')
FMT_BLUE=$(printf '\033[34m')
FMT_YELLOW=$(printf '\033[33m')
FMT_RED=$(printf '\033[31m')
FMT_BOLD=$(printf '\033[1m')
FMT_RESET=$(printf '\033[0m')

if [ -d "/opt/n64chain" ]; then
  echo "${FMT_GREEN}${FMT_BOLD}*** Init N64 toolchain in Docker${FMT_RESET}"
  SCRIPT_DIR="/opt"
else
  echo "${FMT_BLUE}${FMT_BOLD}*** Init N64 toolchain on host${FMT_RESET}"
  SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
fi

N64_TOOL_CHAIN="$SCRIPT_DIR/n64chain"

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
  echo "${FMT_RED}Error: This script must be sourced. Please use 'source ${0}' or '. ${0}'${FMT_RESET}"
  exit 1
fi

if [ ! -d "$N64_TOOL_CHAIN" ]; then
  echo "${FMT_YELLOW}*** N64 toolchain is not setup?${FMT_RESET}"
  echo "${FMT_BLUE}*** Please run setup_n64_toolchain.sh first${FMT_RESET}"
  return
fi

export N64_TOOLCHAIN=$N64_TOOL_CHAIN

# Export variables used to build:
export N64_ROOT=$N64_TOOL_CHAIN
export PATH="$N64_ROOT/tools/bin:$PATH"
export N64KITDIR=$N64_ROOT/N64_SDK/nintendo/n64kit
export ROOT=$N64_ROOT/N64_SDK/ultra
export GCCDIR=$ROOT/GCC
export N64_DEMOS="$N64_ROOT/N64_SDK/ultra/usr/src/pr/demos"

echo "${FMT_GREEN}${FMT_BOLD}*** N64 TOOLCHAIN INITIALIZED ***${FMT_RESET}"
echo "${FMT_BLUE}N64_ROOT:           $N64_ROOT${FMT_RESET}"
echo "${FMT_BLUE}ROOT:               $ROOT${FMT_RESET}"
echo "${FMT_BLUE}GCCDIR:             $GCCDIR${FMT_RESET}"
echo "${FMT_BLUE}N64KITDIR:          $N64KITDIR${FMT_RESET}"
echo "${FMT_BLUE}N64_DEMOS:          $N64_DEMOS${FMT_RESET}"
