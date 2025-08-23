global function
section .text
function:
    push ebp
    mov  ebp, esp
    sub  esp, 12
    mov eax,1
.Lret_1:
    mov  esp, ebp
    pop  ebp
    ret
global function1
section .text
function1:
    push ebp
    mov  ebp, esp
    sub  esp, 8
    push WORD PTR [ebp-8]
    push WORD PTR [ebp+8]
    call function
    add esp, 8
    push eax
.Lret_2:
    mov  esp, ebp
    pop  ebp
    ret
