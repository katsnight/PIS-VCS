#include <wiringPi.h> 
#include <stdio.h>

int main (void)  {
    	    int PINS[8] = {0, 1, 2, 3, 4 ,5 ,6, 7}; 
   wiringPiSetup();

for (int i = 0; i < 8; i++) {
pinMode (PINS[i], OUTPUT);
}

for (int i = 0; i < 8; i++) {
digitalWrite (PINS[i], LOW);
}

while(1) {
      for (int i = 0; i < 8; i++) {
digitalWrite (PINS[i], HIGH);          
delay(150);
digitalWrite (PINS[i], LOW);
delay(250);
}
for (int i = 7; i>=0; i--) {
digitalWrite (PINS[i], HIGH);          
delay(150);
digitalWrite (PINS[i], LOW);
delay(250);
}
}
 return 0;
}
