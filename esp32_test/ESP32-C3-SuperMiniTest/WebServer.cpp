

/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <Arduino.h>
#include <WiFi.h>

#include "Parameters.h"


// ---------- WiFi ----------
const char* ssid = "ASUS_98_2G";
const char* password = "LiDoDa#959285$";
//const char* ssid     = "HUAWEI P30";
//const char* password = "6381bf07b666";

NetworkServer server(80);

void setupWebServer() {

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
  Serial.println("Server started");
}

void loopWebServer() {
    NetworkClient client = server.accept();  // listen for incoming clients

    if (client) {                     // if you get a client,
        Serial.println("New Client.");  // print a message out the serial port
        String currentLine = "";        // make a String to hold incoming data from the client
        while (client.connected()) {    // loop while the client's connected
            if (client.available()) {     // if there's bytes to read from the client,
                char c = client.read();     // read a byte, then
                Serial.write(c);            // print it out the serial monitor
                if (c == '\n') {            // if the byte is a newline character

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
                    }
                    else {  // if you got a newline, then clear currentLine:
                        currentLine = "";
                    }
                }
                else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }

                // Check to see if the client request was "GET /H" or "GET /L":
                if (currentLine.endsWith("GET /H")) {
                    digitalWrite(LED_PIN, HIGH);  // GET /H turns the LED on
                }
                if (currentLine.endsWith("GET /L")) {
                    digitalWrite(LED_PIN, LOW);  // GET /L turns the LED off
                }
            }
        }
        // close the connection:
        client.stop();
        Serial.println("Client Disconnected.");
    }
}
