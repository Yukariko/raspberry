#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>
#define buzzera 28

int octav[] = {0, 131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 350,
	392, 440, 494, 524, 588, 659, 699, 784, 880, 988};

int main(int argc, char **argv)
{
	if(wiringPiSetup() == -1)
		return -1;
	pinMode(buzzera, OUTPUT);
	softToneCreate(buzzera);
	digitalWrite(buzzera, 0);
	for(;;) {
		for(int i=0; i < 22; i++) {
			softToneWrite(buzzera, octav[i]);
			delay(atoi(argv[1]));
		}

		for(int i=100; i < 4001; i+=10) {
			softToneWrite(buzzera, i);
			delay(10);
		}
		break;
	}
	return 0;
}
