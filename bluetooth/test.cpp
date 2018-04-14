#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <pthread.h>

pthread_t Run_thread;
char Data_in[10];
int fd, rcv_cnt=0, rcv_flag=99;

void  *Thread1(void *pArg)
{
	int i=0;
	for(;;) {
		if(serialDataAvail(fd) && (Data_in[i] = serialGetchar(fd)) > 0) {
			printf("receive = %c hex=0x%x int %d\n", Data_in[i], Data_in[i], i);
			fflush(stdout);
			rcv_cnt=i++;
			rcv_flag = 1;
		}
		else
			i = 0;
		delay(200);
	}
	return 0;
}

int main(void)
{
	setbuf(stdout, NULL);
	if(wiringPiSetupGpio() == -1)
		return -1;

	if((fd = serialOpen("/dev/ttyS0", 9600)) < 0) {
		perror("serialOpen");
		return -1;
	}

	pthread_create(&Run_thread, NULL, Thread1, NULL);
	serialPuts(fd, "connect bluetooth\r\n");

	for(int i=0;;) {
		if(rcv_cnt > i && rcv_flag == 1) {
			printf("send data = %x \n", Data_in[i]);
			serialPutchar(fd, Data_in[i++]);
			if(rcv_cnt == i) {
				rcv_flag = rcv_cnt = 0;
			} else {
				i = 0;
				fflush(stdin);
			}
			delay(1000);
		}
	}
	return 0;
}

