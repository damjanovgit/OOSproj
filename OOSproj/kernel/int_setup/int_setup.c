
#include"int_setup.h"
#include"../basic_graphics/basic_graphics.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

extern void remap_PIC();
extern void enable_int();
extern void sigPIC1();
extern void sigPIC2();

void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void myFunc(regs* r){ 
    static int i=0,col=0;
    if(i%100) col=(col+1)%16;
    printString(10,i=(i+10)%200,(unsigned char*)"Unassigned interrupt",col);
    //enable_int();
}

void associateInt(int num,unsigned long base,unsigned short selector,unsigned char flags){
    
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel = selector;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

void setIDT(){
    
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&idt;
    
    for(int i=0;i<256;i++)
            associateInt(i, (unsigned)myFunc, 0x08, 0x8E);
    //memset(&idt, 0, sizeof(struct idt_entry) * 256);
        
    associateInt(0, (unsigned)isr0, 0x08, 0x8E);
    associateInt(1, (unsigned)isr1, 0x08, 0x8E);
    associateInt(2, (unsigned)isr2, 0x08, 0x8E);
    associateInt(3, (unsigned)isr3, 0x08, 0x8E);
    associateInt(4, (unsigned)isr4, 0x08, 0x8E);
    associateInt(5, (unsigned)isr5, 0x08, 0x8E);
    associateInt(6, (unsigned)isr6, 0x08, 0x8E);
    associateInt(7, (unsigned)isr7, 0x08, 0x8E);

    associateInt(8, (unsigned)isr8, 0x08, 0x8E);
    associateInt(9, (unsigned)isr9, 0x08, 0x8E);
    associateInt(10, (unsigned)isr10, 0x08, 0x8E);
    associateInt(11, (unsigned)isr11, 0x08, 0x8E);
    associateInt(12, (unsigned)isr12, 0x08, 0x8E);
    associateInt(13, (unsigned)isr13, 0x08, 0x8E);
    associateInt(14, (unsigned)isr14, 0x08, 0x8E);
    associateInt(15, (unsigned)isr15, 0x08, 0x8E);

    associateInt(16, (unsigned)isr16, 0x08, 0x8E);
    associateInt(17, (unsigned)isr17, 0x08, 0x8E);
    associateInt(18, (unsigned)isr18, 0x08, 0x8E);
    associateInt(19, (unsigned)isr19, 0x08, 0x8E);
    associateInt(20, (unsigned)isr20, 0x08, 0x8E);
    associateInt(21, (unsigned)isr21, 0x08, 0x8E);
    associateInt(22, (unsigned)isr22, 0x08, 0x8E);
    associateInt(23, (unsigned)isr23, 0x08, 0x8E);

    associateInt(24, (unsigned)isr24, 0x08, 0x8E);
    associateInt(25, (unsigned)isr25, 0x08, 0x8E);
    associateInt(26, (unsigned)isr26, 0x08, 0x8E);
    associateInt(27, (unsigned)isr27, 0x08, 0x8E);
    associateInt(28, (unsigned)isr28, 0x08, 0x8E);
    associateInt(29, (unsigned)isr29, 0x08, 0x8E);
    associateInt(30, (unsigned)isr30, 0x08, 0x8E);
    associateInt(31, (unsigned)isr31, 0x08, 0x8E);
    
    remap_PIC();
    
    associateInt(32, (unsigned)irq0, 0x08, 0x8E);
    associateInt(33, (unsigned)irq1, 0x08, 0x8E);
    associateInt(34, (unsigned)irq2, 0x08, 0x8E);
    associateInt(35, (unsigned)irq3, 0x08, 0x8E);
    associateInt(36, (unsigned)irq4, 0x08, 0x8E);
    associateInt(37, (unsigned)irq5, 0x08, 0x8E);
    associateInt(38, (unsigned)irq6, 0x08, 0x8E);
    associateInt(39, (unsigned)irq7, 0x08, 0x8E);

    associateInt(40, (unsigned)irq8, 0x08, 0x8E);
    associateInt(41, (unsigned)irq9, 0x08, 0x8E);
    associateInt(42, (unsigned)irq10, 0x08, 0x8E);
    associateInt(43, (unsigned)irq11, 0x08, 0x8E);
    associateInt(44, (unsigned)irq12, 0x08, 0x8E);
    associateInt(45, (unsigned)irq13, 0x08, 0x8E);
    associateInt(46, (unsigned)irq14, 0x08, 0x8E);
    associateInt(47, (unsigned)irq15, 0x08, 0x8E);
    
    idt_load();
    enable_int();
}

void handle_int(regs* r){
    printString(10,60,(unsigned char*)"Interrupt happened",YELLOW);
    printChar(10,80,(unsigned char)(r->int_no+0x30),YELLOW);
    while(1);
}

void irq_handler(struct regs *r)
{
    void (*handler)(struct regs *r);

    handler = irq_routines[r->int_no - 32];
    
    if (handler)
    {
        handler(r);
    }

    if (r->int_no >= 40)
    {
        sigPIC2();
    }
    
    sigPIC1();
}