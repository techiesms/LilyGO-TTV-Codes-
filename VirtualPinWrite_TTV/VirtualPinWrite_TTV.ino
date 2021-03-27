
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <IRremote.h>
#include <U8g2lib.h>
#include "utilities.h"


U8G2_SSD1309_128X64_NONAME2_F_4W_SW_SPI u8g2(U8G2_R0,
    /* clock=*/ OLED_SCLK,
    /* data=*/  OLED_MOSI,
    /* cs=*/    OLED_CS,
    /* dc=*/    OLED_DC,
    /* reset=*/ OLED_RST);

IRrecv irrecv(IR_RECV);
decode_results results;
WiFiMulti wifiMulti;


void setup()
{
  // Debug console
  Serial.begin(115200);

  /*Turn on power control*/
  pinMode(PWR_ON, OUTPUT);
  digitalWrite(PWR_ON, HIGH);

  /*Power on the display*/
  pinMode(OLED_PWR, OUTPUT);
  digitalWrite(OLED_PWR, HIGH);

  /*Set touch Pin as input*/
  pinMode(TOUCH_PIN, INPUT);

  /*Touch chip power control*/
  pinMode(TOUCH_PWR, PULLUP);
  digitalWrite(TOUCH_PWR, HIGH);

  int16_t ypos = 16;

  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.clearBuffer();

  irrecv.enableIRIn(); // Start the receiver
  wifiMulti.addAP("SSID", "PASS");

  u8g2.clearBuffer();
  u8g2.setFlipMode(0);
  u8g2.setFontMode(1); // Transparent
  u8g2.setDrawColor(1);
  u8g2.setFontDirection(0);
  u8g2.setCursor(9, 40);
  u8g2.setFont(u8g2_font_inb24_mf);
  u8g2.print( "Blynk");
  u8g2.nextPage();

}

void loop()
{
  ir_function();

}

void ir_function()
{
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 0xFFA25D:  //CH-   //off
        break;
      case 0xFF629D:  //CH
        break;
      case 0xFFE21D:  //CH+
        break;
      case 0xFF6897:  //0
        break;
      case 0xFF9867:  //100+
        break;
      case 0xFFB04F:  //200+
        break;
      case 0xFF30CF:  //1
        u8g2.clearBuffer();
        u8g2.setFlipMode(0);
        u8g2.setFontMode(1); // Transparent
        u8g2.setDrawColor(1);
        u8g2.setFontDirection(0);
        u8g2.setCursor(40, 35);
        u8g2.setFont(u8g2_font_luRS08_tf);
        u8g2.print( "Bulb1 OFF");
        u8g2.nextPage();
        if ((wifiMulti.run() == WL_CONNECTED)) {

          HTTPClient http;

          Serial.print("[HTTP] begin...\n");
          // configure traged server and url
          //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
          http.begin("http://blynk-cloud.com/YOUR_AUTH_TOKEN/update/V1?value=1"); //HTTP

          Serial.print("[HTTP] GET...\n");
          // start connection and send HTTP header
          int httpCode = http.GET();

          // httpCode will be negative on error
          if (httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              Serial.println(payload);
            }
          } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }

          http.end();
        }
        break;
      case 0xFF18E7:  //2
        u8g2.clearBuffer();
        u8g2.setFlipMode(0);
        u8g2.setFontMode(1); // Transparent
        u8g2.setDrawColor(1);
        u8g2.setFontDirection(0);
        u8g2.setCursor(40, 35);
        u8g2.setFont(u8g2_font_luRS08_tf);
        u8g2.print( "Bulb1 ON");
        u8g2.nextPage();
        if ((wifiMulti.run() == WL_CONNECTED)) {

          HTTPClient http;

          Serial.print("[HTTP] begin...\n");
          // configure traged server and url
          //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
          http.begin("http://blynk-cloud.com/YOUR_AUTH_TOKEN/update/V1?value=0"); //HTTP

          Serial.print("[HTTP] GET...\n");
          // start connection and send HTTP header
          int httpCode = http.GET();

          // httpCode will be negative on error
          if (httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              Serial.println(payload);
            }
          } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }

          http.end();
        }
        break;
      case 0xFF7A85://3
        u8g2.clearBuffer();
        u8g2.setFlipMode(0);
        u8g2.setFontMode(1); // Transparent
        u8g2.setDrawColor(1);
        u8g2.setFontDirection(0);
        u8g2.setCursor(40, 35);
        u8g2.setFont(u8g2_font_luRS08_tf);
        u8g2.print( "Bulb2 OFF");
        u8g2.nextPage();
        if ((wifiMulti.run() == WL_CONNECTED)) {

          HTTPClient http;

          Serial.print("[HTTP] begin...\n");
          // configure traged server and url
          //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
          http.begin("http://blynk-cloud.com/YOUR_AUTH_TOKEN/update/V2?value=1"); //HTTP

          Serial.print("[HTTP] GET...\n");
          // start connection and send HTTP header
          int httpCode = http.GET();

          // httpCode will be negative on error
          if (httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              Serial.println(payload);
            }
          } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }

          http.end();
        }
        break;
      case 0xFF10EF://4
        u8g2.clearBuffer();
        u8g2.setFlipMode(0);
        u8g2.setFontMode(1); // Transparent
        u8g2.setDrawColor(1);
        u8g2.setFontDirection(0);
        u8g2.setCursor(40, 35);
        u8g2.setFont(u8g2_font_luRS08_tf);
        u8g2.print( "Bulb2 ON");
        u8g2.nextPage();
        if ((wifiMulti.run() == WL_CONNECTED)) {

          HTTPClient http;

          Serial.print("[HTTP] begin...\n");
          // configure traged server and url
          //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
          http.begin("http://blynk-cloud.com/YOUR_AUTH_TOKEN/update/V2?value=0"); //HTTP

          Serial.print("[HTTP] GET...\n");
          // start connection and send HTTP header
          int httpCode = http.GET();

          // httpCode will be negative on error
          if (httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              Serial.println(payload);
            }
          } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }

          http.end();
        }
        break;
      case 0xFF38C7://5
        break;
      case 0xFF5AA5://6
        break;
      case 0xFF42BD://7
        break;
      case 0xFF4AB5://8
        break;
      case 0xFF52AD://9
        break;
      case 0xFFA857:  //+
        break;
      case 0xFFE01F:  // -
        break;
      case 0xFF22DD://NEXT
        break;
      case 0xFFC23D://PLAY
        break;
      case 0xFF02FD://PREV
        break;
      case 0xFF906F:  //EQ
        break;
      default:
        break;
    }
    irrecv.resume(); // Receive the next value
  }

}
