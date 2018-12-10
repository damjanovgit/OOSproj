


#include"keyboard.h"


volatile int filled=0;
volatile char kb_buffer[BUFFER_LENGTH];
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    UP_ARROW,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    LEFT_ARROW,	/* Left Arrow */
    0,
    RIGHT_ARROW,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    DOWN_ARROW,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

char command=0;

extern void disable_int();
extern void enable_int();

void keyboard_handler(struct regs *r){
    unsigned char code;

    code = get_char();

    if (!(code&0x80)){
        char ch=kbdus[code];
        if((ch>=UP_ARROW&&ch<=DOWN_ARROW)||ch==0){
         command=ch; 
         return;
        }
        if(ch=='\b'){
            if(filled!=0)
                kb_buffer[--filled]=0;
        }
        else{
            kb_buffer[filled++]=kbdus[code];
            if(filled>=BUFFER_LENGTH)
                filled=0;
        }
    }
}

char getCommand(void){
    return command;
}
char getChar(){
    
    while(filled==0);
    char ret;
    disable_int();
    ret=kb_buffer[filled-1];
    kb_buffer[--filled]=0;
    enable_int();
    return ret;
}
char getCharNoWait(){
    if(filled==0) return 0;
    char ret;
    disable_int();
    ret=kb_buffer[filled-1];
    kb_buffer[--filled]=0;
    enable_int();
    return ret;    
}
void getBuffer(char* buffer,int* len){
    *len=filled;
    int i;
    for(i=0;i<*len;i++)
        buffer[i]=kb_buffer[i];
    buffer[i]=0;
}
void flushBuffer(){
    filled=0;
    kb_buffer[filled]=0;
}