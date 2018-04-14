#include <wiringPi.h>
#include <cstring>
#include <cstdlib>

int main(int argc, char **argv)
{
	if (wiringPiSetup() == -1)
		return -1;

	pinMode(21, OUTPUT);
	
	//digitalWrite(21, atoi(argv[1]));

	
	for(int i = 0; i < 10000; i++)
	{
		digitalWrite(21, 1);
		delay(50);
		digitalWrite(21, 0);
		delay(50);
	}
	return 0;
}
