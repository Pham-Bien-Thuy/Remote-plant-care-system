//==================================
//ESP32 WebSocket Server: Toggle LED
//by: Ulas Dikme
//==================================
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ESPmDNS.h>
#include <DHT.h>

const char* ssid = "lab411";
const char* password = "ktttlab411";

#define LED 25
#define PUMP 2
DHT dht(26, DHT11);

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

boolean LEDonoff=false; 
boolean PUMPonoff=false;
String JSONtxt;

#include "html_page.h"
#include "functions.h"

void setup()
{
  Serial.begin(115200); 
  pinMode(LED, OUTPUT);
  pinMode(PUMP, OUTPUT);
  dht.begin();
  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){Serial.print("."); delay(500);}
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", webpage);
  
  server.begin(); webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop()
{
  webSocket.loop(); server.handleClient();

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  String temp = "Nan";
  String hum = "Nan";
  if(isnan(t) || isnan(h))
  {
    //Serial.println("Failed to read from DHT sensor!");
  }
  else {
    //Serial.print("Temperature: ");
    //Serial.println(t);
    temp = String(t);
    //Serial.print("Humidity: ");
    //Serial.println(h);
    hum = String(h);
  }
  
  if(LEDonoff == false) digitalWrite(LED, LOW);
  else digitalWrite(LED, HIGH);
  
  if(PUMPonoff == false) digitalWrite(PUMP, HIGH);
  else digitalWrite(PUMP, LOW);
  
  String LEDstatus = "OFF";
  String PUMPstatus = "OFF";
  if(LEDonoff == true) LEDstatus = "ON";
  if(PUMPonoff == true) PUMPstatus = "ON";
  JSONtxt = "{\"LEDonoff\":\"" +LEDstatus+ "\",\"PUMPonoff\":\"" +PUMPstatus+ "\",\"Temperature\":\"" +temp+ "\",\"Humidity\":\"" +hum+ "\"}";
  webSocket.broadcastTXT(JSONtxt);
}