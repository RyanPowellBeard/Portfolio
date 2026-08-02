[org 0x7c00]   ;The BIOS loads the boot sector at address 0x7c00

; Set up the stack, Important for any function calls or interrupts
    xor ax, ax      ; Clear the AX register
    mov ds, ax      ; Set the data segment to 0
    mov es, ax      ; Set the extra segment to 0
    mov ss, ax      ; Set the stack segment to 0
    mov sp, 0x7c00  ; Set the stack pointer to the end of the boot sector, stack grows downwards

; Read second_stage.bin from the disk into memory at 0x0000:0x8000
    mov ah, 0x02    ; BIOS function to read sectors
    mov al, 1       ; Number of sectors to read (1 sector = 512 bytes)
    mov ch, 0       ; Cylinder number (0 for the first track)
    mov cl, 2       ; Sector number (starts from 1, so sector 2 is the second sector)
    mov dh, 0       ; Head number (0 for the first head)
    mov dl, 0x80    ; Drive number (0x80 for the first hard drive)
    mov bx, 0x8000  ; Buffer address to load the second stage (segment:offset = 0x0000:0x8000)
    int 0x13        ; Call BIOS interrupt to read from disk

    jc disk_error     ; Jump to disk_error if the carry flag is set (indicating an error)

    ; Jump to the second stage code at 0x0000:0x8000
    jmp 0x0000:0x8000 ; Jump to the second stage code

disk_error:
    mov ah, 0x0e   ; Teletype output function for BIOS interrupt 0x10
    mov al, 'E'    ; Character 'E'
    int 0x10       ; Call BIOS interrupt to print 'E' Trigger Video Service Interrupt
    cli             ; Clear interrupts to prevent further issues

halt:
    hlt             ; Halt the CPU
    jmp halt        ; Infinite loop to keep the CPU halted

    times 510-($-$$) db 0 ; Fill the rest of the bytes with zeros to make the total size of the boot sector 512 bytes
    dw 0xAA55           ; Boot signature (0xAA55) at the end of the boot sector (required for the BIOS to recognize it as a valid bootloader)

    ; To Assemble and Create Bootable Image:
    ; nasm -f bin first_stage.asm -o first_stage.bin
    ; dd if=first_stage.bin of=/dev/sdX bs=512 count=1
    ; Replace /dev/sdX with the appropriate device name for your USB drive
    ; After writing the bootloader to the USB drive, you can boot from it to load the second stage from the disk.

    ; To run in qemu:
    ; qemu-system-x86_64 -drive format=raw,file=first_stage.bin 