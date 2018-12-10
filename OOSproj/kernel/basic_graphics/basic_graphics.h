

#ifndef BASIC_GRAPHICS_H
#define BASIC_GRAPHICS_H

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 200
//Borders are not checked, keep that in mind

typedef enum Color{

    BLACK=0,
    BLUE=1,
    GREEN=2,
    CYAN=3,
    RED=4,
    MAGENTA=5,
    BROWN=6,
    LIGHT_GREY=7,
    DARK_GREY=8,
    LIGHT_BLUE=9,
    LIGHT_GREEN=10,
    LIGHT_CYAN=11,
    LIGHT_RED=12,
    LIGHT_MAGENTA=13,
    YELLOW=14,
    WHITE=15
}Color;

void printChar(int x,int y,unsigned char ch,Color color);
void printString(int x,int y,unsigned char *str,Color color);
void printPixel(int x,int y,Color color);
void printRectangle(int x1,int y1,int x2,int y2,Color color);
void printCircle(int x,int y,int r,Color color);
//void printLine(int x1,int y1,int x2,int y2,Color color);

//void clearScreen(Color color);

#endif