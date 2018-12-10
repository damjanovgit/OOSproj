
#include"get_time.h"
#include"../basic_graphics/basic_graphics.h"

Time getGrinichTime(){
    //------------------
    static char once=0;
    if(!once){
     do_bcd();
     once=1;
    }
    //------------------
    Time time;
    time.second=get_seconds();
    time.minute=get_minutes();
    time.hour=get_hours();
    
    time.second=(time.second>>4)*10+(time.second&0x0f);
    time.minute=(time.minute>>4)*10+(time.minute&0x0f);
    time.hour=(time.hour>>4)*10+(time.hour&0x0f);
    
    return time;
}
Time getLocalTime(){
    Time time=getGrinichTime();
    
    time.hour=(time.hour+2)%24;
    return time;
}
void printTime(int x,int y){
     Time time=getLocalTime();

     printRectangle(x,y,x+80,y+10,BLACK);
     
     printChar(x,y,time.hour/10+0x30,WHITE);
     printChar(x+10,y,time.hour%10+0x30,WHITE);
     printChar(x+20,y,':',WHITE);
     printChar(x+30,y,time.minute/10+0x30,WHITE);
     printChar(x+40,y,time.minute%10+0x30,WHITE);
     printChar(x+50,y,':',WHITE);
     printChar(x+60,y,time.second/10+0x30,WHITE);
     printChar(x+70,y,time.second%10+0x30,WHITE);   
        
}

void printExistingTime(int x,int y,Time time){
     printRectangle(x,y,x+80,y+10,BLACK);
     
     printChar(x,y,time.hour/10+0x30,WHITE);
     printChar(x+10,y,time.hour%10+0x30,WHITE);
     printChar(x+20,y,':',WHITE);
     printChar(x+30,y,time.minute/10+0x30,WHITE);
     printChar(x+40,y,time.minute%10+0x30,WHITE);
     printChar(x+50,y,':',WHITE);
     printChar(x+60,y,time.second/10+0x30,WHITE);
     printChar(x+70,y,time.second%10+0x30,WHITE);   
}
