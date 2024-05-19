#!/usr/bin/env bash
#
# Sets up the N64 toolchain on a modern Linux system using these resources:
#
# https://ultra64.ca/resources/software/
# https://github.com/tj90241/n64chain
# https://github.com/trhodeos/modern-n64sdk?tab=readme-ov-file
# https://github.com/n64dev/cen64
#
set -eu

# Print colors:
FMT_RED=$(printf '\033[31m')
FMT_GREEN=$(printf '\033[32m')
FMT_YELLOW=$(printf '\033[33m')
FMT_BOLD=$(printf '\033[1m')
FMT_RESET=$(printf '\033[0m')

SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"

N64_TOOL_CHAIN="$SCRIPT_DIR/n64chain"

SPICY_VER="0.6.2"
MAKEMASK_VER="0.2.2"

OS=$(uname)
ARCH=$(uname -m)
PLATFORM="linux_amd64"

# Check platform:
if [ "$OS" = "Linux" ]; then
  if [ "$ARCH" = "arm64" ]; then
    PLATFORM="linux_arm64"
  elif [ "$ARCH" = "x86_64" ]; then
    PLATFORM="linux_amd64"
  fi
elif [ "$OS" = "Darwin" ]; then
  if [ "$ARCH" = "arm64" ]; then
    PLATFORM="darwin_arm64"
  elif [ "$ARCH" = "x86_64" ]; then
    PLATFORM="darwin_amd64"
  fi
else
  echo "${FMT_BOLD}${FMT_RED}*** Unsupported platform: ${PLATFORM}${FMT_RESET}"
  exit 1
fi

SPICY_URL="https://github.com/trhodeos/spicy/releases/download/v${SPICY_VER}/spicy_${SPICY_VER}_${PLATFORM}.tar.gz"
MAKEMASK_URL="https://github.com/trhodeos/makemask/releases/download/v${MAKEMASK_VER}/makemask_${MAKEMASK_VER}_${PLATFORM}.tar.gz"
SDK_URL="https://ultra64.ca/files/software/other/sdks/n64sdk.7z"
PIF_URL="https://archive.org/download/mame-0.221-roms-merged/aleck64.zip/pifdata.bin"

build_toolchain() {
  if [ -d "$N64_TOOL_CHAIN/tools/bin" ]; then
    echo "${FMT_YELLOW}*** N64 toolchain is already setup?${FMT_RESET}"
    return 0
  fi
  echo "${FMT_BOLD}${FMT_GREEN}*** Build N64 toolchain${FMT_RESET}"
  git clone https://github.com/tj90241/n64chain.git "$N64_TOOL_CHAIN" || echo "${FMT_YELLOW}*** N64 toolchain already cloned${FMT_RESET}"

  BUILD_SCRIPT="$N64_TOOL_CHAIN/tools/build-posix64-toolchain.sh"

  # Use HTTPS instead of FTP:
  sed -i 's/BINUTILS="ftp:/BINUTILS="https:/' "$BUILD_SCRIPT"
  sed -i 's/GCC="ftp:/GCC="https:/' "$BUILD_SCRIPT"
  sed -i 's/MAKE="ftp:/MAKE="https:/' "$BUILD_SCRIPT"

  # Build the tool chain (takes some time):
  "$BUILD_SCRIPT" || {
    echo "${FMT_RED}*** Faild to build N64 toolchain${FMT_RESET}"
    exit 1
  }
  echo "${FMT_GREEN}*** Build N64 toolchain done.${FMT_RESET}"
}

