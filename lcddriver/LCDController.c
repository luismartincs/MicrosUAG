#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "Timer.h"

#define LCD_E 24
#define LCD_RS 25
#define LCD_D4 23
#define LCD_D5 22
#define LCD_D6 21
#define LCD_D7 14
#define LED 13

unsigned char ledTaskID;
unsigned char counterTaskID;
unsigned char lcdUpdateTaskID;

unsigned char led_status = 0;
unsigned char count = 0;

//================Controlador LCD ==============

//========== Enviar nibble por nibble ==========

void pulseEnable(){ 
   digitalWrite (LCD_E, HIGH) ; 
   usleep(150); 
   digitalWrite (LCD_E, LOW) ;
}

void sendByte(char bits)
{
  digitalWrite (LCD_D4,(bits & 0x10)) ;  
  digitalWrite (LCD_D5,(bits & 0x20)) ;  
  digitalWrite (LCD_D6,(bits & 0x40)) ;  
  digitalWrite (LCD_D7,(bits & 0x80)) ;  
  pulseEnable();

  digitalWrite (LCD_D4,(bits & 0x1)) ;  
  digitalWrite (LCD_D5,(bits & 0x2)) ;  
  digitalWrite (LCD_D6,(bits & 0x4)) ;  
  digitalWrite (LCD_D7,(bits & 0x8)) ;  
  pulseEnable();         
}

void sendText(char *s)
{
  while(*s) 
   sendByte(*s++);
}

void goToXY(unsigned char x, unsigned char y)
{
  unsigned char firstCharAdr[]={0x80,0xC0};
  sendByte(firstCharAdr[y-1] + x - 1);
}

//========== Modos de operacion ================

void setCmdMode(void) 
{
  digitalWrite (LCD_RS, 0);
}

void setChrMode(void) 
{
  digitalWrite (LCD_RS, 1);
}

//======== Estados para inicializar ============

void start(void){
    sendByte(0x33);
}

void setMode(void){
    sendByte(0x32);
}

void setLine(void){
    sendByte(0x28);
}

void setDisplay(void){
    sendByte(0x0C);
}

void setClear(void){
    sendByte(0x01);
}

void end(void){
    usleep(2000);
}

void updateText(void){
   char str[16];
   sprintf(str,"Contador:%i",count);
   sendText(str);
}

void (* lcd_states[])(void) =
{
        setCmdMode,
	start,
	setMode,
	setLine,
	setDisplay,
	setClear,
	end
};

void (* write_string[])(void) =
{
	setCmdMode,
	setClear,
	end,
	setChrMode,
	updateText
};

void lcd_init(){
    unsigned char i = 0;
    for(i=0; i < 7; i++){
       lcd_states[i]();
    }
}

//==========================

void ledTask(){
   led_status = !led_status;
   digitalWrite(LED,led_status);
}

void counterTask(){
    count++;
}

void lcdTask(){

   unsigned char i = 0;
   for (i=0; i < 5; i++){
    write_string[i]();
   }
}

void init(){

   wiringPiSetup();
   pinMode (LCD_E,  OUTPUT);
   pinMode (LCD_RS, OUTPUT);
   pinMode (LCD_D4, OUTPUT);
   pinMode (LCD_D5, OUTPUT);
   pinMode (LCD_D6, OUTPUT);
   pinMode (LCD_D7, OUTPUT);
   pinMode(LED,OUTPUT);

   lcd_init();

   ledTaskID = getTimer(1000,1000,1);
   counterTaskID = getTimer(1000,1000,1);
   lcdUpdateTaskID = getTimer(250,250,1);

   setCallBack(ledTaskID,&ledTask);
   setCallBack(counterTaskID,&counterTask);
   setCallBack(lcdUpdateTaskID,&lcdTask);

   startTimers(); 
}


int main(int argc, char const *argv[])
{

	init();
	return 0;
}
