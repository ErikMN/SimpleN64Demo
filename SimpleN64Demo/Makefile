# Print colors:
RED=\033[0;31m
LIGHT_RED=\033[1;31m
GREEN=\033[0;32m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
YELLOW=\033[1;33m
NC=\033[0m # No color

BINDIR = $(N64_TOOLCHAIN)/tools/bin

# Compiler, linker and binary tools:
CC = $(BINDIR)/mips64-elf-gcc
LD = $(BINDIR)/mips64-elf-ld
MAKEROM = $(BINDIR)/spicy
MAKEMASK = $(BINDIR)/makemask
PIFDATA = $(BINDIR)/pifdata.bin

# Library path:
LIB = $(ROOT)/usr/lib
LPR = $(LIB)/PR

# Include path:
INC = $(ROOT)/usr/include

# GCC option flags:
GCCFLAG = -c -I$(INC) -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 -D_LANGUAGE_C \
					-D_ULTRA64 -D__EXTENSIONS__ -mabi=32 -march=vr4300 -mtune=vr4300

CFLAGS = $(LCDEFS) $(LCINCS) $(LCOPTS) $(GCCFLAG) $(OPTIMIZER)

# FINAL = YES
ifeq ($(FINAL), YES)
	OPTIMIZER = -O2
	LCDEFS = -DNDEBUG -D_FINALROM -DF3DEX_GBI_2
	N64LIB = -lgultra_rom
else
	OPTIMIZER = -g3
	LCDEFS = -DDEBUG -DF3DEX_GBI_2
	N64LIB = -lgultra_rom
endif

# The app name:
NAME = SimpleN64Demo
APP = $(NAME).out
TARGETS = $(NAME).n64

HFILES = $(wildcard *.h)

CODEFILES = main.c dram_stack.c rdp_output.c controller.c
CODEOBJECTS = $(CODEFILES:.c=.o)

DATAFILES = static.c cfb.c rsp_cfb.c zbuffer.c
DATAOBJECTS = $(DATAFILES:.c=.o)

CODESEGMENT = codesegment.o

OBJECTS = $(CODESEGMENT) $(DATAOBJECTS)

LCINCS = -I.
LCOPTS = -G 0
LDFLAGS = $(MKDEPOPT) -L$(ROOT)/usr/lib $(N64LIB) -L$(GCCDIR)/mipse/lib -lkmc
LDIRT = $(APP)

.PHONY: all
all: $(TARGETS)

# Make the codesegment:
$(CODESEGMENT): $(CODEOBJECTS)
	@echo "${CYAN}*** Linking codesegment from ${LIGHT_RED}$(CODEOBJECTS)${NC}"
	$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

# Make the ROM file:
$(TARGETS) $(APP): spec $(OBJECTS)
	@echo "${PURPLE}*** Making ROM${NC}"
	$(MAKEROM) -s 9 -r $(TARGETS) -e $(APP) spec
	@echo "${BLUE}*** Masking ROM${NC}"
	$(MAKEMASK) $(TARGETS)
	@echo "\e[32m*** Done! Output: ${YELLOW}$(TARGETS)\e[0m"

# Run using CEN64:
.PHONY: run
run: $(TARGETS)
	@cen64 -multithread -noaudio $(PIFDATA) $(TARGETS)

# Run using Mupen64Plus with specialized plugins:
.PHONY: run_mupen
run_mupen: $(TARGETS)
	@mupen64plus --gfx mupen64plus-video-angrylion-plus --rsp mupen64plus-rsp-cxd4-sse2 $(TARGETS)

# Debug using CEN64:
.PHONY: debug
debug:
	@cen64 -debug localhost:8080 $(PIFDATA) $(TARGETS)

.PHONY: cppcheck
cppcheck:
	@echo "${PURPLE}*** Static code analysis${NC}"
	@cppcheck $(shell find . -name "*.[ch]") \
		--verbose --enable=all -DDEBUG=1 \
		--suppress=missingIncludeSystem \
		--suppress=unknownMacro \
		--suppress=unusedFunction

.PHONY: indent
indent:
	@echo "${PURPLE}*** Formatting code${NC}"
	@clang-format $(shell find . -name "*.[ch]") \
		-style=file -i -fallback-style=none

.PHONY: vars
vars:
	@echo "${YELLOW}*** Debug info${NC}"
	@echo "CC:" $(CC)
	@echo "ROOT:" $(ROOT)
	@echo "N64_TOOLCHAIN:" $(N64_TOOLCHAIN)
	@echo "N64KITDIR:" $(N64KITDIR)
	@echo "N64LIB:" $(N64LIB)
	@echo "MKDEPOPT:" $(MKDEPOPT)
	@echo "MAKEROM:" $(MAKEROM)
	@echo "CFLAGS:" $(CFLAGS)
	@echo "LDFLAGS:" $(LDFLAGS)
	@echo "LCINCS: " $(LCINCS)
	@echo "LCOPTS: " $(LCOPTS)
	@echo "OBJECTS:" $(OBJECTS)
	@echo "CODEOBJECTS:" $(CODEOBJECTS)
	@echo "DATAOBJECTS:" $(DATAOBJECTS)
	@echo "LCDEFS:" $(LCDEFS)

.PHONY: clean
clean:
	@echo "${RED}*** Clean build${NC}"
	$(RM) $(APP) $(TARGETS) *.o *.out
