/*
   Verificacion de presion en un servo
*/
#include <Servo.h>
// SERVO:
Servo servo;

const int servoPin = 9;
const int cerrado = 90;
const int abierto = 0;

// Historico de posiciones
int posInicial = cerrado;
int posAnterior;
int posicion;

// VOLTIMETRO:
float vArduino = 3.3; // Cuando esta alimentado por USB la salida de 5V solo llega a 3.3V
float r1 = 100000; // valor en ohms de la primer resistencia
float r2 = 10000; // valor en ohms de la segunda resistencia

// Tensiones del servo:
// Pata PWM:
float vEst = 0.24;
float vForz;

// Timestamps
const long intervalo = 15;
unsigned long int millisAnteriores = 0;
unsigned long int millisAnterioresVolt = 0;

void accionoServo(int signal) {
  unsigned long millisActuales = millis(); // Momento actual
  /* Veo si el tiempo transcurrido aplica segun el intervalo tomado 
   * para que el Servo cambie de estado 
   */
  if (millisActuales - millisAnteriores >= intervalo) {
      millisAnteriores = millisActuales; // Guardo el estado actual como anterior para la proxima medicion
      servo.write(signal);
      posicion = signal;
  }
}

void muestroTension(float volts) {

  unsigned long millisActuales = millis(); // Momento actual
  /* Veo si el tiempo transcurrido aplica segun el intervalo tomado 
   * para que el Servo cambie de estado 
   */
  if (millisActuales - millisAnterioresVolt >= 1000) {
    millisAnterioresVolt = millisActuales;
    Serial.println(volts);
  }
 
}

void setup() {

  servo.attach(servoPin); // Inicializo el servo

  Serial.begin(9600);

  Serial.println("--------------------");
  Serial.println("VOLTIMETRO DC");
  Serial.print((int)(vArduino / (r2 / (r1 + r2)))); // vMax: tension maxima que soporta
  Serial.println("V");
  Serial.println("--------------------");
  Serial.println("");

  delay(2000);

}

void loop() {

  accionoServo(posInicial);

  int input = analogRead(A0);
  float vOutput = input * (vArduino / 1023.0); // Se mapea la tension

  // Formula para calcular la tension en un divisor de potencial:
  // Vout = (R2 / (R1 + R2)) * Vin

  // vInput: Tension de DC a medir
  float vInput = vOutput / (r2 / (r1 + r2));
  
  muestroTension(vInput);
  
}
