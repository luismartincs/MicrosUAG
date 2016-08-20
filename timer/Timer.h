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


void startTimers();
unsigned char getTimer(unsigned int counter, unsigned int reload, unsigned char repeat);
void setTimer(unsigned char timerId,unsigned int counter, unsigned int reload, unsigned char repeat);
void setCallBack(unsigned char timer,void(*callback)());
Timer getTimerValues(unsigned char timerId);
unsigned int getTimerCount(unsigned char timerId);
void enable(unsigned char timerId,unsigned char status);
unsigned char getTimerStatus(unsigned char timerId);
void freeTimer(unsigned char timerId);