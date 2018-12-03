#include <Ftduino.h>

void setup() {
  ftduino.init();
  ftduino.ultrasonic_enable(true);
  delay(1000); 
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  int16_t distance = ftduino.ultrasonic_get();
  Serial.println(distance);
  delay(1000); 
 
}
