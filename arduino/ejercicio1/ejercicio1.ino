#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "ASKAR";
const char* password = "A1n4d0y6_!";

String serverName = "http://13.58.130.210:5000";
//String serverName = "http://192.168.0.101:5000";

unsigned long lastTime = 0;

unsigned long timerDelay = 5000;

int LED_BUILTIN = 2;

char incomingByte = 0;
String datos ="";
void setup() {
  Serial2.begin(9600);
  
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  pinMode (LED_BUILTIN, OUTPUT);
}
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      String response = http_getState();
      Serial.println("GetState: "+response);
      Serial2.println(response);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
    
  }
  
  while(Serial2.available()>0){
    incomingByte = Serial2.read();
    datos+=incomingByte;
    if(incomingByte=='}'){
      JSONVar obj = JSON.parse(datos);
      //Serial.println(obj);
      String response = http_setAnalogo(obj);
      //Serial.println("SetAnalog: "+response);
      datos="";
    }
  }
  
}


String http_getState() {
  String response = "{}";

  HTTPClient http;

  String serverPath = serverName + "/getState";

  // Your Domain name with URL path or IP address with path
  http.begin(serverPath.c_str());

  // Send HTTP GET request
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    response = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
  return response;
}


String http_setAnalogo(JSONVar valor){
  String response = "{}";

  HTTPClient http;
  int val = valor["val"];
  String serverPath = serverName + "/setAnalogo?val="+String(val);
  http.begin(serverPath.c_str());

  // Send HTTP GET request
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    response = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
  return response;
}
