/* based on the example "ComPort"
*/
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  while(!Serial);      // warte auf USB-Verbindung
}

void loop() {
  Serial.println("Message");  
  delay(1000);                   
}
