#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#define buzzera 28

int main(int argc, char **argv)
{
	if(wiringPiSetup() == -1)
		return -1;
	pinMode(buzzera, OUTPUT);
	digitalWrite(buzzera, 0);
//	return 0;
	for(;;) {
		for(int i=0; i < 100000; i++) {
			printf("buzzer short %d\n", i);
			digitalWrite(buzzera, 1);
			delay(atoi(argv[1]));
			digitalWrite(buzzera, 0);
			delay(atoi(argv[1]));
		}

		for(int i=0; i < 1; i++) {
			printf("buzzer long %d\n", i);
			digitalWrite(buzzera, 1);
			delay(600);
			digitalWrite(buzzera, 0);
			delay(600);
		}
		break;
	}
	return 0;
}
