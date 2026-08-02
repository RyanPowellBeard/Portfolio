; Stage Two: Load the second stage from disk and jump to it
[org 0x8000]   ; The second stage will be loaded at address 0x0000:0x8000 (segment:offset)
; The second stage code starts here
start:
    mov ah, 0x0e   ; Teletype output function for BIOS interrupt 0x10
    mov al, 'S'    ; Character 'S'
    int 0x10       ; Call BIOS interrupt to print 'S' Trigger Video Service Interrupt
    mov al, 'e'    ; Character 'e'
    int 0x10       ; Call BIOS interrupt to print 'e' Trigger Video Service Interrupt
    mov al, 'c'    ; Character 'c'
    int 0x10       ; Call BIOS interrupt to print 'c' Trigger Video Service Interrupt
    mov al, 'o'    ; Character 'o'
    int 0x10       ; Call BIOS interrupt to print 'o' Trigger Video Service Interrupt
    mov al, 'n'    ; Character 'n'
    int 0x10       ; Call BIOS interrupt to print 'n' Trigger Video Service Interrupt
    mov al, 'd'    ; Character 'd'
    int 0x10       ; Call BIOS interrupt to print 'd' Trigger Video Service Interrupt
    mov al, ' '    ; Character ' '
    int 0x10       ; Call BIOS interrupt to print ' ' Trigger Video Service Interrupt
    mov al, 'S'    ; Character 'S'
    int 0x10       ; Call BIOS interrupt to print 'S' Trigger Video Service Interrupt
    mov al, 't'    ; Character 't'
    int 0x10       ; Call BIOS interrupt to print 't' Trigger Video Service Interrupt
    mov al, 'a'    ; Character 'a'
    int 0x10       ; Call BIOS interrupt to print 'a' Trigger Video Service
    mov al, 'g'    ; Character 'g'
    int 0x10       ; Call BIOS interrupt to print 'g' Trigger Video Service
    mov al, 'e'    ; Character 'e'
    int 0x10       ; Call BIOS interrupt to print 'e' Trigger Video Service

    ; After printing the message, you can add more code here to perform additional tasks or simply halt the CPU
    cli             ; Clear interrupts to prevent further issues
    
    ; you could now load a kernel or perform other tasks before halting the CPU, or enter Protected Mode (32-bit) if you want to run more complex code here:
    jmp $          ; Infinite loop to prevent the second stage from exiting (jumps to the current address)

    times 510-($-$$) db 0 ; Fill the rest of the bytes with zeros to make the total size of the second stage 512 bytes
    dw 0xAA55           ; Boot signature (0xAA55) at the end of the second stage (not strictly necessary for the second stage, but included for consistency)

    ; To Assemble and Create Second Stage Image:
    ; nasm -f bin second_stage.asm -o second_stage.bin
    ; The second stage is loaded by the first stage, so you don't need to write it directly to the disk. Just make sure it's in the same directory as the first stage when you run the first stage, as the first stage will read it from the disk and load it into memory.
    ; After writing the first stage to the USB drive, you can boot from it to load the second stage from the disk and see the "Second Stage" message displayed on the screen.   
    ; To run in qemu:
    ; qemu-system-x86_64 -drive format=raw,file=first_stage.bin
    
    ; To combine both stages for linux/Mac 
    ; To assemble and create a combined image with both stages:
    ; cat first_stage.bin second_stage.bin > combined.bin
    ; qemu-system-x86_64 -drive format=raw,file=combined.bin