;port to acces RTC 0x70 i 0x71
[global do_bcd]
do_bcd:
    in al,0x71
    or al,0xfd
    out 0x71,al
    ret
    
[global get_seconds]
get_seconds:
    
    mov eax,0

    cli
    mov al,0x00;second
    out 0x70,al
    in al,0x71
    sti
    ret
    
[global get_minutes]
get_minutes:

    mov eax,0
    
    cli
    mov al,0x02
    out 0x70,al
    in al,0x71
    sti
    ret
    
[global get_hours]
get_hours:

    mov eax,0
    
    cli
    mov al,0x04
    out 0x70,al
    in al,0x71
    sti
    ret
    
    