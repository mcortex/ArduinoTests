/*
 * Lectura de Tension (AnalogReadVoltage)
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

const float voltajeEntrada = 3.3;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Lee el valor a traves del pin analogico de entrada A0:
  int valorMedido = analogRead(A0);

  // Convierto la lectura (de 0 a 1023) a voltaje (0 a 5V):
  float voltajeMedido = valorMedido * (voltajeEntrada / 1023);
  Serial.print("Voltaje medido: ");
  // Imprimo el valor medido:
  Serial.println(voltajeMedido);
  delay(1000);
}
