// DigitalReadSerial:  Lee una entrada de pulsador en pin 2 y la imprime al monitor serial

int pulsador = 2; // Defino una variable de pin para el pulsador
const long interval = 500; // Tiempo en milisegundos entre lecturas
unsigned long previousMillis = 0; // Ultimo momento de actualizacion

// Debounce para sacar ruido a las pulsaciones
int ultimoPulsado = LOW; // Ultima lectura del pin
int actualPulsado;
unsigned long lastDebounce = 0; // Ultimo momento del debounce
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600); // Inicializo comunicacion serial
  pinMode(pulsador,INPUT); // linkeo el pulsador como entrada
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis; // Actualizo estado anterior

    int estadoPulsador = digitalRead(pulsador); // Leo el pulsador

    if (estadoPulsador != ultimoPulsado) {
      lastDebounce = millis(); //Reset del debounce
    }

    if ((millis() - lastDebounce) > debounceDelay) {
      if (estadoPulsador != actualPulsado) {
        actualPulsado = estadoPulsador;
      }
      if (actualPulsado == HIGH) {
        Serial.println(estadoPulsador); // Imprimo en el monitor serial
      }
    }

    
      ultimoPulsado = estadoPulsador;
  }


}
