#include "Timer.h"


Timer timers[MAX_TIMERS];

unsigned char timersEnable[MAX_TIMERS];
unsigned char freeTimers[MAX_TIMERS];
unsigned char usedTimers = 0;

//=======================================================================================================

void startTimers(){
	int i = 0;

	while(1){

		for (i = 0; i < MAX_TIMERS; ++i)
		{
			if(timersEnable[i] == ENABLE){
				
				timers[i].counter = timers[i].counter - 1;

				if(timers[i].counter == 0){
					
					if(timers[i].callback != NULL){
						timers[i].callback();
					}else{
						if(DEBUG){
							printf("Timer %i : Sin callback\n",(i+1));
						}
					}

					if(timers[i].repeat == 1){
						timers[i].counter = timers[i].reload;
					}else{
						timersEnable[i] = DISABLE;
					}

				}
			}
		}

		usleep(uSEC_BASE);
	}

}

//=======================================================================================================

unsigned char getTimer(unsigned int counter, unsigned int reload, unsigned char repeat){

	unsigned char i = 0;

	for(i=0; i < MAX_TIMERS; i++){

		if(freeTimers[i] == 0){
			printf("Timer %i is free\n",i);

			timers[i].counter = counter;
			timers[i].reload = reload;
			timers[i].repeat = repeat;

			timersEnable[i] = ENABLE;
			freeTimers[i] = ENABLE;
			return i+1;
		}else{
			printf("Timer %i is used\n",i);
		}

	}

	return 0;
}

//=======================================================================================================

void setTimer(unsigned char timerId,unsigned int counter, unsigned int reload, unsigned char repeat){

	timerId--;
	timers[timerId].counter = counter;
	timers[timerId].reload = reload;
	timers[timerId].repeat = repeat;

}

//=======================================================================================================

void setCallBack(unsigned char timer,void(*callback)()){
	timers[timer-1].callback = callback;
}

//=======================================================================================================

Timer getTimerValues(unsigned char timerId){
	timerId--;
	Timer timerCopy;
	timerCopy.counter = timers[timerId].counter;
	timerCopy.reload = timers[timerId].reload;
	timerCopy.repeat = timers[timerId].repeat;
	return timerCopy;
}

//=======================================================================================================

unsigned int getTimerCount(unsigned char timerId){
	timerId--;
	return timers[timerId].counter;
}

//=======================================================================================================

void enable(unsigned char timerId,unsigned char status){
	timerId--;
	timersEnable[timerId] = status;
}

//=======================================================================================================

unsigned char getTimerStatus(unsigned char timerId){
	return timersEnable[--timerId];
}

//=======================================================================================================

void freeTimer(unsigned char timerId){
	timerId--;
	timers[timerId].counter = 0;
	timers[timerId].reload = 0;
	timers[timerId].repeat = 0;
	timersEnable[timerId] = DISABLE;
	freeTimers[timerId] = DISABLE;
}