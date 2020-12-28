#include"inc/tm4c123gh6pm.h"
#include "stdint.h"
#include "lcd.h"
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "math.h"
extern unsigned char satirsayisi;
unsigned char satirr=1;  // 1 yapýlýrsa 2 satýr ayarlanýr 0 yapýlýrsa tek satýra
int main(void)
{

    while(1){
                     lcdilkayarlar();

                     lcdgotoxy(0xC7);
                     lcdyaz('A');


                }

    }

