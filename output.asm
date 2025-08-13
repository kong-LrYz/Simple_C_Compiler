global function
section .text
function:
    push ebp
    mov  ebp, esp
    sub  esp, 28
.Lret_1:
    mov  esp, ebp
    pop  ebp
    ret
global function1
section .text
function1:
    push ebp
    mov  ebp, esp
    sub  esp, 28
.Lret_2:
    mov  esp, ebp
    pop  ebp
    ret
