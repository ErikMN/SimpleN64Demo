# SimpleN64Demo <img src="img/n64.svg" width="32" alt="N64 logo"/>

Simple Nintendo64 application using Nintendo libraries.

```text
├── SimpleN64Demo       // Demo using libultra
└── SimpleN64DemoNusys  // Demo using NuSystem abstraction layer
```

## Setup toolchain and SDK

### Building on host

For Debian/Ubuntu/Fedora run:

```bash
make deps
```

then run:

```bash
make hostsetup
```

This will take a while (the n64chain will take about 1GB of disk space when done). </br>
After that just source the init script like so (this will be done automatically in VSCodes integrated terminal):

```bash
source init_n64_env.sh
```

### Building using [Docker](https://docs.docker.com/get-docker/)

This will build the n64chain in Docker without the need to install any host dependencies, just run:

```bash
make dockersetup
```

Then run:

```bash
make dockerbuild
```

To build the N64 apps (the Docker image takes about 2.5GB of disk space).

## Problems

If you get an error message when building stating something like:

```bash
../mips64-elf/bin/as: error while loading shared libraries: libopcodes-2.34.so: cannot open shared object file: No such file or directory
```

You will need to set LD_LIBRARY_PATH to point to the lib directory of the toolchain:

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$N64_TOOLCHAIN/tools/x86_64-pc-linux-gnu/mips64-elf/lib/
```

## Emulators

[Cen64](https://github.com/n64dev/cen64) is included when setting up the n64chain.

```bash
alias cen64mt="cen64 -multithread -noaudio $N64_TOOL_CHAIN/tools/bin"
```

More emulators [here](https://n64.dev/#emulators).

## Debugging using VSCode and GDB

It is possible to debug the N64 app using GDB. </br>
This has been setup with Visual Studio Code. </br>

### Prerequisites

* [Visual Studio Code](https://code.visualstudio.com/)
* [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
* gdb-multiarch (GNU Debugger with support for multiple architectures)

With cen64 setup as the N64 emulator just run:

```bash
make debug
```

to start the GDB server on port 8080. </br>
Then press ```F5``` in VSCode to connect to the GDB server. </br>
If a breakpoint has been set in the code, GDB will pause the execution at that point.

## Misc

### Useful links

[Awesome N64 Development](https://n64.dev/)

[Nintendo 64 Development Resource](https://ultra64.ca/)

[Nintendo 64 Online Manuals](https://ultra64.ca/files/documentation/online-manuals/man-v5-2/allman52/)

[Nintendo N64 Source code Programming - A Basic Introduction](https://www.youtube.com/watch?v=68nFnspMPfM)

[Debugging Nintendo 64 ROMs with GDB and Cen64](https://www.youtube.com/watch?v=IPiZqg-2CrA)

[Wavefront OBJ model converter](https://github.com/n64dev/objn64)

[Nintendo 64 Programming notes](https://badd10de.dev/notes/n64-programming.html)

[Nintendo 64 modern SDK](https://crashoveride95.github.io/modernsdk/)
