
// https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display
#include <TFT_eSPI.h>
// Can be installed from the library manager (Search for "TFT_eSPI")
//https://github.com/Bodmer/TFT_eSPI
#include <WiFi.h>
#include <HTTPClient.h>
#include "secrets.h"
// https://github.com/bblanchon/ArduinoJson
#include <ArduinoJson.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define BLUE_WIRE 22
#define YELLOW_WIRE 27

#define BUTTON_PUSHED_STATE 0
#define BUTTON_NOT_PUSHED_STATE 1


// Used to set the "background" state of the button push.
// Un-pushed button = 1, so start at 1. Then when a push is detected,
// set background state to 0 so that a button hold-down only counts as one push.
int backgroundState = BUTTON_NOT_PUSHED_STATE;

int customerCount = 0;

TFT_eSPI tft = TFT_eSPI();

void setup_wifi(){
  WiFi.begin(SSID, PASSWORD);
  tft.print("connecting to wifi");

  while (WiFi.status() != WL_CONNECTED) 
  {
    tft.print(".");
    delay(1000);
  }
  tft.println("");
  tft.println("connected to wifi");
}

const char* get_cat_fact() {
  String url = "https://catfact.ninja/fact";
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();

      // Deserialize the JSON, grabbing the 'fact' value
      JsonDocument doc;
      deserializeJson(doc, payload);
      const char* fact = doc["fact"];

      return fact;
    }
  } else {
    return "";
  }
}

void setup_button() {
  pinMode(BLUE_WIRE, INPUT_PULLUP);

  pinMode(YELLOW_WIRE, OUTPUT);
  digitalWrite(YELLOW_WIRE, LOW);
}

void increment_customer_count() {
  customerCount += 1;
}

void show_customer_count() {
  tft.fillScreen(TFT_BLACK); // Clear the screen before writing to it
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // White text on a black background
  tft.setFreeFont(&FreeSans24pt7b);
  tft.drawCentreString(String(customerCount), SCREEN_WIDTH/2, SCREEN_HEIGHT/5 - 25, 1);

  tft.setFreeFont(&FreeSans18pt7b);
  const char* customerMessage = customerCount == 1 ? "Happy Customer" : "Happy Customers";
  tft.drawCentreString(customerMessage, SCREEN_WIDTH/2, SCREEN_HEIGHT/5 + 25, 1);

  // Show a fun cat fact to demonstrate internet connectivity / hitting an API
  const char* catFact = get_cat_fact();

  tft.setFreeFont(&FreeSans12pt7b);
  tft.setCursor(0, SCREEN_HEIGHT/2 + 30, 1); // Acceptable margins so the text is not off-screen
  tft.println(catFact);

  // tft.drawCentreString(catFact, SCREEN_WIDTH/2, SCREEN_HEIGHT/2.5 + 50, 1);
}

void customer_detected() {
  increment_customer_count();
  show_customer_count();
}

void check_button() {
  int buttonValue = digitalRead(BLUE_WIRE);

  // Something happened with the button
  if (buttonValue != backgroundState) {
    
    // Button has been released
    if (buttonValue == BUTTON_NOT_PUSHED_STATE) {
      customer_detected();
    }

    // The button down-ness switched so the background state also switched because
    // it is the opposite of the down-ness.
    // If the button is pressed, the background state is un-pressed. And vice versa.
    backgroundState = !backgroundState;
  }
}

void setup_screen() {
  tft.init();
  tft.setRotation(1); // This is the display in landscape
  tft.fillScreen(TFT_BLACK); // Clear the screen before writing to it
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // White text on a black background
  tft.setFreeFont(&FreeSans9pt7b); // Small font
  tft.setCursor(0, 9, 9); // Acceptable margins so the text is not off-screen
  tft.println("Hello, World! Enjoy your lunch.");
}

unsigned long last_count_reset = 0; 
void reset_count(){
  // if current seconds - last reset is more then 12 hours
  if (millis()/1000 - last_count_reset > 12*60*60) {
    Serial.println("customer count reset");
    tft.println("Count Reset");
    customerCount = 0;
    last_count_reset= millis()/1000;
  }
}

void setup() {
  Serial.begin(9600);
  setup_screen();
  setup_button();
  setup_wifi();
}

void loop() {
  check_button();
  reset_count();
  delay(50);
}
