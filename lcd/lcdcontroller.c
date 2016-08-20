/*
 * lcd.c:
 *     Simple program to send a string to the LCD 
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define LCD_E 24
#define LCD_RS 25
#define LCD_D4 23
#define LCD_D5 22
#define LCD_D6 21
#define LCD_D7 14

void pulseEnable ()
{
   digitalWrite (LCD_E, HIGH) ; 
   delay(0.5); //  1/2 microsecond pause - enable pulse must be > 450ns
   digitalWrite (LCD_E, LOW) ; 
}

/*
  send a byte to the lcd in two nibbles
  before calling use SetChrMode or SetCmdMode to determine whether to send character or command
*/
void lcd_byte(char bits)
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

void SetCmdMode() 
{
  digitalWrite (LCD_RS, 0); // set for commands
}

void SetChrMode() 
{
  digitalWrite (LCD_RS, 1); // set for characters
}

void lcd_text(char *s)
{
  while(*s) 
   lcd_byte(*s++);
 }

void lcd_gotoxy(unsigned char x, unsigned char y)
{
  unsigned char firstCharAdr[]={0x80,0xC0};
  lcd_byte(firstCharAdr[y-1] + x - 1);
}


void lcd_init()
{
   wiringPiSetup() ; // use BCIM numbering
   // set up pi pins for output
   pinMode (LCD_E,  OUTPUT);
   pinMode (LCD_RS, OUTPUT);
   pinMode (LCD_D4, OUTPUT);
   pinMode (LCD_D5, OUTPUT);
   pinMode (LCD_D6, OUTPUT);
   pinMode (LCD_D7, OUTPUT);
   
   // initialise LCD
   SetCmdMode(); // set for commands
   lcd_byte(0x33); // full init 
   lcd_byte(0x32); // 4 bit mode
   lcd_byte(0x28); // 2 line mode
   lcd_byte(0x0C); // display on, cursor off, blink off
   lcd_byte(0x01);  // clear screen
   delay(3);        // clear screen is slow!
}

int main (int argc, char *argv []) 
{
  lcd_init();
  
  SetChrMode(); 
  lcd_text("hello world!");
  SetCmdMode();
  lcd_gotoxy(1,2);
  SetChrMode();
  lcd_text("Luis");
  return 0 ;
}
