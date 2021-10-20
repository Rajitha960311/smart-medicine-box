#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define buzzPin D1

const char* ssid = "OPPO A5s";
const char* password = "qweqweqwe";

String serverName = "http://192.168.43.236:8080/medInfo";

unsigned long lastTime = 0;
unsigned long timerDelay = 18000; // 18 sec

void setup() {
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  //Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
  //Serial.print("Connected to WiFi network with IP Address: ");
  //Serial.println(WiFi.localIP());

  pinMode(buzzPin,OUTPUT); // Set buzzer-pin as output
  digitalWrite(buzzPin, HIGH);
}

void loop() {
  
  String rs = "{}";
  String receivedData = "";
  
  if ((millis() - lastTime) > timerDelay) {

    String haveReminder = checkReminders();

    //Serial.println(haveReminder);
    if(haveReminder=="true"){
          Buzzer();       
    }
  
    lastTime = millis();
  }
  
  if (Serial.available()) {
    receivedData = Serial.readStringUntil('\n');
    receivedData.trim();
  }

  if(receivedData != "" && receivedData !="893C0E21" && receivedData !="B64E130A"){
    rs = httpPOSTRequest(serverName,receivedData);
    Serial.println(rs);
    delay(18000);
  }

  if(receivedData != "" && (receivedData =="893C0E21" || receivedData =="B64E130A")){
    rs = httpGETRequest(serverName, receivedData);
    rs.trim();
    Serial.println(rs);
    delay(18000);
  }

}

String httpGETRequest(String serverName, String receivedData) {   
  WiFiClient client;
  HTTPClient http;
  String serverPath = serverName + "/" +receivedData;
  
  // Your IP address with path or Domain name with URL path
  http.begin(client, serverPath);
  
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    //Serial.print("Error code: ");
    //Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

String httpPOSTRequest(String serverName, String receivedData) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(receivedData);
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    //Serial.print("Error code: ");
    //Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

String checkReminders() {   
  WiFiClient client;
  HTTPClient http;
  String serverPath = "http://192.168.43.236:8080/medInfo/alarm";
  
  // Your IP address with path or Domain name with URL path
  http.begin(client, serverPath);
  
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  
  String payload = "false"; 
  
  if (httpResponseCode>0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    //Serial.print("Error code: ");
    //Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void Buzzer()
{

  digitalWrite(buzzPin, LOW);   
  delay(1000);                       
  digitalWrite(buzzPin, HIGH);    
  delay(1000); 
}
