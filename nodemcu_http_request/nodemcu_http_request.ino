#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Dialog 4G 311";
const char* password = "5c8a8aF1";

const char* serverName = "http://192.168.8.151:8080/medInfo";

String rs;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){ 
              
      //rs = httpPOSTRequest(serverName);
      //Serial.println(rs);

      rs = httpGETRequest("893C0E21");
      Serial.println(rs);
      
    }
    else {
      Serial.println("WiFi Disconnected");
    }

    delay(30000);

}

String httpGETRequest(String rfid) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path
  http.begin(client, "http://192.168.8.151:8080/medInfo/"+rfid);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

String httpPOSTRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.POST("/101/Vitamin/Capsule/After meal/50/No/8:30 a.m./1/3:00 p.m./1/9:00 p.m/2");
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
