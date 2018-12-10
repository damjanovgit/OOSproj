

[org 0x7c00]
KERNEL_OFFSET  equ 0x1000   ; location for loading kernel
    
    
    mov ah,0x00
    mov al,0x13;video memory 0xa0000, 320x240 
    int 0x10
    
    mov [BOOT_DRIVE], dl ; boot drive

    ;mov bp, 0x9000        
    ;mov sp, bp

    mov bx,KERNEL_OFFSET;loading address
    mov cl,0x02;from sector
    call load_from_disk
    
    do:
        add bx,0x1e00;+512 bytes
        add cl,0x0f;from sector
        
        call load_from_disk
        
        cmp cl,0xf0;load a lot of sectors
        jle do
          
    call KERNEL_OFFSET   
    
    jmp $

load_from_disk:

    ;mov bx, KERNEL_OFFSET
    mov ah, 0x02     
    mov al, 15    
    
    mov ch, 0x00     
    mov dh, 0x00     
    ;mov cl, 0x02     
    int 0x13  
    
    ret
    
BOOT_DRIVE db 0

times  510-($-$$) db 0
dw 0xaa55