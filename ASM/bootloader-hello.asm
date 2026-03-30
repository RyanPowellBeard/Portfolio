[org 0x7c00]    ;The BIOS loads the boot sector at address 0x7c00  

bits 16              ;Tell NASM to generate 16-bit real mode code

start:
    jmp main          ; Jump to the main code to avoid any issues with the bootloader being too small  

; -------------------Main Code------------------
main:
    ;Set up data segment and stack segment
    xor ax, ax        ; Clear the AX register
    mov ds, ax        ; Set the data segment to 0
    mov es, ax        ; Set the extra segment to 0
    mov ss, ax        ; Set the stack segment to 0
    mov sp, 0x7c00    ; Set the stack pointer to the end of the boot sector, stack grows downwards

    ; Bootloader code starts here

    ;----Greeting Message ----
    mov si, GreetingMessage ; Load the address of the greeting message into SI
    call PrintString          ; Call the PrintString function to display the greeting message

    ;----New Line ----
    mov si, newline ; Load the address of the newline string into SI
    call PrintString          ; Call the PrintString function to print a new line

    ;----Prompt for User Input ----
    mov si, EnterMessage_to_Bootloader ; Load the address of the input prompt message into SI
    call PrintString          ; Call the PrintString function to display the input prompt message

    ;----Read User Input ----
    mov di, inputBuffer ; Load the address of the input buffer into DI
    call ReadString           ; Call the ReadString function to read user input into the buffer

    ;----New Line ----
    mov si, newline ; Load the address of the newline string into SI
    call PrintString          ; Call the PrintString function to print a new line

    ;----Echo User Input ----
    ; Echo the message "You entered: " followed by the user input
    mov si, EchoMessage ; Load the address of the echo message into SI
    call PrintString          ; Call the PrintString function to display the echo message

    
    ;-- Print the user input back to the screen
    mov si, inputBuffer ; Load the address of the input buffer into SI
    call PrintString    ; Call the PrintString function to display the user input

    ;----New Line ----
    mov si, newline ; Load the address of the newline string into SI
    call PrintString          ; Call the PrintString function to print a new line

    ;Halt
    cli               ; Clear interrupts to prevent further issues
    hlt               ; Halt the CPU
    jmp $            ; Infinite loop to keep the CPU halted (jumps to the current address)



;mov di, inputBuffer ; Load the address of the input buffer into DI

; ------------------Functions------------------
PrintString:
    pusha            ; Save all registers on the stack
    .print_loop:
        lodsb           ; Load the next byte from the string into AL and increment SI
        cmp al, 0       ; Check if the byte is null (end of string)
        je .done        ; If it is null, we are done printing
        mov ah, 0x0e    ; Teletype output function for BIOS interrupt 0x10
        int 0x10        ; Call BIOS interrupt to print the character in AL
        jmp .print_loop       ; Repeat for the next character
    .done:
    popa             ; Restore all registers from the stack
    ret              ; Return from the function
ReadString:
    pusha            ; Save all registers on the stack

    ; Do not mov bx, di, unless we wand to user BX for something else
    ;mov bx, di      ; Load the address of the input buffer into BX
    .read_loop:
        mov ah, 0x00    ; BIOS function to read a character from the keyboard
        int 0x16        ; Call BIOS interrupt to read a character for keypress AL = ASCII character

        cmp al, 0x0D    ; Check if the character is Enter (carriage return)
        je .done        ; If it is Enter, we are done reading input

        stosb           ; Store the character in AL into the buffer at ES:DI and increment DI (instead of mov [di], al; inc di)

        ; Echo the character so the user sees what they are typing
        mov ah, 0x0e    ; Teletype output function for BIOS interrupt 0x10
        int 0x10        ; Call BIOS interrupt to print the character
        jmp .read_loop  ; Continue reading input until Enter is pressed
    .done:
        mov byte [di], 0 ; Null-terminate the input string in the buffer, at di(the end) not dx (the beginning)
    popa             ; Restore all registers from the stack
    ret              ; Return from the function

; -------------------Data Section------------------
GreetingMessage db 'Hello from the Bootloader!', 0 ; Null-terminated string for greeting message
EnterMessage_to_Bootloader db 'Enter a message to display: ', 0 ; Null-terminated string for input prompt
EchoMessage db 'You entered: ', 0 ; Null-terminated string for echo message
newline db 0x0D, 0x0A, 0 ; Carriage return and line feed for new line

; using a simple buffer to store user input, you can adjust the size as needed
inputBuffer db 100 dup(0) ; Buffer to store user input (100 bytes in this case)


;------------------Bootloader Footer------------------

; Fill the rest of the bytes with zeros to make the total size of the boot sector 512 bytes
times 510-($-$$) db 0 ; Fill the rest of the bytes with zeros to make the total size of the boot sector 512 bytes
dw 0xAA55           ; Boot signature (0xAA55) at the end of the boot sector (required for the BIOS to recognize it as a valid bootloader)

; -------------------Instructions to Assemble and Create Bootable Image------------------
    ; To Assemble and Create Bootable Image:
    ; nasm -f bin bootloader-hello.asm -o bootloader-hello.bin
    ; dd if=bootloader-hello.bin of=/dev/sdX bs=512 count=1
    ; Replace /dev/sdX with the appropriate device name for your USB drive

    ;to run in qemu:
    ;qemu-system-x86_64 -drive format=raw,file=bootloader-hello.bin