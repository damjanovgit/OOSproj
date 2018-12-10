

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include"../int_setup/int_setup.h"

#define BUFFER_LENGTH 255

#define UP_ARROW 26
#define LEFT_ARROW 27
#define RIGHT_ARROW 28
#define DOWN_ARROW 29

extern int get_char();

void keyboard_handler(struct regs *r);
char getChar();
char getCharNoWait();
void getBuffer();
void flushBuffer();

char getCommand(void);

#endif