#include <stdio.h>
#include <unistd.h>
#include "wiringPi.c"

#define	CE 10	/* wiringOP pin 10 = CE0 */
#define	RS 8	/* wiringOP pin 8 = SDA */
#define	D4 4	/* wiringOP pin 4 = P4 */
#define	D5 5	/* wiringOP pin 5 = P5 */
#define	D6 6	/* wiringOP pin 6 = P6 */
#define	D7 7	/* wiringOP pin 7 = P7 */

int Pulse() {  /* pulse the CE line - the Write line is tied low */
   	digitalWrite(CE, LOW); // set ch to st
	usleep(10);
   	digitalWrite(CE, HIGH); // set ch to st
	usleep(10);
		}

int sendData(char d) {

/* Output MSB First */
if(d & 16) { digitalWrite(D4,1); } else { digitalWrite(D4,0); }
if(d & 32) { digitalWrite(D5,1); } else { digitalWrite(D5,0); }
if(d & 64) { digitalWrite(D6,1); } else { digitalWrite(D6,0); }
if(d & 128) { digitalWrite(D7,1); } else { digitalWrite(D7,0); }
	Pulse();

/* then the LSB */
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
   	digitalWrite(CE, HIGH);
	digitalWrite(RS,0);
		}

int main (int argc, char **argv)
{
  	int c, d, e, x;
	char cd;

if(argc < 3) {
	printf("Usage: lcd c af - to execute command 0xAF\n");
	printf("Usage: lcd d \"string of data\" - to output string to the LCD\n");
	exit(1);
		}

cd = argv[1][0];

init();

if(cd == 'c') {
d = argv[2][1];
if(d > 0x39) { d += 9; }
d = d & 15;

c = argv[2][0];
if(c > 0x39) { c += 9; }
c = (c  & 15) << 4;
e = c | d;
printf("doing Ctl with c = 0x%x d=0x%x e=0x%x\n",c,d,e);
digitalWrite(RS,0);
sendData(e);
		}
else		{
digitalWrite(RS,1);
x = 0;
while(argv[2][x] != 0) {
sendData(argv[2][x]);
x++;
			}
		}

}

