
#include"basic_graphics/basic_graphics.h"
#include"int_setup/int_setup.h"
#include"get_time/get_time.h"
#include"keyboard/keyboard.h"
//#include"allocation/allocate.h"


#include"demo.h"//Time and cmdString are in here

volatile char tick=0;
int count=0;

void timer_handler(regs* r){
    count++;
    if(count%10==0){
     time=getLocalTime();
     count=0;
    }
    
    updatePlayer();
    tick=1;
}

void  kernel_main() {
    setIDT();
    irq_install_handler(0, timer_handler);
    irq_install_handler(1, keyboard_handler);
    
    player.x=50;
    player.y=50;
    for(;;){
        if(tick==1){
            
            getInstruction();
            
            updateAllFlyObjs();
            printAll();
            tick=0;
        }   
    }
}