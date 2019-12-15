bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)

global CalculSuma
CalculSuma:
    mov ecx, [esp+4]; c
    mov ebx, [esp+8]; b
    mov eax, [esp+12]; a
    add ebx, eax
    sub ebx, ecx
ret