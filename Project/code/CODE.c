#include <16f877a.h>//Including header file for uc
#fuses XT,NOWDT//Configuring fuses
#use delay(clock=4000000)//Including use directive
#include <lcd.c> //LCD library
#include <math.h>//Including math library

//Configuring ADC registers
#byte adresh=0x1e
#byte adresl=0x9e
#byte adcon0=0x1f
#byte adcon1=0x9f

int16 rd_adc();//Defining function of 16 bit analog to digital conversion
//Main body of the program

void main()
{
   int16 x;//Declaring int variable of 16 bit
   set_tris_a(0xff);//Configuring port A as an input
   adcon0=0b01000000;//Moving binary literal value to adc register
   adcon1=0;//Moving decimal literal value to adc register

   lcd_init();         //Initializing lcd

   while(1)            //Infinite while loop
   { //Performing arithmetic operations and storing result in x variable
      x=rd_adc();
      x=(x/121);  
      printf(lcd_putc,"\fAC Voltages=%LUV",x);//Giving command to display float data on the lcd
      delay_ms(1900);//Giving command for delay
   }
}

int16 rd_adc()//Body of return type function
{
int16 value = 0;
bit_set(ADCON0,0);      //Turn on ADC
bit_set(ADCON0,2);      //Start AD Conversion
while(bit_test(ADCON0,2)){}    //wait untill conversion is done
value = make16(ADRESH,ADRESL);    //Read result
return value;        //return value
}

