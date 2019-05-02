#include <Ftduino.h>

/**
 * Motorports
 * M1: Antrieb Links
 * M2: Antrieb Rechts
 * M3: Antrieb Greifarm
 * M4: [Leer]
 * 
 * I1: Drucksensor Unten
 * I2: Drucksensor Oben
 * I3: Abstandssensor vorne am Roboter
 * I4: Abstandssensor vorne am "Greifarm" (Höher als Kugeln/Würfel)
 */

uint8_t mtr = Ftduino::RIGHT; // mtr = Motor Turn Right
uint8_t mtl = Ftduino::LEFT;  // mtl = Motor Turn Left
uint8_t mst = Ftduino::BRAKE; // mst = Motor Stop via Widerstandsbremse
uint8_t mpo = Ftduino::OFF;   // mpo = Motor Power Off

uint8_t el = Ftduino::M1;     // el = Engine Left Track
uint8_t er = Ftduino::M2;     // er = Engine Right Track
uint8_t eg = Ftduino::M3;     // eg = Engine grappler

uint8_t numberot = 0;          // numberot = numberofturns => Nach 4 Drehungen ist der Roboter einmal außen längs gefahren

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Successfull connected on COM port.");
}

void forwards(uint8_t run_speed = Ftduino::MAX) {
  ftduino.motor_set(er, mtr, run_speed);
  ftduino.motor_set(el, mtl, run_speed);
}

void stop_tank(uint8_t strength = Ftduino::MAX) {
  ftduino.motor_set(er, mst, strength);
  ftduino.motor_set(el, mst, strength);
}

void turn_left(uint8_t angle, bool on_point = true) {
  // angle: Drehung vom Motorrad, nicht vom Roboter
  // on_point: ???
  ftduino.motor_counter(er, mtr, Ftduino::MAX/7, angle);
  if(on_point == false) {
    ftduino.motor_set(el, mpo, Ftduino::MAX);
  }
  else {
    ftduino.motor_counter(el, mtr, Ftduino::MAX/7, angle);
  }
}

void turn_right(uint8_t angle, bool on_point = true) {

  // angle: Drehung vom Motorrad, nicht vom Roboter
  // on_point: ???

  ftduino.motor_counter(el, mtl, Ftduino::MAX/7, angle);
  if(on_point == false) {
    ftduino.motor_set(er, mpo, Ftduino::MAX);
  }
  else {
    ftduino.motor_counter(er, mtl, Ftduino::MAX/7, angle);
  }
}

// mit vorwärts vereinigbar
void backwards(uint8_t run_speed = Ftduino::MAX) {
  ftduino.motor_set(er, mtl, run_speed);
  ftduino.motor_set(el, mtr, run_speed);
}


// die nächsten zwei Funktionen könnten zu einer zusammengefasst werden, die als Argument up oder down hat
void grapple_down(){
  // Die nächsten zwei Zeilen könnten eventuell auch nur einmal ausgeführt werden, dann lieber nicht in der Funktion
  ftduino.input_set_mode(Ftduino::I1, Ftduino::SWITCH); // Set Input pin I1 to the higher one of those touch sensors
  ftduino.input_set_mode(Ftduino::I2, Ftduino::SWITCH); // Set Input pin I2 to the lower one of those touch sensors
  ftduino.motor_set(eg, mtl, Ftduino::MAX/7);
  while(!ftduino.input_get(Ftduino::I1));
  ftduino.motor_set(eg, mst, Ftduino::MAX);
}

void grapple_up(){
  // Die nächsten zwei Zeilen könnten eventuell auch nur einmal ausgeführt werden, dann lieber nicht in der Funktion
  ftduino.input_set_mode(Ftduino::I1, Ftduino::SWITCH); // Set Input pin I1 to the higher one of those touch sensors
  ftduino.input_set_mode(Ftduino::I2, Ftduino::SWITCH); // Set Input pin I2 to the lower one of those touch sensors
  ftduino.motor_set(eg, mtr, Ftduino::MAX/7);
  while(!ftduino.input_get(Ftduino::I2));
  ftduino.motor_set(eg, mst, Ftduino::MAX);
}

uint8_t get_distance_while_grapple_up(){                     // Misst Abstand, während der Greifarm oben ist
  
}

