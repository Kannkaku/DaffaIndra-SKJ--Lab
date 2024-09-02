section .data           ; variable for the program
    num1 dw 5           ; create a variable named num1, define word, reserves 2 bytes (16 bits) in memory for the variable num1 and initializes it with the value 5.
    num2 dw 10          ; same thing as above
    result dw 0

section .text           ; code part/segment
    global _start       ; global makes the _start label accessible to the linker as the entry point of the program. This is where the execution begins.

_start:                 ; his label marks the entry point of the program. The colon (:) indicates that it’s a label, not an instruction.
    mov ax, [num1]      ; moves num1 value to accumulator
    imul ax, [num2]     ; multiply accumulator with num2 value
    mov [result], ax    ; store accumulator value to result

; Exit the program
    mov eax, 1          ; moves the value 1 into the EAX register. In Linux systems, this is the system call number for exit.
    xor ebx, ebx        ; performs a XOR between EBX and itself, which effectively sets EBX to 0. EBX holds the exit status. The program will exit with a status of 0 (typically meaning success).
    int 0x80            ; the interrupt instruction that triggers a system call in Linux. The value in EAX determines which system call to execute. EAX contains 1, it invokes the exit system call, terminates the program.