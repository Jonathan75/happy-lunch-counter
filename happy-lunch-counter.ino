
// https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display
#include <TFT_eSPI.h>
// Can be installed from the library manager (Search for "TFT_eSPI")
//https://github.com/Bodmer/TFT_eSPI
#include <WiFi.h>
#include <HTTPClient.h>
#include "secrets.h"

#define BLUE_WIRE 22
#define YELLOW_WIRE 27

#define BUTTON_PUSHED_STATE 0
#define BUTTON_NOT_PUSHED_STATE 1


// Used to set the "background" state of the button push.
// Un-pushed button = 1, so start at 1. Then when a push is detected,
// set background state to 0 so that a button hold-down only counts as one push.
int backgroundState = BUTTON_NOT_PUSHED_STATE;

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

void hit_api() {
  String url = "https://catfact.ninja/fact";
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      tft.println(payload);
    }
  } else {
    tft.println("error http get");
  }
}

void setup_button() {
  pinMode(BLUE_WIRE, INPUT_PULLUP);

  pinMode(YELLOW_WIRE, OUTPUT);
  digitalWrite(YELLOW_WIRE, LOW);
}

void check_button() {
  int buttonValue = digitalRead(BLUE_WIRE);

  // Something happened with the button
  if (buttonValue != backgroundState) {
    
    // Button has been released
    if (buttonValue == BUTTON_NOT_PUSHED_STATE) {
      tft.println("Another happy customer.");
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
  tft.println("Hello World!");

}

void setup() {
  setup_screen();
  setup_button();
  setup_wifi();

  hit_api();
}

void loop() {
  check_button();
  delay(50);
}
