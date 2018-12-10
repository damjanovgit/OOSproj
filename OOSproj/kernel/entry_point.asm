

[bits 16]
[global _start]
_start:
    
    call switch_to_pm
    
    jmp $
    
%include"kernel/gdt.asm"
%include"kernel/switch_to_pm.asm"

[bits 32]

[extern kernel_main]
BEGIN_PM:

    call kernel_main
    
    jmp $
    
%include"kernel/int_setup/isr_list.asm"
%include"kernel/int_setup/irq_list.asm"
%include"kernel/int_setup/remap_PIC.asm"
%include"kernel/get_time/get_time.asm"
%include"kernel/keyboard/get_char.asm"
