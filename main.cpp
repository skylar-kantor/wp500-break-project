

#include "InterruptIn.h"
#include "PinNames.h"
#include "PinNamesTypes.h"
#include "mbed.h"
#include "mbed_thread.h"
#include "1802.h"
#include <string>

int direction = 0;
void switchDirection();
void speedChange();
int stepPeriod[5] = {200, 100, 50, 25, 10};
int periodPos = 0;
// Initialise the digital pins D13-D10 as outputs
DigitalOut coil1(PA_5);
DigitalOut coil2(PA_6);
DigitalOut coil3(PA_7);
DigitalOut coil4(PD_14);

InterruptIn switcher(BUTTON1, PullDown);
InterruptIn speed(PD_15, PullUp);

int main() { 
  speed.fall(&speedChange);
  switcher.rise(&switchDirection);
  while (true) {
     printf("Period = %d\nDirection = %d\n", stepPeriod[periodPos], direction);
    if (direction == 0) {
      coil2 = 0;
      coil3 = 0;
      coil4 = 0;
      coil1 = 1;
      thread_sleep_for(stepPeriod[periodPos]);
      coil2 = 1;
      coil3 = 0;
      coil4 = 0;
      coil1 = 0;
      thread_sleep_for(stepPeriod[periodPos]);
      coil2 = 0;
      coil3 = 1;
      coil4 = 0;
      coil1 = 0;
      thread_sleep_for(stepPeriod[periodPos]);
      coil2 = 0;
      coil3 = 0;
      coil4 = 1;
      coil1 = 0;
      thread_sleep_for(stepPeriod[periodPos]);
    }

    else {
      coil2 = 0;
      coil3 = 0;
      coil4 = 1;
      coil1 = 0;
      thread_sleep_for(stepPeriod[periodPos]);
      coil2 = 0;
      coil3 = 1;
      coil4 = 0;
      coil1 = 0;
      thread_sleep_for(stepPeriod[periodPos]);
      coil2 = 1;
      coil3 = 0;
      coil4 = 0;
      coil1 = 0;
      thread_sleep_for(stepPeriod[periodPos]);
      coil2 = 0;
      coil3 = 0;
      coil4 = 0;
      coil1 = 1;
      thread_sleep_for(stepPeriod[periodPos]);
    }
  }
}

void switchDirection() {
  wait_us(100);
  if (direction == 0) {
    direction = 1;
  } else {
    direction = 0;
  }
}

void speedChange() {
  wait_us(100);
  periodPos++;
  periodPos %= 5;
}
