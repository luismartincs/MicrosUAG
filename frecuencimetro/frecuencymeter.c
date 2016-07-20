#include <stdio.h>
#include <wiringPi.h>

#define DISP4 0
#define DISP3 7
#define DISP2 9
#define DISP1 8

#define LED1 27
#define LED2 26
#define LED3 6

#define F 25 
#define G 24
#define A 23
#define B 22
#define E 21
#define C 29
#define D 28

#define SIGNAL 4

#define BUTTON 5


unsigned char HOLD = 0;

//TASK COUNTERS

int task1 = 2500;
unsigned char t1s = 0;

int task2 = 5000;
unsigned char t2s = 0;

int task3 = 1250;
unsigned char t3s = 0;

int taskBtn = 500;
unsigned char lbtns = 1;

int lins = 1;
int counter = 0;

int displayUpdate = 20;

unsigned char display = 0;

unsigned char segments[] = {
			  F,G,A,B,E,C,D,
			  0,1,0,0,0,0,0,
	                  1,1,1,0,1,0,1,
			  1,0,0,0,0,1,0,
			  1,0,0,0,1,0,0,
			  0,0,1,0,1,0,1,
			  0,0,0,1,1,0,0,
			  0,0,0,1,0,0,0,
			  1,1,0,0,1,0,1,
			  0,0,0,0,0,0,0,
			  0,0,0,0,1,0,0,
			  1,0,1,1,1,1,1,
                  };

unsigned char displays[] = {DISP1,DISP2,DISP3,DISP4};
unsigned char displaysValue[] = {0,0,0,0};

//gcc -Wall -o blink blink.c -lwiringPi

void cleanGPIO(){

  digitalWrite(DISP1,LOW);
  digitalWrite(DISP2,LOW);
  digitalWrite(DISP3,LOW);
  digitalWrite(DISP4,LOW);

  digitalWrite(F,HIGH);
  digitalWrite(G,HIGH);
  digitalWrite(A,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(E,HIGH); 
  digitalWrite(C,HIGH);
  digitalWrite(D,HIGH);  

  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);

}

void setup(){
  wiringPiSetup();

  pinMode(DISP1,OUTPUT);
  pinMode(DISP2,OUTPUT);
  pinMode(DISP3,OUTPUT);
  pinMode(DISP4,OUTPUT);

  pinMode(F,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(E,OUTPUT); 
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);  

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(BUTTON,INPUT);
   
  cleanGPIO();
}

void showDigit(unsigned char display,unsigned char number){
 
 int i=0;
 number = number+1;

 digitalWrite(DISP1,LOW);
 digitalWrite(DISP2,LOW);
 digitalWrite(DISP3,LOW);
 digitalWrite(DISP4,LOW);


 digitalWrite(display,HIGH);

 for(i=0; i < 7; i++){ 
    digitalWrite(segments[i],segments[(7*number)+i]);
 }
	
}


int main (void){
   
  int cbtns = 1;
  int cins = 1;

  setup();

  for(;;){

	if(taskBtn == 0){
		cbtns = digitalRead(BUTTON);
		if(cbtns != lbtns){
			if(cbtns == 0){
				HOLD = !HOLD;
			}
		}
		lbtns = cbtns;
		taskBtn = 500;
	}

	if(task1 == 0){
		if(HOLD){		
		  t1s = !t1s;
		  digitalWrite(LED1,t1s);		
		}else{
		  digitalWrite(LED1,LOW);
		}
		task1 = 2500;
	}


	if(task2 == 0){
		t2s = !t2s;
		digitalWrite(LED2,t2s);
		task2 = 5000;
	}

	if(task3 == 0){
		if(!HOLD){
		   t3s = !t3s;
		   digitalWrite(LED3,t3s);
		}else{
		   digitalWrite(LED3,LOW);
		}
		task3 = 1250;
	}


 	if(!HOLD){

		cins = digitalRead(SIGNAL);
		
		if(cins != lins){
			counter++;
		}

	}

	if(displayUpdate == 0){
		if(!HOLD){
			if(counter <= 9999){
	
				displaysValue[3] = counter/1000;
				int h = counter%1000;
				displaysValue[2] = h/100;
				h = h % 100;
				displaysValue[1] = h/10;
				h = h % 10;
				displaysValue[0] = h;	
			
			}else{
				displaysValue[3] = 1;
				displaysValue[2] = 10;
				displaysValue[1] = 10;
				displaysValue[0] = 10;
			}
		
		}

		if(display == 4){
			display = 0;
		}

		showDigit(displays[display],displaysValue[display]);
		
		display ++;

		displayUpdate = 20;
	}
	
	
    lins = cins;
    task1--;
    task2--;
    task3--;

    taskBtn--;
    displayUpdate--;

    delayMicroseconds(100);
  }


  return 0;
}