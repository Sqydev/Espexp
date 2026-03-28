#!/usr/bin/env bash
cat > .clangd << EOF
CompileFlags:
  Add:
    - --target=riscv32-esp-elf
    - -isystem$HOME/.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/8.4.0
    - -isystem$HOME/.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/8.4.0/riscv32-esp-elf
  Remove:
    - -fstrict-volatile-bitfields
    - -fno-tree-switch-conversion
EOF
