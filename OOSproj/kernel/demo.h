
#ifndef DEMO_H
#define DEMO_H

#include"basic_graphics/basic_graphics.h"
#include"keyboard/keyboard.h"
#include"get_time/get_time.h"

typedef struct FlyObj{
    int rad;
    int posx,posy;
    char xinc;
    char yinc;
    Color color;
}FlyObj;

typedef struct Player{
    
    short x;
    short y;
    short xspeed;
    short yspeed;
}Player;

#define MAX_NUM_FLYOBJ 50
int numFlyObj=0;

FlyObj flyObj[MAX_NUM_FLYOBJ]={0};

int pseudoRand(int num){
 static unsigned char r=0;
 return ((r++*7+5)*13)%num;

}

Player player;
void printPlayer(void){
    printRectangle(player.x-3,player.y-3,player.x+3,player.y+3,CYAN);
}

Time time;

char game_over=0;
void updatePlayer(void){
    char ch=getCommand();
    if(ch==UP_ARROW) player.yspeed--;
    if(ch==DOWN_ARROW) player.yspeed++;
    if(ch==LEFT_ARROW) player.xspeed--;
    if(ch==RIGHT_ARROW) player.xspeed++;
    if(ch==0) player.xspeed=player.yspeed=0;
    
    if(player.xspeed>5) player.xspeed=5;
    if(player.yspeed>5) player.yspeed=5;
    if(player.xspeed<-5) player.xspeed=-5;
    if(player.yspeed<-5) player.yspeed=-5;
    
    player.x+=player.xspeed;
    player.y+=player.yspeed;
    
    if(player.x>315) player.x=315;
    if(player.x<5) player.x=5;
    if(player.y<5) player.y=5;
    if(player.y>195) player.y=195;
    
    for(int i=0;i<numFlyObj;i++){
     if((player.x-flyObj[i].posx)*(player.x-flyObj[i].posx)+
         (player.y-flyObj[i].posy)*(player.y-flyObj[i].posy)<flyObj[i].rad*flyObj[i].rad){
     
        numFlyObj=0;
        game_over=1;
     }
    }
}

void printFlyObjs(void){
    for(int i=0;i<numFlyObj;i++){
     printCircle(flyObj[i].posx,flyObj[i].posy,flyObj[i].rad,flyObj[i].color);   
    }
}

void updateFlyObj(int index){
    if(flyObj[index].xinc==0){
     flyObj[index].posx++;
     if(flyObj[index].posx+flyObj[index].rad>=WINDOW_WIDTH-1) flyObj[index].xinc=1;  
    }
    else{
     flyObj[index].posx--;
     if(flyObj[index].posx-flyObj[index].rad<=1) flyObj[index].xinc=0;  
    }
    
    if(flyObj[index].yinc==0){
     flyObj[index].posy++;
     if(flyObj[index].posy+flyObj[index].rad>=WINDOW_HEIGHT-1) flyObj[index].yinc=1;  
    }
    else{
     flyObj[index].posy--;
     if(flyObj[index].posy-flyObj[index].rad<=1) flyObj[index].yinc=0;  
    }
}

void updateAllFlyObjs(void){
    for(int i=0;i<numFlyObj;i++){
        updateFlyObj(i);
    }
}

void createFlyObj(void){
    if(numFlyObj>=MAX_NUM_FLYOBJ) return;
    flyObj[numFlyObj].rad=20;
    flyObj[numFlyObj].xinc=pseudoRand(time.second)%2;
    flyObj[numFlyObj].yinc=pseudoRand(time.second+pseudoRand(13))%2;
    flyObj[numFlyObj].posx=pseudoRand(317)%320;
    flyObj[numFlyObj].posy=pseudoRand(173)%200;
    flyObj[numFlyObj].color=pseudoRand(17)%15;
    
    numFlyObj++;
}

void doBackground(void){
    printRectangle(0,0,340,240,BLUE);
    printString(10,20,(unsigned char*)"You can enter,",LIGHT_GREY);
    printString(10,40,(unsigned char*)"but you can never leave.",LIGHT_GREY);
    printString(10,60,(unsigned char*)"What am I?",LIGHT_GREY);
    
}

int cmdLen=0;
char cmdString[BUFFER_LENGTH]={0};
void doCommandLine(){
    printRectangle(0,180,320,200,BLACK);
    printRectangle(1,181,318,198,LIGHT_BLUE);
    printString(5,185,cmdString,WHITE);
}

void printAll(void){
    doBackground();
    printExistingTime(230,0,time);
    doCommandLine();
    
    printFlyObjs();
    printPlayer();
    
    if(game_over){
     printString(100,100,"GAME OVER",BLACK);   
    }
}


char strcmp(char *str1,char *str2){
    int count=0;
    while(str1[count]!=0&&str2[count]!=0&&str1[count]==str2[count]) count++;
    if(str1[count]==0&&str2[count]!=0) return 0;
    if(str2[count]==0&&str1[count]!=0) return 0;   
    if(str1[count]!=str2[count]) return 0;
    return 1;
}

void getInstruction(void){
    getBuffer(cmdString,&cmdLen);
    if(cmdLen==0) return;
    if(cmdString[cmdLen-1]=='\n') {
        cmdString[cmdLen-1]=0;
        if(strcmp(cmdString,"circle"))
            createFlyObj();
        if(strcmp(cmdString,"remove"))
            if(numFlyObj>0)
            numFlyObj--;
        if(strcmp(cmdString,"remove-all"))
            numFlyObj=0;
        if(strcmp(cmdString,"start")){
            game_over=0;
            for(int i=0;i<5;i++){
                createFlyObj();
            }
        }
        flushBuffer();
    }
    
}

#endif
