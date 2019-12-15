bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen
extern fread
extern printf
extern fclose

import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    numefisier db 'fisier.txt', 0
    modacces db 'r', 0
    format db '%d', 0
    descriptor dd -1
    len equ 100
    sir times len db 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword modacces
        push dword numefisier
        call [fopen]
        add esp, 4*2
        mov [descriptor], eax
        cmp eax, 0
        je final
        
        push dword [descriptor]
        push dword len
        push dword 1
        push dword sir
        call [fread]
        add esp, 4*4
        
        mov esi, 0
        mov ecx, eax
        Repeta:
            mov al, byte[sir+esi]
            cmp al, ' '
            je finalRep
            sub al, 48
            cbw
            mov bl, 2
            idiv bl
            cmp ah, 0
            je par
            jmp finalRep
            par:
                inc edx
            finalRep:    
                inc esi
        loop Repeta
        
        push dword edx
        push dword format
        call [printf]
        add esp, 4*2
        
        push dword [descriptor]
        call [fclose]
        add esp, 4
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
