global executeAs
executeAs:
push       rbp			; push the old base pointer onto the stack to save it for later
mov        rbp, rsp		; copy the value of the stack pointer to the base pointer
mov        eax, 15		; copy 15 into the general purpose register
pop        rbp			; pop the old basepointer of the stack
ret						; return