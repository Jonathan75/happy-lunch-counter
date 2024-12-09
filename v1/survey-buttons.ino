// Based on https://www.instructables.com/id/-Arduinolitics-Google-Analytics-on-Arduino/
#include <ESP8266WiFi.h>
#include "config.h"
#include "melody.h"

const char* host = "www.google-analytics.com";
const int httpPort = 80;
int deviceID = 0; 
int trackingVersion = 1;

void setup() {
  Serial.begin(115200);
  Serial.println("Running Setup...");
  delay(1000);
  pinMode(D0, OUTPUT);
  pinMode(D1,INPUT_PULLUP);
  pinMode(D2,INPUT_PULLUP);
  pinMode(D4,INPUT_PULLUP);
  pinMode(D5,INPUT_PULLUP);
  pinMode(D6,INPUT_PULLUP);
  pinMode(D8,OUTPUT);
  
  randomSeed(analogRead(0));
  if (deviceID == 0) {
    deviceID = random(1000);    
  } 
  Serial.print("Device ID");
  Serial.println(deviceID);
  
  Serial.print("SSID ");
  Serial.println(WIFI_SSID);
  Serial.print("password ");
  Serial.println(WIFI_PASSWORD);
    
  Serial.print("WIFI connecting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    blinkLed();
  }
  
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  trackEvent("PowerON","MAC:" + String(WiFi.macAddress()),"1");
}


void loop() {
  int button_value = 0;  
  if (digitalRead(D1) == LOW) button_value = 1;
  if (digitalRead(D2) == LOW) button_value = 2;
  if (digitalRead(D4) == LOW) button_value = 3;
  if (digitalRead(D5) == LOW) button_value = 4;
  if (digitalRead(D6) == LOW) button_value = 5;
  if (button_value > 0 ) button_press(button_value);
}


void button_press(int value){
  if (value >= 3) 
    play_melody(happy_melody, happy_tempo, sizeof(happy_melody) / sizeof(int));    
  else 
    play_melody(underworld_melody, underworld_tempo, sizeof(underworld_melody) / sizeof(int));    
  
  trackEvent("Miranova-Floor5-BusA",String(value),String(value));
  }

void trackEvent(String action,String label,String value) {
  String payloadType = "event"; // Must be one of 'pageview', 'appview', 'event', 'transaction', 'item', 'social', 'exception', 'timing'.
  String payloadCategory = "Culinary";

  String payloadData = "v=";
        payloadData += trackingVersion;
        payloadData += "&tid=";
        payloadData += trackingID;
        payloadData += "&cid=";
        payloadData += deviceID;
        payloadData += "&t=";
        payloadData += payloadType;
        payloadData += "&ec=";
        payloadData += payloadCategory;
        payloadData += "&ea=";
        payloadData += action;
        payloadData += "&el=";
        payloadData += label;
        payloadData += "&ev=";
        payloadData += value;

  Serial.print("PAYLOAD: ");
  Serial.println(payloadData);

  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


  //CONNECT
  int retryCount = 10;

  //SEND TRACKING DATA
  if (client.connected()) {
    client.println("POST /collect HTTP/1.1");
    client.println("Host: www.google-analytics.com");
    client.print("Content-Length: ");
    client.println(payloadData.length());
    client.println();
    client.print(payloadData);
    client.println();
    Serial.print("connected: ");
    Serial.print(client.connected());
    Serial.print("    Avaliable: ");
    Serial.print(client.available());
    Serial.print("\n");
  } else {
    Serial.println("failed.. just skipping a beat for now");
  }
  
  //CHECK RESPONSE
  retryCount = 10;
  while(!client.available() && retryCount > 0) {
    retryCount--;
    client.println();
    Serial.print("Avaliable-loop: ");
    Serial.print(client.available());
    Serial.print("\n");
    delay(100);//actually lost speed removing delay in retry here
  }
  int responseSize = 0;
  while (client.available()) {
    char c = client.read();
    responseSize++;// Serial.print(c); <-- Break comments for serious debugging
  }
  Serial.print("Response size: ");
  Serial.println(responseSize);
}

void ledOn(){digitalWrite(LED_BUILTIN, 0);}
void ledOff(){digitalWrite(LED_BUILTIN, 1);}

void blinkLed() {
  analogWrite(0, 1);
  int blinkCount = 20;
  int delayTime = 20;
  
  for (int i=0; i <= blinkCount; i++){
    digitalWrite(LED_BUILTIN, 0);
    delay(delayTime);
    digitalWrite(LED_BUILTIN, 1);
    delay(delayTime);
  }
  digitalWrite(LED_BUILTIN, 1);
  delay(1000);
}