intall_tools() {
  if [ ! -d "$N64_TOOL_CHAIN/tools/bin" ]; then
    echo "${FMT_YELLOW}*** N64 toolchain is not setup?${FMT_RESET}"
    return 1
  fi
  echo "${FMT_GREEN}*** Setup SDK and tools${FMT_RESET}"

  # Download SDK and tools:
  wget -nc -P "$N64_TOOL_CHAIN" "$SDK_URL" || {
    echo "${FMT_RED}*** Failed to download N64 SDK${FMT_RESET}"
    return 1
  }
  wget -nc -P "$N64_TOOL_CHAIN" "$SPICY_URL" || {
    echo "${FMT_RED}*** Failed to download spicy${FMT_RESET}"
    return 1
  }
  wget -nc -P "$N64_TOOL_CHAIN" "$MAKEMASK_URL" || {
    echo "${FMT_RED}*** Failed to download makemask${FMT_RESET}"
    return 1
  }

  # Install tools:
  tar -xzf "$N64_TOOL_CHAIN/spicy_${SPICY_VER}_${PLATFORM}.tar.gz" --directory="$N64_TOOL_CHAIN/tools/bin" spicy || {
    echo "${FMT_RED}*** Failed to install spicy${FMT_RESET}"
    return 1
  }
  tar -xzf "$N64_TOOL_CHAIN/makemask_${MAKEMASK_VER}_${PLATFORM}.tar.gz" --directory="$N64_TOOL_CHAIN/tools/bin" makemask || {
    echo "${FMT_RED}*** Failed to install makemask${FMT_RESET}"
    return 1
  }

  # Install SDK:
  if [ ! -d "$N64_TOOL_CHAIN/N64_SDK" ]; then
    7z x "$N64_TOOL_CHAIN/n64sdk.7z" -o"$N64_TOOL_CHAIN/N64_SDK"
  fi

  # Rename these files:
  if [ -d "$N64_TOOL_CHAIN/N64_SDK/ultra/GCC/MIPSE" ]; then
    mv "$N64_TOOL_CHAIN/N64_SDK/ultra/GCC/MIPSE" "$N64_TOOL_CHAIN/N64_SDK/ultra/GCC/mipse"
    mv "$N64_TOOL_CHAIN/N64_SDK/ultra/GCC/mipse/LIB" "$N64_TOOL_CHAIN/N64_SDK/ultra/GCC/mipse/lib"
    mv "$N64_TOOL_CHAIN/N64_SDK/ultra/GCC/mipse/lib/CRTKMC.O" "$N64_TOOL_CHAIN/N64_SDK/ultra/GCC/mipse/lib/crtkmc.o"
    mv "$N64_TOOL_CHAIN/N64_SDK/ultra/GCC/mipse/lib/LIBKMC.A" "$N64_TOOL_CHAIN/N64_SDK/ultra/GCC/mipse/lib/libkmc.a"
  fi

  # Update PRdefs with the new tools:
  cat <<EOF >"$N64_TOOL_CHAIN/N64_SDK/ultra/usr/include/make/PRdefs"
#
# for N64OS PC
#

# application name
CC = mips64-elf-gcc
LD = mips64-elf-ld
MAKEROM = spicy

# library path
LIB = \$(ROOT)/usr/lib
LPR = \$(LIB)/PR

# include path
INC = \$(ROOT)/usr/include

# gcc option
GCCFLAG = -c -I\$(INC) -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 -D_LANGUAGE_C -D_ULTRA64 -D__EXTENSIONS__ -mabi=32 -march=vr4300 -mtune=vr4300
CFLAGS = \$(LCDEFS) \$(LCINCS) \$(LCOPTS) \$(GCCFLAG) \$(OPTIMIZER)

# common rules
COMMONRULES = \$(ROOT)/usr/include/make/commonrules

# for CELF
CELFRULES = \$(ROOT)/usr/include/make/celfrules

include \$(ROOT)/usr/include/make/celfdefs
EOF
  echo "${FMT_GREEN}*** Setup SDK and tools done.${FMT_RESET}"
}

setup_emulator() {
  if ! command -v cmake &>/dev/null; then
    echo "${FMT_RED}*** CMake is not installed.${FMT_RESET}"
    return 1
  fi
  if [ -e "$N64_TOOL_CHAIN/tools/bin/cen64" ]; then
    echo "${FMT_YELLOW}*** N64 emulator is already installed${FMT_RESET}"
    return 0
  fi
  echo "${FMT_GREEN}*** Setup N64 emulator${FMT_RESET}"

  git clone https://github.com/n64dev/cen64.git "$N64_TOOL_CHAIN/cen64" || {
    echo "${FMT_RED}*** Failed to clone N64 emulator${FMT_RESET}"
    return 1
  }
  cmake -B "$N64_TOOL_CHAIN/cen64/build" "$N64_TOOL_CHAIN/cen64" || {
    echo "${FMT_RED}*** Failed to initialize N64 emulator build${FMT_RESET}"
    return 1
  }
  make -j"$(nproc)" -C "$N64_TOOL_CHAIN/cen64/build" || {
    echo "${FMT_RED}*** Failed to build N64 emulator${FMT_RESET}"
    return 1
  }
  cp "$N64_TOOL_CHAIN/cen64/build/cen64" "$N64_TOOL_CHAIN/tools/bin" || {
    echo "${FMT_RED}*** Failed to copy N64 emulator to N64 toolchain${FMT_RESET}"
    return 1
  }
  wget -nc -P "$N64_TOOL_CHAIN/tools/bin" "$PIF_URL" || {
    echo "${FMT_RED}*** Failed to download pifdata${FMT_RESET}"
    return 1
  }
}

# Run the setup functions:
build_toolchain || exit 1
intall_tools || exit 1
setup_emulator || exit 1
echo "${FMT_BOLD}${FMT_GREEN}*** N64 toolchain and SDK setup OK!${FMT_RESET}"
