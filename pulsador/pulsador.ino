int pushButton = 2;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(pushButton,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = digitalRead(pushButton);
  Serial.println(sensorValue); // Abrir monitor serial y apretar el pulsador
  delay(1);
}
