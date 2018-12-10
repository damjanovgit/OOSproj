

#ifndef INT_SETUP_H
#define INT_SETUP_H

typedef struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed)) idt_entry;

typedef struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) idt_ptr;

typedef struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
}regs;

extern void *irq_routines[16];

idt_entry idt[256];
idt_ptr idtp;

extern void idt_load();
void associateInt(int num,unsigned long base,unsigned short selector,unsigned char flags);
void setIDT();

void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);

#endif