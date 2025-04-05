/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com

  Modified by Dr J for PHYS231 SP21:
    fixed typos
    acquire and display MAC address for connection to UNC PSK network
    changed notation from GPIO pin number to LED descriptor
    reversed source/sink logic – VERY COOL EXAM QUESTION - ask on Discord!!!!!
    various cool tweaks
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "Mishuzone";
const char* password = "chuchu66";
const char *yourname = "Michael Woods"; // don't show a video with Dr J's name in it

char web_server_title[100];

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliary variables to store the current output state
String ESP12_LED_State = "off";
String nodeMCU_LED_State = "off";

// Assign output variables to GPIO pins
const int ESP12_LED = 2;    //this is the LED by the antenna
const int nodeMCU_LED = 16; //this is the LED by the USB connector

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// reversed source/sink logic
// you should probably ask about this on Discord
#define lo HIGH
#define hi LOW

void setup() {
  Serial.begin(115200);
  delay(3000);
  // Initialize the output variables as outputs
  pinMode(ESP12_LED, OUTPUT);
  pinMode(nodeMCU_LED, OUTPUT);
  // Turn LEDs off
  digitalWrite(ESP12_LED, lo);
  digitalWrite(nodeMCU_LED, lo);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("My MAC address is ");
  Serial.println(WiFi.macAddress());
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.print("WiFi connected to IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
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
            if (header.indexOf("GET /ESP12_LED_State/on") >= 0) {
              Serial.println("ESP12_LED on");
              ESP12_LED_State = "on";
              digitalWrite(ESP12_LED, hi);
            } else if (header.indexOf("GET /ESP12_LED_State/off") >= 0) {
              Serial.println("ESP12_LED off");
              ESP12_LED_State = "off";
              digitalWrite(ESP12_LED, lo);
            } else if (header.indexOf("GET /nodeMCU_LED_State/on") >= 0) {
              Serial.println("nodeMCU_LED on");
              nodeMCU_LED_State = "on";
              digitalWrite(nodeMCU_LED, hi);
            } else if (header.indexOf("GET /nodeMCU_LED_State/off") >= 0) {
              Serial.println("nodeMCU_LED off");
              nodeMCU_LED_State = "off";
              digitalWrite(nodeMCU_LED, lo);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");

            // Web Page Heading
            snprintf(web_server_title, 100, "<body><h1>%s's ESP8266 Web Server</h1>", yourname);
            client.println(web_server_title);

            // Display current state, and ON/OFF buttons for ESP12_LED
            client.println("<p>ESP12_LED (near antenna): Current state is " + ESP12_LED_State + "</p>");
            // If the ESP12_LED_State is off, it displays the TURN ON button
            if (ESP12_LED_State == "off") {
              client.println("<p><a href=\"/ESP12_LED_State/on\"><button class=\"button\">TURN ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/ESP12_LED_State/off\"><button class=\"button button2\">TURN OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for nodeMCU_LED
            client.println("<p>nodeMCU_LED (near USB): Current State is " + nodeMCU_LED_State + "</p>");
            // If the nodeMCU_LED_State is off, it displays the TURN ON button
            if (nodeMCU_LED_State == "off") {
              client.println("<p><a href=\"/nodeMCU_LED_State/on\"><button class=\"button\">TURN ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/nodeMCU_LED_State/off\"><button class=\"button button2\">TURN OFF</button></a></p>");
            }
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
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
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
