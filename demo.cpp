#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wiringPi.c"

#define	CE 10	/* wiringOP pin 10 = CE0 */
#define	RS 8	/* wiringOP pin 8 = SDA */
#define	D4 4	/* wiringOP pin 4 = P4 */
#define	D5 5	/* wiringOP pin 5 = P5 */
#define	D6 6	/* wiringOP pin 6 = P6 */
#define	D7 7	/* wiringOP pin 7 = P7 */

using namespace std;

int Pulse() {
   	digitalWrite(CE, LOW); // set ch to st
	usleep(10);
   	digitalWrite(CE, HIGH); // set ch to st
	usleep(10);
		}

int sendData(int d) {

// printf("data d = 0X%X\n",d);

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
	sendData(0x0c); 
	digitalWrite(RS,1);
		}

int out_stg( char *s ) {

	int x = 0;

	while( s[x] != 0xa ) {
	sendData(s[x]);
// printf("x = %d\n",x);
	x++;
		   }
		}

int main (int argc, char **argv)
{
	int x = 0;
	char s[256] = { 0 };
	char q[256] = { 'C', 'P', 'U',' ','T', 'e', 'm', 'p', ' ', '=', ' ', 0xa };
	char z[256] = { 0xdf, 'C',  0xa };
	char k[256] = { 0 };
	FILE *stream;

	init();

stream = popen( "cat /sys/devices/virtual/thermal/thermal_zone0/temp", "r" );
fgets( s, sizeof( s ) - 1, stream);

out_stg(q);
out_stg(s);
out_stg(z);

digitalWrite(RS,0);
sendData(0xd0);
digitalWrite(RS,1);

stream = popen( "date '+%a %b %d %T'", "r" );
fgets( k, sizeof( k ) - 1, stream);
out_stg(k);

digitalWrite(RS,0);
for(;;) {
	sendData(0x18);
	sleep(1);
			}
digitalWrite(RS,1);
 }

