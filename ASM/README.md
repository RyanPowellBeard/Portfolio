# ASM Bootloader Project

A collection of x86 Assembly bootloader programs demonstrating various bootloading techniques and BIOS interactions.

## Overview

This project contains several bootloader implementations written in x86 assembly, ranging from simple single-stage bootloaders to more complex multi-stage bootloaders. These programs showcase fundamental concepts like BIOS interrupts, memory management, and disk I/O in real mode.

## Files

### Simple Bootloaders

- **boot-hello.asm** / **boot-hello.bin**
  - A minimal single-stage bootloader that prints "Hello World" to the screen
  - Demonstrates basic BIOS teletype output (INT 0x10)
  - Entry point: `0x7c00` (standard BIOS boot sector address)

- **bootloader-hello.asm** / **bootloader-hello.bin**
  - An interactive bootloader with user input capabilities
  - Prompts the user for input and echoes it back to the screen
  - Features string printing and input reading functions
  - Demonstrates string handling in real mode assembly

### Multi-Stage Bootloader

- **first_stage.asm** / **first_stage.bin**
  - The first stage of a two-stage bootloader
  - Reads the second stage from disk (sector 2) into memory at `0x0000:0x8000`
  - Includes disk I/O error handling
  - Jumps to the second stage after successful load

- **second_stage.asm** / **second_stage.bin**
  - The second stage bootloader loaded by the first stage
  - Prints "Second Stage" to the screen
  - Located at memory address `0x0000:0x8000`
  - Ready for loading a kernel or performing additional boot tasks

- **combined.bin**
  - Pre-built combined image containing both first and second stages
  - Created by concatenating first_stage.bin and second_stage.bin

## Building

### Prerequisites

- **NASM** (Netwide Assembler): `sudo apt-get install nasm` (or equivalent for your OS)
- **QEMU** (optional, for testing): `sudo apt-get install qemu-system-x86`

### Assembly Instructions

Assemble any ASM file to binary using NASM:

```bash
nasm -f bin <filename>.asm -o <filename>.bin
```

Example:
```bash
nasm -f bin boot-hello.asm -o boot-hello.bin
```

### Combining Stages (Linux/Mac)

To create a combined image of the two-stage bootloader:

```bash
cat first_stage.bin second_stage.bin > combined.bin
```

## Running and Testing

### Using QEMU

Test any bootloader image with QEMU:

```bash
# Simple bootloaders
qemu-system-x86_64 -drive format=raw,file=boot-hello.bin

# Two-stage bootloader
qemu-system-x86_64 -drive format=raw,file=first_stage.bin

# Combined image
qemu-system-x86_64 -drive format=raw,file=combined.bin
```

Press `Ctrl+A` then `X` to exit QEMU.

### Writing to USB (for Real Hardware)

**Warning: This will overwrite data on your device!**

1. Identify your USB device: `lsblk` or `sudo fdisk -l`
2. Write the bootloader to the first sector:
   ```bash
   sudo dd if=<bootloader>.bin of=/dev/sdX bs=512 count=1
   ```
   Replace `/dev/sdX` with your USB device name (e.g., /dev/sdb, /dev/sdc)

3. Boot from the USB device by changing your BIOS/UEFI boot order

## Technical Details

### Memory Layout

- **Boot Sector Load Address**: `0x7c00` (BIOS standard)
- **Second Stage Load Address**: `0x0000:0x8000` (via first stage)
- **Stack Pointer**: Initialized to `0x7c00` (grows downward)

### Boot Sector Format

- **Size**: Must be exactly 512 bytes
- **Padding**: Unused space is filled with zeros
- **Boot Signature**: Ends with `0xAA55` at bytes 510-511 (required for BIOS recognition)

### BIOS Interrupts Used

- **INT 0x10** (Video Services): Used for printing characters to screen
  - Function 0x0E: Teletype output mode
- **INT 0x13** (Disk I/O): Used for reading sectors from disk
  - Function 0x02: Read sectors

### Real Mode Operation

All code runs in x86 real mode (16-bit):
- No virtual memory
- Linear memory addressing using segment:offset notation
- Direct hardware access via BIOS interrupts

## Assembly Syntax

All files use NASM (Netwide Assembler) syntax. Key directives:

- `[org 0x7c00]`: Sets the origin/load address
- `bits 16`: Specifies 16-bit real mode code generation
- `times N db 0`: Repeats zero bytes N times (for padding)
- `dw`: Define word (2 bytes)

## Project Structure

```
ASM/
├── boot-hello.asm           # Simple "Hello World" bootloader
├── boot-hello.bin           # Compiled binary
├── bootloader-hello.asm     # Interactive bootloader with input
├── bootloader-hello.bin     # Compiled binary
├── first_stage.asm          # Two-stage bootloader (stage 1)
├── first_stage.bin          # Compiled binary
├── second_stage.asm         # Two-stage bootloader (stage 2)
├── second_stage.bin         # Compiled binary
├── combined.bin             # Combined first + second stage
├── Linux-Bootloader/        # Container directory
└── README.md                # This file
```

## Learning Resources

These bootloaders demonstrate:
- x86 assembly language fundamentals
- BIOS real mode operation
- Memory addressing and segmentation
- BIOS interrupt usage
- Disk I/O operations
- Multi-stage bootloading techniques

## License

These are educational examples for learning purposes.

## Notes

- The bootloaders are tested using QEMU on Linux
- All code assumes x86-64 architecture with x86 real mode emulation
- These are simplified bootloaders intended for educational purposes, not production use
- Modern systems use UEFI instead of BIOS, which requires different approaches
