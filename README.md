# SimpleN64Demo

Simple Nintendo64 application using NuSystem abstraction layer.

## Setup toolchain

<https://github.com/trhodeos/modern-n64sdk>

### Environment variables

Set the following variables in your shell configuration file.

```bash
export N64_ROOT=$HOME/Dev/N64
export N64KITDIR=$N64_ROOT/N64_SDK/nintendo/n64kit
export N64_TOOLCHAIN=$N64_ROOT/N64_TOOLCHAIN
export PATH="$N64_TOOLCHAIN/tools/bin:$PATH"
export ROOT=$N64_ROOT/N64_SDK/ultra
export GCCDIR=$ROOT/GCC
```

## Emulators

<https://github.com/n64dev/cen64>
