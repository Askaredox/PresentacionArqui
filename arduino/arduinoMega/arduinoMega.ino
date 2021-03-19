#include <Arduino_JSON.h>
char incomingByte = 0;
String datos ="";
int sensorPin = A1;
int ledPin = 13;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check if the other Arduino is transmitting
  // send data only when you receive data:
  while (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();
    datos+=incomingByte;
    // say what you got:
    //Serial.print("I received: ");
    //Serial.println(incomingByte);
    if(incomingByte=='}'){
      int sensorValue = analogRead(sensorPin);
      Serial1.println("{\"val\":"+String(sensorValue)+"}");
      JSONVar obj = JSON.parse(datos);
      datos="";
      Serial.println(obj);
      digitalWrite(ledPin, bool(obj["encendido"])?HIGH:LOW);
    }
  }
}
