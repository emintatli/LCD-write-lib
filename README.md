# LCD-write-lib
An LCD library which you can easily set the row, text place, and your text


Usage:


                     
                     extern unsigned char satirsayisi;
                     unsigned char satirr=1;  // row set 1= 2nd row 0 is first row

                     while(1){
                     lcdilkayarlar();  // init settings

                     lcdgotoxy(0xC7);  // set the text coordinates
                     lcdyaz('A');    //the text which is gonna display on lcd


                }
