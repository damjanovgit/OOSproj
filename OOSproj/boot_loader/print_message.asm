
print_message:

    pusha
    
    mov ah,0x0e

    here:
        
        mov al,[bx]
        cmp al,0
        je prm_done
        
        int 0x10
        
        add bx,1
        
        jmp here
    
    prm_done:
        popa
        ret
    