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
    Serial.println("predict");
    data = arduino.readline()
  if data:
        return data
// 0: "lila Lippenstift", 1: "rosa Lippenstift", 2: "Tierchen", 3: "Nichts", 4: "Fehler"

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

void turn_right_and_clear_area_in_the_corner_for_sorted_items(){
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

void put_item_in_the_middle_part_of_the_arena_for_sorting_later(){
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

uint8_t terminating_condition = 0;                           // Wenn diese Variable den Wert 1 annimmt, hört der Roboter auf zu sortieren. => Abbruchbedingung!

void turning_left_and_start_new_line(){
   turn_left(90);
   dgu = get_distance_while_grapple_up();
   if(dgu < 16){
    terminating_condition = 1;
    break;
   }
   else{
     forwards();
     delay(15000);
     turn_left(90);
     where_to_turn++;
     nots++;    
   }
}

void turning_right_and_start_new_line(){
   turn_right(90);
   dgu = get_distance_while_grapple_up();
   if(dgu < 16){
    terminating_condition = 1;
    break;
   }
   else{
     forwards();
     delay(15000);
   turn_right(90);
   where_to_turn--;
     nots++;    
   }
}

void grapple_the_item(){
   forwards();
   delay(5000);
   grapple_down();
   item = camera_result_smooth();
}

void going_back_to_start_position_of_sorting_from_the_sorting_area(){
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
   }
   dgd = get_distance_while_grapple_down();
   while(dgd > 30){
    forwards();
    dgd = get_distance_while_grapple_down();
   } 
}

void sort_a_ball(){
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

void going_to_the_area_of_the_cubes_with_color_one(){
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
}

void sort_a_cube(){
              forwards();
          delay(20000);
          grapple_up();
          backwards();
          delay(5000);
          turn_right(180);
}

void going_back_to_start_position_of_sorting_from_the_area_of_the_cubes_with_color_one(){

          dgd = get_distance_while_grapple_down();
          while(dgd > 20){
            forwards();
            dgd = get_distance_while_grapple_down();
          }
          turn_left(90);
}

void going_to_the_area_of_the_cubes_with_color_two_or_three(){
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
}

void going_back_to_start_position_of_sorting_from_the_area_of_the_cubes_with_color_two(){
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

void going_back_to_start_position_of_sorting_from_the_area_of_the_cubes_with_color_three(){
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

void loop() {                                                // Ich gehe davon aus, dass der Kasten am Greifarm max. 10 cm länge nach vorne hat. Sonst müssen alle mit * markeirten punkte angepasst werden.

while(terminating_condition == 0){
 
 Serial.println(camera_result_smooth());

  while(numberot < 4){                                                    // Räumt einen Streifen außen frei und berücksichtigt dabei auch die vier Ecken mit zusätzlichem Freiraum, da dort später die Gegenstände abgelegt werden.
    dgu = get_distance_while_grapple_up();
    while(dgu > 10){                                                      // Fährt solange geradeaus, bis in einem maximalen Abstand von 10cm ein Gegenstand liegt oder sich eine Wand befindet.
      forwards();
      dgu = get_distance_while_grapple_up();
    }
    if(camera_result_rough() == 0){                                       // Handelt es sich um eine Wand, räumt der Roboter einen Weg um die Ecke frei, damit dort später die gegenstände liegen können, indem er eventuelle Gegenstände in die Mitte schiebt.
      turn_right_and_clear_area_in_the_corner_for_sorted_items();
    }
    else{                                                                 // Handelt es sich um einen Gegenstand wird der "Greifarm" heruntergefahren, der Gegenstand in die Mitte geschoben und der Roboter begibt sich in den vorherigen Zustand an vorheriger Position zurück.
      put_item_in_the_middle_part_of_the_arena_for_sorting_later();
    }
  }
  turn_right(90);
  while(true){                                                            // Fährt in Bahnen durch den mittleren Bereich und sortiert dabei alle Gegenstände die er findet, in dem er zurück zum Ausgangspunkt fährt, den Gegenstand zur enstprechenden Position bringt und dann wieder mit den Bahnen anfängt.
    dgu = get_distance_while_grapple_up();
    while(dgu > 10){                                                      // Fährt solange geradeaus, bis in einem maximalen Abstand von 10cm ein Gegenstand liegt oder sich eine Wand befindet.
      forwards();
      dgu = get_distance_while_grapple_up();
    }
    if(camera_result_rough() == 0){                                       // Handelt es sich um eine Wand, fängt der Roboter eine neue Bahn an. In welche Richtung er sich dafür dreht wird von der vorherigen Drehung festgelegt. Bei der ersten Drehung dreht er nach links.
      if(where_to_turn == 0){
        turning_left_and_start_new_line();
      }
      else{
        turning_right_and_start_new_line();
      }
    }
    else{                                                                 // "Nimmt" den Gegenstand mit dem "Greifarm auf" und die Kamera überprüft um was es sich handelt.
        grapple_the_item();
      if(where_to_turn == 0){                                             // Anschließend dreht sich der Roboter um zurückzufahren.
        turn_right(180);
      }
      else{
        turn_left(180);
      }
      going_back_to_start_position_of_sorting_from_the_sorting_area();    // Der Roboter begibt sich zur Startposition der ersten Bahn zurück und legt den Ball dann entweder in der direkt benachbarten Ecke (Kugel) ab, oder er fährt zu den nächsten Ecken und legt den Gegenstand dort ab (Würfel). Anschließend fährt der Roboter zurück um wieder mit der ersten Bahn anzufangen.
      if(item == 0){
        sort_a_ball();
      }
      else{
        going_to_the_area_of_the_cubes_with_color_one();
        if(item == 1){
          sort_a_cube_with_color_one();
          going_back_to_start_position_of_sorting_from_the_area_of_the_cubes_with_color_one();
        }
        else{
          going_to_the_area_of_the_cubes_with_color_two_or_three();
          if(item == 2){
            sort_a_cube();
            going_back_to_start_position_of_sorting_from_the_area_of_the_cubes_with_color_two();
          }
          else{
            going_to_the_area_of_the_cubes_with_color_two_or_three();
            sort_a_cube();
            going_back_to_start_position_of_sorting_from_the_area_of_the_cubes_with_color_three();
          }
        }
      }
    }
  }
 }
}
