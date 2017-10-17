/*
 * Voltimetro de DC con Arduino:
 * Utiliza un divisor resistivo para medir desde la pata A0.
 * Medira valores de 0 a 55 Volts con fuente externa y 0 a 36 con USB.
 */
//float vArduino = 5; // Tension de arduino con fuente externa
float vArduino = 3.3; // Cuando esta alimentado por USB la salida de 5V solo llega a 3.3V
float r1 = 100000; // valor en ohms de la primer resistencia
float r2 = 10000; // valor en ohms de la segunda resistencia

void setup() {
  Serial.begin(9600);

  //Enviar codigos ANSI a la terminal
//  Serial.print("\x1B");
//  Serial.print("[2J");
//  Serial.print("\x1B");
//  Serial.println("[H");
  //Fin de codigos ANSI para la terminal

  Serial.println("--------------------");
  Serial.println("VOLTIMETRO DC");
  Serial.print((int)(vArduino / (r2 / (r1 + r2)))); // vMax: tension maxima que soporta
  Serial.println("V");
  Serial.println("--------------------");
  Serial.println("");
  delay(2000);
}

void loop() {
  /*
   To change the values from 0-1023 to a range that 
   corresponds to the voltage the pin is reading, 
   you'll need to create another variable, a float, and do a little math. 
   To scale the numbers between 0.0 and 5.0, divide 5.0 by 1023.0 and multiply that 
   by sensorValue:
   */
  int input = analogRead(A0);
  float vOutput = input * (vArduino / 1023.0); // Se mapea la tension

  // Formula para calcular la tension en un divisor de potencial: 
  // Vout = (R2 / (R1 + R2)) * Vin

  // vInput: Tension de DC a medir
  float vInput = vOutput / (r2 / (r1+r2)); 
  
  //Enviar codigos ANSI a la terminal
//  Serial.print("\x1B");
//  Serial.print("[1A");
  //Fin de codigos ANSI para la terminal

  Serial.println(vInput);
  delay(1000);
}
