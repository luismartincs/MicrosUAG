#include <stdio.h>


void estado1(void){
	printf("%s\n","Primer estado");
}

void estado2(void){
	printf("%s\n","Segundo estado");
}

void estado3(void){
	printf("%s\n","Tercer estado");
}

void (* estados[])(void) =
{
	estado1,
	estado2,
	estado3
};

typedef enum state_codes { START, SEND, FINISH} state;


int main(int argc, char const *argv[])
{

	state current_state = START;

	estados[0]();

	printf("%s\n","Tabla de saltos");


	return 0;
}