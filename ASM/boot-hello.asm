[org 0x7c00]    ;The BIOS loads the boot sector at address 0x7c00

;Bootloader code starts here
start:
    mov ah, 0x0e   ;Teletype output function for BIOS interrupt 0x10
    mov al, 'H'    ;Character 'H'
    int 0x10       ;Call BIOS interrupt to print 'H' Trigger Video Service Intterupt ,
    mov al, 'e'    ;Character 'e'
    int 0x10       ;Call BIOS interrupt to print 'e' Trigger Video Service Intterupt
    mov al, 'l'    ;Character 'l'
    int 0x10       ;Call BIOS interrupt to print 'l' Trigger Video Service Intterupt
    mov al, 'l'    ;Character 'l'
    int 0x10       ;Call BIOS interrupt to print 'l' Trigger Video Service Intterupt
    mov al, 'o'    ;Character 'o'
    int 0x10       ;Call BIOS interrupt to print 'o' Trigger Video Service Intterupt
    mov al, ' '    ;Character ' '
    int 0x10       ;Call BIOS interrupt to print ' ' Trigger Video Service Intterupt
    mov al, 'W'    ;Character 'W'
    int 0x10       ;Call BIOS interrupt to print 'W' Trigger Video Service Intterupt
    mov al, 'o'    ;Character 'o'
    int 0x10       ;Call BIOS interrupt to print 'o' Trigger Video Service Intterupt
    mov al, 'r'    ;Character 'r'
    int 0x10       ;Call BIOS interrupt to print 'r' Trigger Video Service Intterupt
    mov al, 'l'    ;Character 'l'
    int 0x10       ;Call BIOS interrupt to print 'l' Trigger Video Service Intterupt
    mov al, 'd'    ;Character 'd'
    int 0x10       ;Call BIOS interrupt to print 'd' Trigger Video Service Intterupt
    jmp $          ;Infinite loop to prevent the bootloader from exiting (jumps to the current address)
    
    times 510-($-$$) db 0 ;Fill the rest of the bytes with zeros to make the total size of the boot sector 512 bytes
    dw 0xAA55           ;Boot signature (0xAA55) at the end of the boot sector (required for the BIOS to recognize it as a valid bootloader)

    ; To Assemble and Create Bootable Image:
    ; nasm -f bin boot-hello.asm -o boot-hello.bin
    ; dd if=boot-hello.bin of=/dev/sdX bs=512 count=1
    ; Replace /dev/sdX with the appropriate device name for your USB drive
    ; After writing the bootloader to the USB drive, you can boot from it to see the "Hello World" message displayed on the screen.

    ;to run in qemu:
    ;qemu-system-x86_64 -drive format=raw,file=boot-hello.bin