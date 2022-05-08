# SimpleN64Demo

Simple Nintendo64 application using Nintendo libraries.

```text
├── SDK                 // Pre-built ready-to-use N64 SDK for Linux
└── SimpleN64DemoNusys  // Demo using NuSystem abstraction layer
```

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

## Misc

### Useful links

Awesome N64 Development
<https://n64.dev/>

Nintendo 64 Development Resource
<https://ultra64.ca/>

Function Reference
<https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/n64man/n64man.htm>

Nintendo N64 Source code Programming - A Basic Introduction
<https://www.youtube.com/watch?v=68nFnspMPfM>

Debugging Nintendo 64 ROMs with GDB and Cen64
<https://www.youtube.com/watch?v=IPiZqg-2CrA>

Wavefront OBJ model converter that generates optimized N64 displaylists for compilation with libultra.
<https://github.com/n64dev/objn64>
