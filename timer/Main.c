#include <stdio.h>
#include "Timer.h"

unsigned char T1;
unsigned char T2;
unsigned char T3;

void tarea1()
{
	printf("Ejecutando tarea 1\n");
}

void tarea2()
{
	printf("Ejecutando tarea 2\n");
}

void tarea3()
{
	printf("Ejecutando tarea 3\n");
	enable(T1,0);
}


void init(){

	T1 = getTimer(250,250,1);
	T2 = getTimer(1000,1000,1);
	T3 = getTimer(5000,5000,0);

	setCallBack(T1,&tarea1);
	setCallBack(T2,&tarea2);
	setCallBack(T3,&tarea3);

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