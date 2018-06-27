#include <stdio.h>
#include <unistd.h>
#include "wiringPi.c"

#define	CE 10	/* wiringOP pin 10 = CE0 */
#define	RS 8	/* wiringOP pin 8 = SDA */
#define	D4 4	/* wiringOP pin 4 = P4 */
#define	D5 5	/* wiringOP pin 5 = P5 */
#define	D6 6	/* wiringOP pin 6 = P6 */
#define	D7 7	/* wiringOP pin 7 = P7 */

int Pulse() {
   	digitalWrite(CE, LOW); // set ch to st
	usleep(10);
   	digitalWrite(CE, HIGH); // set ch to st
	usleep(10);
		}

int sendData(int d) {

printf("data d = 0X%X\n",d);

if(d & 16) { digitalWrite(D4,1); } else { digitalWrite(D4,0); }
if(d & 32) { digitalWrite(D5,1); } else { digitalWrite(D5,0); }
if(d & 64) { digitalWrite(D6,1); } else { digitalWrite(D6,0); }
if(d & 128) { digitalWrite(D7,1); } else { digitalWrite(D7,0); }
	Pulse();

if(d & 1) { digitalWrite(D4,1); } else { digitalWrite(D4,0); }
if(d & 2) { digitalWrite(D5,1); } else { digitalWrite(D5,0); }
if(d & 4) { digitalWrite(D6,1); } else { digitalWrite(D6,0); }
if(d & 8) { digitalWrite(D7,1); } else { digitalWrite(D7,0); }
	Pulse();
			}


int init() {
  	wiringPiSetup();
	pinMode(CE,OUTPUT);
	pinMode(RS,OUTPUT);
	pinMode(D4,OUTPUT);
	pinMode(D5,OUTPUT);
	pinMode(D6,OUTPUT);
	pinMode(D7,OUTPUT);
   	digitalWrite(CE, HIGH); // set ch to st
	digitalWrite(RS,0);
	sendData(1);
	sendData(2);
	sendData(0x28); 
	digitalWrite(RS,1);
		}

int main (int argc, char **argv)
{
	int x = 0;
  	char c = 0;

	init();

if(argc < 2) {

while( c != 0xa ) {
 c = getchar();
 putchar(c);
sendData(c);
		}
	}

else		{

while(argv[1][x] != 0) {
sendData(argv[1][x]);
x++;
			}
		}
 }

