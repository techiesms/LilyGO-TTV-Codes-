
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <IRremote.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>
#include <U8g2lib.h>
#include <pcf8563.h>
#include "utilities.h"

U8G2_SSD1309_128X64_NONAME2_F_4W_SW_SPI u8g2(U8G2_R0,
    /* clock=*/ OLED_SCLK,
    /* data=*/  OLED_MOSI,
    /* cs=*/    OLED_CS,
    /* dc=*/    OLED_DC,
    /* reset=*/ OLED_RST);

const char* ssid     = "SSID";
const char* password = "PASS";

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  /*Turn on power control*/
  pinMode(PWR_ON, OUTPUT);
  digitalWrite(PWR_ON, HIGH);

  /*Power on the display*/
  pinMode(OLED_PWR, OUTPUT);
  digitalWrite(OLED_PWR, HIGH);

  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.clearBuffer();

  delay(10);



  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

int value = 0;

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          u8g2.clearBuffer();
          u8g2.setFlipMode(0);
          u8g2.setFontMode(1); // Transparent
          u8g2.setDrawColor(1);
          u8g2.setFontDirection(0);
          u8g2.setCursor(35, 50);
          u8g2.setFont(u8g2_font_inb24_mf);
          u8g2.print( "ON");
          u8g2.nextPage();
          digitalWrite(5, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          u8g2.clearBuffer();
          u8g2.setFlipMode(0);
          u8g2.setFontMode(1); // Transparent
          u8g2.setDrawColor(1);
          u8g2.setFontDirection(0);
          u8g2.setCursor(30, 50);
          u8g2.setFont(u8g2_font_inb24_mf);
          u8g2.print( "OFF");
          u8g2.nextPage();
          digitalWrite(5, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
