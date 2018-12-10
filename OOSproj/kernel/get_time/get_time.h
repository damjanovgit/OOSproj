

#ifndef GET_TIME_H
#define GET_TIME_H
    
    typedef struct Time{
     short hour;
     short minute;
     short second;
    }Time;
    
    extern void do_bcd();
    extern short get_seconds();
    extern short get_minutes();
    extern short get_hours();
    
    Time getGrinichTime();
    Time getLocalTime();
    void printTime(int x,int y);
    
    void printExistingTime(int x,int y,Time time);
#endif