uint8_t get_distance_while_grapple_down(){                   // Misst Abstand, während der Greifarm unten ist
  
}

uint8_t camera_result_rough(){                               // Überprüft per Kamera, was vor dem Roboter liegt
                                                             // 0 = Wand
                                                             // 1 = Gegenstand
  
}
// Elena fügt's ein
uint8_t camera_result_smooth(){                              // Überprüft per Kamera, was für ein Gegenstand vor der Kamera liegt  
                                                             // 0 = Kugel
                                                             // 1 = Würfel Farbe 1
                                                             // 2 = Würfel Farbe 2
                                                             // 3 = Würfel Farbe 3    
  
}

uint8_t where_to_turn = 0;                                   // 0 = Links
                                                             // 1 = Rechts

uint8_t nots = 0;                                            // nots = number of turns while sorting

uint8_t item = 0;                                            // Speichert welcher, Gegenstand eingesammelt wird

uint8_t dgu = get_distance_while_grapple_up();

uint8_t dgd = get_distance_while_grapple_down();

void loop() {                                                // Ich gehe davon aus, dass der Kasten am Greifarm max. 10 cm länge nach vorne hat. Sonst müssen alle mit * markeirten punkte angepasst werden.
  // put your main code here, to run repeatedly:
  while(numberot < 4){
    dgu = get_distance_while_grapple_up();
    while(dgu > 10){
      forwards();
      dgu = get_distance_while_grapple_up();
    }
    if(camera_result_rough() == 0){
      turn_right(180);      // 180 als Gradzahl, muss später getestet und angepasst werden
      backwards();
      delay(10000);         // 10s als Zeit um 10cm zurückzulegen, muss später getestet und angepasst werden *
      turn_left(90);        // 90 als Gradzahl, muss später getestet und angepasst werden
      forwards();           
      delay(20000);         // 20s als Zeit um 20cm zurückzulegen, muss später getestet und angepasst werden *
      turn_right(90);       // 90 als Gradzahl, muss später getestet und angepasst werden
      forwards();
      delay(50000);         // 50s als Zeit um 50cm zurückzulegen, muss später getestet und angepasst werden
      turn_left(90);        // 90 als Gradzahl, muss später getestet und angepasst werden
      forwards();      
      delay(10000);         // 10s als Zeit um 10cm zurückzulegen, muss später getestet und angepasst werden
      turn_right(90);       // 90 als Gradzahl, muss später getestet und angepasst werden
      backwards();
      delay(50000);         // 50 als Zeit um 50cm zurückzulegen, muss später getestet und angepasst werden
      turn_left(90);        // 90 als Gradzahl, muss später getestet und angepasst werden
      numberot++;
    }
    else{
      forwards();
      delay(5000);          // 5s als Zeit um 5cm zurückzulegen, muss später getestet und angepasst werden
      grapple_down();
      backwards();
      delay(5000);          // 5s als Zeit um 5cm zurückzulegen, muss später getestet und angepasst werden
      turn_right(90);       // 90 als Gradzahl, muss später getestet und angepasst werden
      forwards();
      delay(10000);         // 10s als Zeit um 10cm zurückzulegen, muss später getestet und angepasst werden *
      grapple_up();
      backwards();
      delay(10000);         // 10s als Zeit um 10cm zurückzulegen, muss später getestet und angepasst werden *
      turn_left(90);        // 90 als Gradzahl, muss später getestet und angepasst werden
    }
  }
  turn_right(90);
  while(true){
    dgu = get_distance_while_grapple_up();
    while(dgu > 10){
      forwards();
      dgu = get_distance_while_grapple_up();
    }
    if(camera_result_rough() == 0){
      if(where_to_turn == 0){
        turn_left(90);
        forwards();
        delay(15000);
        turn_left(90);
        where_to_turn++;
        nots++;
      }
      else{
        turn_right(90);
        forwards();
        delay(15000);
        turn_right(90);
        where_to_turn--;
        nots++;
      }
    }
    else{
      forwards();
      delay(5000);
      item = camera_result_smooth();
      grapple_down();
      if(where_to_turn == 0){
        turn_right(180);
      }
      else{
        turn_left(180);
      }
      while(nots > 0){
        dgd = get_distance_while_grapple_down();
        while(dgd > 15){
          forwards();
          dgd = get_distance_while_grapple_down();
        }
        if(where_to_turn == 0){
          turn_left(180);
          backwards();
          delay(10000);
          turn_right(90);
          forwards();
          delay(15000);
          turn_left(90);
          where_to_turn++;
          nots--;
        }
        else{
          turn_right(180);
          backwards();
          delay(10000);
          turn_left(90);
          forwards();
          delay(15000);
          turn_right(90);
          where_to_turn--;
          nots--;
        }
        dgd = get_distance_while_grapple_down();
        while(dgd > 30){
          forwards();
          dgd = get_distance_while_grapple_down();
        }
        if(item == 0){
          turn_left(270);
          backwards();
          delay(20000);
          turn_left(90);
          forwards();
          delay(30000);
          grapple_up();
          backwards();
          delay(30000);
          turn_right(90);
          forwards();
          delay(20000);
          turn_right(90);
        }
        else{
          turn_left(90);
          dgd = get_distance_while_grapple_down();
          while(dgd > 20){
            forwards();
            dgd = get_distance_while_grapple_down();
          }
          turn_right(90);
          dgd = get_distance_while_grapple_down();
          while(dgd > 5){
            forwards();
            dgd = get_distance_while_grapple_down();
          }
          turn_right(90);
          dgd = get_distance_while_grapple_down();
          while(dgd > 20){
            forwards();
            dgd = get_distance_while_grapple_down();
          }
          if(item == 1){
            forwards();
            delay(20000);
            grapple_up();
            backwards();
            delay(5000);
            turn_right(180);
            dgd = get_distance_while_grapple_down();
            while(dgd > 20){
              forwards();
              dgd = get_distance_while_grapple_down();
            }
            turn_left(90);
          }
          else{
            turn_right(90);
            forwards();
            delay(20000);
            turn_left(90);
            dgd = get_distance_while_grapple_down();
            while(dgd > 5){
              forwards();
              dgd = get_distance_while_grapple_down();
            }
            turn_right(90);
            dgd = get_distance_while_grapple_down();
            while(dgd > 20){
              forwards();
              dgd = get_distance_while_grapple_down();
            }
            if(item == 2){
              forwards();
              delay(20000);
              grapple_up();
              backwards();
              delay(5000);
              turn_right(180);
              dgd = get_distance_while_grapple_down();
              while(dgd > 20){
                forwards();
                dgd = get_distance_while_grapple_down();
              }
              turn_left(90);
              forwards();
              delay(20000);
              turn_right(90);
              dgd = get_distance_while_grapple_down();
              while(dgd > 5){
                forwards();
                dgd = get_distance_while_grapple_down();
              }
              turn_left(90);
              dgd = get_distance_while_grapple_down();
              while(dgd > 20){
                forwards();
                dgd = get_distance_while_grapple_down();
              }
              turn_left(90);
            }
            else{
              turn_right(90);
              forwards();
              delay(20000);
              turn_left(90);
              dgd = get_distance_while_grapple_down();
              while(dgd > 5){
                forwards();
                dgd = get_distance_while_grapple_down();
              }
              turn_right(90);
              dgd = get_distance_while_grapple_down();
              while(dgd > 20){
                forwards();
                dgd = get_distance_while_grapple_down();
              }
              forwards();
              delay(20000);
              grapple_up();
              backwards();
              delay(5000);
              turn_right(180);
              dgd = get_distance_while_grapple_down();
              while(dgd > 20){
                forwards();
                dgd = get_distance_while_grapple_down();
              }
              turn_left(90);
              forwards();
              delay(20000);
              turn_right(90);
              dgd = get_distance_while_grapple_down();
              while(dgd > 5){
                forwards();
                dgd = get_distance_while_grapple_down();
              }
              turn_left(90);
              dgd = get_distance_while_grapple_down();
              while(dgd > 20){
                forwards();
                dgd = get_distance_while_grapple_down();
              }
              turn_left(90);
              forwards();
              delay(20000);
              turn_right(90);
              dgd = get_distance_while_grapple_down();
              while(dgd > 5){
                forwards();
                dgd = get_distance_while_grapple_down();
              }
              turn_left(90);
              dgd = get_distance_while_grapple_down();
              while(dgd > 20){
                forwards();
                dgd = get_distance_while_grapple_down();
              }
              turn_left(90);
            }
          }
        }
      }
    }
  }
}
