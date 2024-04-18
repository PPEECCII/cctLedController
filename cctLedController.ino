#include <math.h>

#define TOUCHED_MAX_VALUE 15 //Capacitive touch max touched value

#define TOUCH_PIN 14 //GPIO touch pin number

#define COLD_LIGHT 12 //Cold light control pin
#define WARM_LIGHT 13 //Warm light control pin

#define TOUCH_DURATION 300 //Looping delay time

#define RESOLUTION 4 //PWM frequency resolution

#define LONG_TOUCH_DURATION 3 //Number of touch duration that are considered a long press

#define STATUS_OFF 0 //Off Status constant
#define STATUS_WARM 1 //Warm light status constant
#define STATUS_WHITE 2 //White light status constant
#define STATUS_COLD 3 //Cold light status constant

int count = 0;

int currentValue=1;

boolean isIncreasing = true;

int maxValue;

int status = STATUS_OFF;

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
  pinMode(TOUCH_PIN, INPUT);

  maxValue = pow(2.0, RESOLUTION) - 1;
  analogWriteResolution(RESOLUTION);
  setLight();
}

void loop() {
  boolean touched = digitalRead(TOUCH_PIN) == HIGH;
  if(touched) {
    if(++count >= LONG_TOUCH_DURATION) handleLongPress(count - LONG_TOUCH_DURATION);
  } else {
    if(count > 0 && count < LONG_TOUCH_DURATION) handlePush();
    count = 0;
  }
  delay(TOUCH_DURATION);
}

void handlePush() {
    Serial.println("CORTO");
    if(status == STATUS_OFF) {
      status = STATUS_WARM;
    } else if(status == STATUS_WARM) {
      status = STATUS_WHITE;
    } else if(status == STATUS_WHITE) {
      status = STATUS_COLD;
    } else status = STATUS_OFF;
    setLight();
}

void handleLongPress(int counter) {
    Serial.print("LARGO ");
    Serial.println(counter);
    if(counter <= 0) { 
      isIncreasing = !isIncreasing;
    }
    if(isIncreasing) {
      if(currentValue < maxValue) 
        currentValue++;
    }
    else if(currentValue > 1) 
      currentValue--;
    
    setLight();
}

void setLight() {
  Serial.println(status);
  Serial.println(currentValue);
  analogWrite(WARM_LIGHT, (status == STATUS_WARM || status == STATUS_WHITE) ? currentValue : 0);
  analogWrite(COLD_LIGHT, (status == STATUS_COLD || status == STATUS_WHITE) ? currentValue : 0);
}
