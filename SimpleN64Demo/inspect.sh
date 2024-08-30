#!/usr/bin/env bash

error_exit() {
  echo "$1" >&2
  exit 1
}

inspect_out() {
  # Check if the output file exists
  if [[ ! -f "$OUT" ]]; then
    error_exit "Error: Output file '$OUT' does not exist."
  fi

  # File type:
  file "$OUT" >"$1" || error_exit "Error: 'file' failed."

  # Binary headers and sections:

  echo "Section headers:" >>"$1"
  "$BINDIR"/mips64-elf-objdump -h "$OUT" >>"$1" || error_exit "Error: 'objdump -h' failed."

  # echo "Binary headers and sections:" >>"$1"
  # "$BINDIR"/mips64-elf-objdump -x "$OUT" >>"$1" || error_exit "Error: 'objdump -x' failed."

  # Symbol table:
  # echo "Symbol table:" >>"$1"
  # "$BINDIR"/mips64-elf-nm "$OUT" >>"$1" || error_exit "Error: 'nm' failed."

  # Dynamic symbols (if applicable):
  # echo "Dynamic symbols (if applicable):" >>"$1"
  # "$BINDIR"/mips64-elf-readelf -Ds "$OUT" >>"$1" || error_exit "Error: 'readelf -Ds' failed."

  # Strings in the binary:
  # echo "Strings in the binary:" >>"$1"
  # strings "$OUT" >>"$1" || error_exit "Error: 'strings' failed."
}

if [[ -z "$N64_ROOT" ]]; then
  error_exit "Please init N64 environment first using 'source init_n64_env.sh'."
fi

command -v make >/dev/null 2>&1 || error_exit "Error: 'make' is not installed."
command -v meld >/dev/null 2>&1 || error_exit "Error: 'meld' is not installed."

OUT="SimpleN64Demo.out"
BINDIR="$N64_TOOLCHAIN/tools/bin"

# Generate reference output:
echo "Generating reference output..."
make mild
inspect_out ok.txt
make clean

# Generate output:
echo "Generating output..."
make
inspect_out nok.txt
make clean

# Compare files using meld:
if [[ -f ok.txt && -f nok.txt ]]; then
  echo "Comparing outputs with meld..."
  meld ok.txt nok.txt || error_exit "Error: 'meld' failed."
else
  error_exit "Error: One or both output files (ok.txt, nok.txt) are missing."
fi
