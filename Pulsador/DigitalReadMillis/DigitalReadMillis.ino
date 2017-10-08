// DigitalReadSerial:  Lee una entrada de pulsador en pin 2 y la imprime al monitor serial

int pulsador = 2; // Defino una variable de pin para el pulsador
const long interval = 500; // Tiempo en milisegundos entre lecturas
unsigned long previousMillis = 0; // Ultimo momento de actualizacion

void setup() {
  Serial.begin(9600); // Inicializo comunicacion serial
  pinMode(pulsador,INPUT); // linkeo el pulsador como entrada
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis; // Actualizo estado anterior

    int estadoPulsador = digitalRead(pulsador); // Leo el pulsador

    Serial.println(estadoPulsador); // Imprimo en el monitor serial
    
  }


}
