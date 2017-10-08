// Parpadeo sin delay

// Constantes
const int ledPin = LED_BUILTIN; // Se utiliza el LED interno del ARDUINO
const long interval = 1000; // Tiempo en milisegundos que tarda en parpadear el led

//Variables
int ledState = LOW;

unsigned long previousMillis = 0; // Ultimo momento de actualizacion del LED

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis(); // Momento actual desde inicializacion del dispositivo

  /* Veo si el tiempo transcurrido aplica segun el intervalo tomado 
   * para que el LED cambie de estado 
   */
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Guardo el estado actual como anterior para la proxima medicion

    /*
     * Cambio el estado del LED
     */
    if (ledState == LOW) {
      ledState = HIGH;
    }
    else {
      ledState = LOW;
    }

     digitalWrite(ledPin, ledState); // Envio la señal al LED
  }
 

}
