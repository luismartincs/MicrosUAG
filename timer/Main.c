#include <stdio.h>
#include "Timer.h"

void tarea1()
{
    printf("%s\n","Tarea 1");
    enable(1,0);

    setTimer(1,2,2,1);

    enable(1,1);
}

void tarea2()
{
    printf("Tarea 2, timer 1 count: %i %i\n",getTimerCount(1),getTimerStatus(1));
}


void init(){

	unsigned char T1 = getTimer(10,10,1);
	freeTimer(T1);
	unsigned char T2 = getTimer(1,1,1);

	setCallBack(T1,&tarea1);
	setCallBack(T2,&tarea2);

	Timer t2Copy = getTimerValues(T1);

	printf("counter: %i\n",t2Copy.counter);
	printf("reload: %i\n",t2Copy.reload);
	printf("repeat: %i\n",t2Copy.repeat);

	startTimers();
}

int main(int argc, char const *argv[])
{

	printf("%s\n","Prueba de timers");

	init();

	return 0;
}