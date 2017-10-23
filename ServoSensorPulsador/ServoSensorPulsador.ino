/*
   Verificacion de presion en un servo
*/
#include <Servo.h>
// SERVO:
Servo servo; // Definimos un objeto servo a controlar desde la Raspi

// Variables del servo
const int servoPin = 9; // El servo conectará en el pin 9 (PWM)
const int cerrado = 90; // Cerrado: Servo a 90 grados (Posicion inicial)
const int abierto = 0; // Abierto: Servo a 0 grados

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
float vEst = 0;
float vForce = 1;

// Timestamps
const long intervaloServo = 15;
unsigned long int millisAnteriores = 0;
unsigned long int millisAnterioresVolt = 0;

void accionoServo(char signal) {
  unsigned long millisActuales = millis(); // Momento actual
  /* Veo si el tiempo transcurrido aplica segun el intervalo tomado
     para que el Servo cambie de estado
  */
  if (millisActuales - millisAnteriores >= intervaloServo) {
    millisAnteriores = millisActuales; // Guardo el estado actual como anterior para la proxima medicion

    if (posicion == cerrado && signal == 'A') {
      servo.write(abierto);
      posicion = abierto;
      Serial.println("ABIERTO");
    }
    else if (posicion == abierto && signal == 'A') {
      servo.write(cerrado);
      posicion = cerrado;
      Serial.println("CERRADO");
    }
  }
}

void muestroTension() {

  unsigned long millisActuales = millis(); // Momento actual
  /* Veo si el tiempo transcurrido aplica segun el intervalo tomado
     para que el Servo cambie de estado
  */
  if (millisActuales - millisAnterioresVolt >= 100) {
    millisAnterioresVolt = millisActuales;

    int input = analogRead(A0);
    float vOutput = input * (vArduino / 1023.0); // Se mapea la tension

    // Formula para calcular la tension en un divisor de potencial:
    // Vout = (R2 / (R1 + R2)) * Vin

    // vInput: Tension de DC a medir
    float vInput = vOutput / (r2 / (r1 + r2));

    
    if (vInput == vEst && posicion == cerrado && vForce != 0) {
      vForce = 0;
      Serial.print("Tension de puerta: ");
      Serial.println("ESTACIONARIO (cerrado)");
    }
    if (vInput > vEst && posicion == cerrado && vForce == 0) {
      vForce = 1;
      Serial.print("Tension de puerta: ");
      Serial.println("FORZADO");
    }
    if (vInput > vEst && posicion == abierto) {
      vForce = 0;
      Serial.println("ABIERTO");
    }

//    if (vInput == vEst && vForce != 0) {
//      vForce = 0;
//      Serial.println("ESTACIONARIO (cerrado)");
//    }
//    if (vInput > vEst && vForce == 0) {
//      vForce = 1;
//      Serial.println("FORZADO");
//    }
//    if (vInput > vEst && vForce == 0) {
//      vForce = 1;
//      Serial.println("ABIERTO");
//    }
  }
}



void setup() {

  servo.attach(servoPin); // Inicializo el servo

  Serial.begin(9600);

  if (servo.read() != posInicial) {
    servo.write(posInicial); // Si la puerta estaba abierta la cierro
    posicion = posInicial;

    delay(intervaloServo); // Solo usamos delay aca ya que es solo una accion bloqueante de inicializacion
  }

  Serial.println(posicion);

}

void loop() {

  if (Serial.available()) {

    char sigRecibida = Serial.read();
    accionoServo(sigRecibida);
  }

  //accionoServo(posInicial);
  muestroTension();

}
