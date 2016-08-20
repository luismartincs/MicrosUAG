#include <stdio.h>
#include <unistd.h>

#define DEBUG 1
#define ENABLE 1
#define DISABLE 0
#define MAX_TIMERS 10
#define uSEC_BASE 1000000 //1000000 per second

typedef struct timer{
	unsigned int counter;
	unsigned int reload;
	unsigned char repeat;
	void (*callback)(void);
} Timer;



Timer getTimerValues(unsigned char timerId);

void startTimers();
void setTimer(unsigned char timerId,unsigned int counter, unsigned int reload, unsigned char repeat);
void setCallBack(unsigned char timer,void(*callback)());
void enable(unsigned char timerId,unsigned char status);
void freeTimer(unsigned char timerId);

unsigned char getTimer(unsigned int counter, unsigned int reload, unsigned char repeat);
unsigned int getTimerCount(unsigned char timerId);
unsigned char getTimerStatus(unsigned char timerId);
