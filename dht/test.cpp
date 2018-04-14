#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

#define MAX_TIMINGS 85
#define DHT_PIN 28

int data[5];

void read_dht_data()
{
	uint8_t laststate = HIGH;
	uint8_t j = 0;
	
	for(int i=0; i < 5; i++) data[i] = 0;
	
	pinMode(DHT_PIN, OUTPUT);
	digitalWrite(DHT_PIN, LOW);
	delay(20);
	digitalWrite(DHT_PIN, HIGH);
	delayMicroseconds(40);
	pinMode(DHT_PIN, INPUT);

	for(int i=0; i < MAX_TIMINGS; i++) {
		uint8_t counter = 0;
		while(digitalRead(DHT_PIN) == laststate) {
			counter++;
			delayMicroseconds(1);
			if(counter == 255) break;
		}
		laststate = digitalRead(DHT_PIN);
		if(counter == 255) break;
		if (i >= 4 && i % 2 == 0) {
			data[j / 8] <<= 1;
			if(counter > 40) data[j / 8] |= 1;
			j++;
		}
	}

	if (j >= 40 && data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
		int h = (int)data[0];
		int c = (int)(data[2] & 0x7F) * ((data[2] & 0x80) ? -1: 1);
		printf("Humidity = %d %% Temp = %d *C \n", h, c);
	}
	else
		printf("Invalid Data[%d %d %d], Skip\n", j, data[4], (data[0] + data[1] + data[2] + data[3]) & 0xFF);

}

int main()
{
	if(wiringPiSetup() == -1)
		return -1;
	while(1) {
		read_dht_data();
		delay(2000);
	}
	return 0;
}
