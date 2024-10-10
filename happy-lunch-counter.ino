
// https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display
#include <TFT_eSPI.h>
// Can be installed from the library manager (Search for "TFT_eSPI")
//https://github.com/Bodmer/TFT_eSPI
#include <WiFi.h>

// const char* ssid     = ""; 
// const char* password = "";

const char* ssid     = ""; 
const char* password = "";

TFT_eSPI tft = TFT_eSPI();


void font_9pt(){ 
  tft.setTextSize(1); 
  tft.setFreeFont(&FreeSans9pt7b); 
}
void font_big(){ 
  // tft.setTextSize(2);
  tft.setTextFont(6); 
  tft.setFreeFont(&FreeSans24pt7b); 
  }


void screen_print(String message, int timeout=1000){
  Serial.println(message);
  // tft.drawString(message, 1, 1, 1);
  tft.println(message);
  delay(timeout);
}

String IpAddress2String(const IPAddress& ipAddress)
{
    return String(ipAddress[0]) + String(".") +
           String(ipAddress[1]) + String(".") +
           String(ipAddress[2]) + String(".") +
           String(ipAddress[3]);
}

void wifi_setup(){
  tft.setCursor(0, 15, 15);
  font_9pt();
  screen_print("starting wifi");
  WiFi.begin(ssid, password);
  screen_print("Wifi connecting to ");
  screen_print(ssid);
  while (WiFi.status() != WL_CONNECTED) 
  {
    screen_print("");
    delay(500);
    screen_print("Retry");
  }

  screen_print("");
  screen_print("WiFi connected");
  screen_print("IP address: ");

  // screen_print(IpAddress2String(WiFi.localIP()));
  tft.println(WiFi.localIP());
}

int x = 320 / 2;
int y = 240 / 2;

void setup() {
  // Start the tft display and set it to black
  tft.init();
  tft.setRotation(1); //This is the display in landscape
  
  // Clear the screen before writing to it
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  
  // int fontSize = 4; 
  // tft.drawString("Hello", x, y, fontSize); // Left Aligned
  // x = 320 /2;
  // y += 16;
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // tft.drawCentreString("World", x, y, fontSize);

  /// new 

  
  // tft.fillScreen(TFT_BLACK);
  // tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // tft.drawString(" !\"#$%&'()*+,-./0123456", 0, 0, 12);
  // tft.drawString("789:;<=>?@ABCDEFGHIJKL", 0, 16, 2);
  // tft.drawString("MNOPQRSTUVWXYZ[\\]^_`", 0, 32, 2);
  // tft.drawString("abcdefghijklmnopqrstuvw", 0, 48, 2);
  // int xpos = 0;
  // xpos += tft.drawString("xyz{|}~", 0, 64, 2);
  // tft.drawChar(127, xpos, 64, 2);

  // https://github.com/Bodmer/TFT_eSPI/blob/master/examples/480%20x%20320/Free_Font_Demo/Free_Fonts.h

  
  wifi_setup();
  font_big();
  tft.fillScreen(TFT_BLACK);
}

int count = 0;
void loop() {
  // screen_print(String(count));
  // tft.drawString(String(count), 1, 1, 1);
  // tft.drawCentreString(String(count), x, y, 1);
  tft.fillScreen(TFT_BLACK);
  // tft.drawCentreString(String(count), 50, 50, 2);
  tft.drawCentreString(String(count), 320/2, 240/2.5, 1);
  count += 1;
  delay(1000);
}
