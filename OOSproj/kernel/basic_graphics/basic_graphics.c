
#include"basic_graphics.h"

#include"font.h"

#define LETTER_SPACING 10

char* const VIDEO_MEMORY=(char*)0xa0000;

void printChar(int x,int y,unsigned char ch,Color color){
    static char once=0;
    if(once==0){//ili se seti da ovo inicijalizujes
        initLetterHash();
        once=1;   
    }
    
    unsigned char* gch=letterHash[ch];
    int posx=x;
    int posy=y;
    
    
    for(int i=0;i<13;i++){
        posy=y*WINDOW_WIDTH+(12-i)*WINDOW_WIDTH;
        for(int j=0;j<8;j++){
            posx=x+j;
            if((gch[i]<<j)&0x80)
                *(VIDEO_MEMORY+posy+posx)=color;
        }
    }
}
void printString(int x,int y,unsigned char* str,Color color){
    int i=0;
    
    int posx=x;
    while(str[i]!=0){
        printChar(posx,y,str[i],color);
        i++;
        posx+=LETTER_SPACING;
    }
}
void printPixel(int x,int y,Color color){
    *(VIDEO_MEMORY+y*WINDOW_WIDTH+x)=color;
}
void printRectangle(int x1,int y1,int x2,int y2,Color color){
    for(int i=y1;i<=y2;i++){
     for(int j=x1;j<=x2;j++){
        *(VIDEO_MEMORY+i*WINDOW_WIDTH+j)=color;
     }
    }
}
void printCircle(int x,int y,int r,Color color){
    printPixel(x,y,WHITE);
    for(int i=y-r;i<=y+r;i++){
     for(int j=x-r;j<=x+r;j++){
        if((i-y)*(i-y)+(j-x)*(j-x)<=r*r){
            *(VIDEO_MEMORY+i*WINDOW_WIDTH+j)+=color;
        }
     }
    }
}
/*
void printLine(int x1,int y1,int x2,int y2,Color color){
    //TO DO: Bresenhams line drawing algorithm
    
    if(x1>x2){int a;a=x1;x1=x2;x2=a;a=y1;y1=y2;y2=a;}
    double k=(y2-y1)/(x2-x1);
    double b=y1-k*x1;
    for(int i=x1;i<=x2;i++){
     *(VIDEO_MEMORY+i*320+i)=color;   
    }
}
*/