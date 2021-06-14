// by : Trezen Parmar

/* This project sends the sensor data to cloud, according the predefined threshold
   value of sensor if value exeeded the predefined threshold then it sends notification on mobile via IFTTT service,
   we can directly then turn the appliances ON and OFF according to our choice with our integrated home automation service.

    details :
    components : nodeMCU, LDR, relays, LEDs, resistors, jumper wires, thingspeak account,
    IFTTT account, internet service(Mobile Hotspot).

    connections :
    1)For LDR connect A0 pin at the junction of LDR and resistor, ground pin
      to end of resistor and 3.3v power to another leg of LDR.
    2)For relays connect vcc to 3.3v power, IN1 to D1, IN2 to D2, GND to ground.
      connect the appliances as normally close on the other end of relays.
*/
#include "ThingSpeak.h"
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>

const int rs = D7, en = D8, d4 = D6, d5 = D5, d6 = D4, d7 = D3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long myChannelNumber = 1397040;
const char * myWriteAPIKey = "F1APS5LR9U3ZEUEH";
char SECRET_SSID[] = "Redmi";
char SECRET_PASS[] = "7984891023";
char ssid[] = "Redmi";
char pass[] = "7984891023";
int keyIndex = 0;            // your network key index number (needed only for WEP)


WiFiServer server(80);

String header; // This stores the HTTP request

int relay1 = D1;
int relay2 = D2;

String relay1state = "off";// state of relayliance1
String relay2state = "off";// state of relayliance2

void setup() {
  Serial.begin(115200);
  delay(100);
  WiFi.mode(WIFI_STA);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  lcd.begin(16, 2);
}

void loop() {

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
    Serial.print("Got IP : ");
    Serial.println(WiFi.localIP());
    Serial.println("HTTP server started");
  }
    lcd.setCursor(0, 0);
    lcd.print(WiFi.localIP());
    
  server.begin();
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /relay1/on") >= 0) {
              Serial.println("relay 1 off");
              relay1state = "on";
              digitalWrite(relay1, HIGH);
              lcd.setCursor(0, 1);
              lcd.print("");
              lcd.print("R1-OFF");
              
            } else if (header.indexOf("GET /relay1/off") >= 0) {
              Serial.println("relay 1 on");
              relay1state = "off";
              digitalWrite(relay1, LOW);
              lcd.setCursor(0, 1);
              lcd.print("");
              lcd.print(" R1-ON");
              
            } else if (header.indexOf("GET /relay2/on") >= 0) {
              Serial.println("relay 2 off");
              relay2state = "on";
              digitalWrite(relay2, HIGH);
              lcd.setCursor(0, 1);
              lcd.print("");
              lcd.print("R2-OFF");
              
              
            } else if (header.indexOf("GET /relay2/off") >= 0) {
              Serial.println("relay 2 on");
              relay2state = "off";
              digitalWrite(relay2, LOW);
              lcd.setCursor(0, 1);
              lcd.print("");
              lcd.print(" R2-ON");
              
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");

            client.println("<body><h1>Click to turn ON and OFF devices</h1>");
            client.println("<h2>The button status displays the current status of devices</h2>");

            client.println("<p>Relay 1</p>");
            // If relayliance 1 is off, it displays the ON button
            if (relay1state == "off") {
              client.println("<p><a href=\"/relay1/on\"><button class=\"button\">ON</button></a></p>");
              client.println("<p>click to turn off</p>");
            } else {
              client.println("<p><a href=\"/relay1/off\"><button class=\"button button2\">OFF</button></a></p>");
              client.println("<p>click to turn on</p>");
            }

            client.println("<p>Relay 2</p>");
            // If relayliance 2 is off, it displays the ON button
            if (relay2state == "off") {
              client.println("<p><a href=\"/relay2/on\"><button class=\"button\">ON</button></a></p>");
              client.println("<p>click to turn off</p>");
            } else {
              client.println("<p><a href=\"/relay2/off\"><button class=\"button button2\">OFF</button></a></p>");
              client.println("<p>click to turn on</p>");
            }
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            break;
          }
          else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
  }
  
  thingspeak();  // function to send data to thingspeak cloud
}

void thingspeak() {
  WiFiClient  client;
  ThingSpeak.begin(client);
  int valueA0 = analogRead(A0);

  // Write value to Field 1 of a ThingSpeak Channel

  int httpCode = ThingSpeak.writeField(myChannelNumber, 1, valueA0, myWriteAPIKey);

  if (httpCode == 200) {
    Serial.println("Channel write successful.");
    Serial.println(valueA0);
  }
}
