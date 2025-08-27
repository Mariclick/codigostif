#include "arduino_secrets.h"

#include "thingProperties.h"


void setup() {
  
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, 16,17);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
    
    if (Serial.available()) {
    String cadena = Serial.readStringUntil('\n');  // Lee hasta '\n'

    if (cadena.length() > 0) {
      ppm = cadena.toFloat();  // Convierte el string a float

      Serial.print("Float recibido: ");
      Serial.println(ppm, 2);
    }
    }
  
}


/*
  Since Ppm is READ_WRITE variable, onPpmChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPpmChange()  {
  // Add your code here to act upon Ppm change
}
/*
  Since Forvent is READ_WRITE variable, onForventChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onForventChange()  {
  if (forvent){
    Serial1.print('1');
  } else {
    Serial1.print('0');
  }
  
}