#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "lcd.h"
#include "math.h"
unsigned char satirsayisi;
extern unsigned char satirr;



void otuzhexgonder()
{
    SysCtlDelay(50000);
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, 0x30);
    GPIOPinWrite(LCDPORT, E, 2); // rs=0
    SysCtlDelay(200);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0
}

void lcdilkayarlar(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // portb aktif
    GPIOPinTypeGPIOOutput(LCDPORT, 0xFF); // butun pinler output

    GPIOPinWrite(LCDPORT, rs, 0); // rs=0
    otuzhexgonder();
    otuzhexgonder();
    otuzhexgonder();

    SysCtlDelay(50000);

    ////////////////////////////////////////////////////
    // burayý 07.11.2020 de ekledim
    GPIOPinWrite(LCDPORT, d4 | d5 | d6 | d7,  0x20 );
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(200);
    GPIOPinWrite(LCDPORT, E, 0x00);
    SysCtlDelay(50000);
    ////////////////////////////////////////////////////

    // dl=0 4 bit
    //lcdfonksiyonayarla(4,2,) bu fonksiyonu yaz
    // normalde LcdKomut(0x28); // dl=0 4 bit --- N=1 2 satýr --- F=0 5x7 lcd
    // olmasý gerekirdi.
    lcdfonksiyonayarla(4,satirr,0);
    //satir DL,N=1 >2 satir  N=0 >1 satir
 //   LcdKomut(0x28);
    LcdKomut(0x0C); // D=1, C=1, B=1
    LcdKomut(0x06); // i/d=1 , s=0
    LcdKomut(0x01); // ekran sil
}

void LcdKomut (unsigned char c)
{
    GPIOPinWrite(LCDPORT, rs, 0); // rs=0
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0xF0));
    GPIOPinWrite(LCDPORT, E, 2); // rs=0
    SysCtlDelay(2000);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0

    SysCtlDelay(50000); // yeni deðiþtirdim

    GPIOPinWrite(LCDPORT, rs, 0); // rs=0
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0x0F)<<4);
    GPIOPinWrite(LCDPORT, E, 2); // rs=0
    SysCtlDelay(2000);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0

    SysCtlDelay(50000); // yeni ekledim
}

void LcdTemizle(void)
{
    LcdKomut(0x01);
}

void lcdfonksiyonayarla( unsigned char dl,unsigned char N,unsigned char F) // dl,N,F
{
//dl=4
    if (N==1 && F==1){
        LcdKomut(0x2C);
        satirsayisi=2;
    }
    else if(N==0 && F==1) {
        LcdKomut(0x24);
        satirsayisi=1;
    }
    else if(N==1 && F==0) {
        LcdKomut(0x28);
        satirsayisi=2;
        }
    else if(N==0 && F==0) {
        LcdKomut(0x20);
        satirsayisi=1;
        }


    // dl için ya 4 yada 8
    // N için 1 için 1 satýra, 2 gelirse 2 satýr
    // F için 7 gelise 5x7 fontu
       // eðer 10 gelirse de 5x10 fonutunu
}


void lcdyaz(unsigned char c)
{
    GPIOPinWrite(LCDPORT, rs, 0x01); // rs=0
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0xF0));
    GPIOPinWrite(LCDPORT, E, 0x02); // rs=0
    SysCtlDelay(200);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0

    SysCtlDelay(500);

    GPIOPinWrite(LCDPORT, rs, 0x01); // rs=0
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0x0F)<<4);
    GPIOPinWrite(LCDPORT, E, 0x02); // rs=0
    SysCtlDelay(200);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0

    SysCtlDelay(500);

}

void lcdgotoxy(unsigned char x)
{
    // x=1 y=5 derse 84h olacak kodu
    // rs=0

    GPIOPinWrite(LCDPORT, rs, 0); // rs=0
        GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (x & 0xF0));
        GPIOPinWrite(LCDPORT, E, 0x02); // rs=0
        SysCtlDelay(200);
        GPIOPinWrite(LCDPORT, E, 0); // rs=0

        SysCtlDelay(500);

        GPIOPinWrite(LCDPORT, rs, 0); // rs=0
        GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (x & 0x0F)<<4);
        GPIOPinWrite(LCDPORT, E, 0x02); // rs=0
        SysCtlDelay(200);
        GPIOPinWrite(LCDPORT, E, 0); // rs=0

        SysCtlDelay(500);
}
