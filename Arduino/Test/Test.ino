#include <FtduinoSimple.h>
//#include <Ftduino.h>

/**
 * Motorports
 * M1: Antrieb Links
 * M2: Antrieb Rechts
 * M3: Antrieb Greifarm
 * M4: [Leer]
 * 
 * 
 */

uint8_t mtr = Ftduino::RIGHT; // mtr = Motor Turn Right
uint8_t mtl = Ftduino::LEFT;  // mtl = Motor Turn Left
uint8_t mst = Ftduino::BRAKE; // mst = Motor Stop via Widerstandsbremse
uint8_t mpo = Ftduino::OFF;   // mpo = Motor Power Off

uint8_t el = Ftduino::M1;     // el = Engine Left Track
uint8_t er = Ftduino::M2;     // er = Engine Right Track
uint8_t eg = Ftduino::M3;     // eg = Engine of that Generic.Bullshit in front of the robot

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Successfull connected on COM port.");
  ftduino.motor_set(Ftduino::M1, Ftduino::LEFT );
}

/*void forwards(uint8_t run_speed = Ftduino::MAX) {
  ftduino.motor_set(er, mtr, run_speed);
  ftduino.motor_set(el, mtl, run_speed);
}

void stop_tank(uint8_t strength = Ftduino::MAX) {
  ftduino.motor_set(er, mst, strength);
  ftduino.motor_set(el, mst, strength);
}

void turn_left(uint8_t angle, bool on_point = true) {
  ftduino.motor_counter(er, mtr, Ftduino::MAX/7, angle);
  if(on_point == false) {
    ftduino.motor_set(el, mpo, Ftduino::MAX);
  }
  else {
    ftduino.motor_counter(el, mtr, Ftduino::MAX/7, angle);
  }
}

void turn_right(uint8_t angle, bool on_point = true) {
  ftduino.motor_counter(el, mtl, Ftduino::MAX/7, angle);
  if(on_point == false) {
    ftduino.motor_set(er, mpo, Ftduino::MAX);
  }
  else {
    ftduino.motor_counter(er, mtl, Ftduino::MAX/7, angle);
  }
}

void backwards(uint8_t run_speed = Ftduino::MAX) {
  ftduino.motor_set(er, mtl, run_speed);
  ftduino.motor_set(el, mtr, run_speed);
}

void use_that_bullshit() {
  ftduino.input_set_mode(Ftduino::I1, Ftduino::SWITCH); // Set Input pin I1 to the higher one of those touch sensors
  ftduino.input_set_mode(Ftduino::I2, Ftduino::SWITCH); // Set Input pin I2 to the lower one of those touch sensors
  ftduino.motor_set(eg, mtl, Ftduino::MAX/7);
  while(!ftduino.input_get(Ftduino::I1));
  ftduino.motor_set(eg, mst, Ftduino::MAX);
  ftduino.motor_set(eg, mtr, Ftduino::MAX/7);
  while(!ftduino.input_get(Ftduino::I2));
  ftduino.motor_set(eg, mst, Ftduino::MAX);
}*/

void loop() { //test
  ftduino.motor_set(Ftduino::M1, Ftduino::RIGHT);
  delay(2000);
  if( ftduino.input_get( Ftduino::I1)) {
    Serial.println("Taster1 ist gedrückt.");
    ftduino.motor_set(Ftduino::M1, Ftduino::LEFT);
    delay(250);
  }
  if(ftduino.input_get(Ftduino::I2)) {
    Serial.println("Taster2 ist gedrückt.");
    ftduino.motor_set(Ftduino::M1, Ftduino::OFF);
    delay(250);
  }
}
