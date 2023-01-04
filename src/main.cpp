#include "mbed.h"

DigitalOut btnIndicator(LED1);
DigitalOut heart(LED4);
DigitalIn pb(p7);

// Flashing rates in blinks per second
#define FAST_HEART_RATE 5
#define SLOW_HEART_RATE 1
#define ONE_SECOND 1000ms

enum rateState_t {FastMode, SlowMode};

int main() {
  rateState_t rateMode = FastMode;
  int prevBtn = pb.read();
  int currBtn;
  
  while (true) {
    heart = !heart;
    currBtn = pb.read(); // Read button once per loop
    btnIndicator = currBtn;
    if ((currBtn != prevBtn) && (currBtn)) {
        rateMode = (rateState_t)!rateMode;
    }
    prevBtn = currBtn;
    if (rateMode == FastMode) {
      ThisThread::sleep_for(ONE_SECOND / FAST_HEART_RATE / 2);
    } else {
      ThisThread::sleep_for(ONE_SECOND / SLOW_HEART_RATE / 2);
    }
  }
}