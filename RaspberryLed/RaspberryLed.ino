/*
 * Control de LED en Arduino desde Raspberry Pi
 * Ver: https://github.com/mcortex/RaspiTests/blob/master/ArduinoTests/ArduinoLed.py
 */

const int ledPin = 13;

void setup() {
  
  pinMode(ledPin,OUTPUT); // Inicializo el pin13 como salida digital
  Serial.begin(9600); // Inicializo el puerto serial a 9600 baudios para comunicar con la raspi
  

}

void loop() {

  // Si el puerto serie esta disponible me comunico con la raspi
  if (Serial.available()) {
    char varRecibida = Serial.read();
    if (varRecibida == 'H') {
      digitalWrite(ledPin,HIGH); // Si recibi una H prendo el LED
    }
    else if (varRecibida == 'L') {
      digitalWrite(ledPin,LOW); // Si recibi una L apago el LED
    }
    
  }

}
