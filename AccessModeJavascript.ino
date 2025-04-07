/*  Rick Ramirez SP21 PHYS231

  The following code was adapted from https://github.com/acrobotic/Ai_Demos_ESP8266
  Looked around and found examples of what I needed
  WebSocket seemed the be the easiest to implement and has room to add more features

  Links to download LittleFS:
  https://github.com/esp8266/Arduino/blob/master/doc/filesystem.rst
  https://github.com/earlephilhower/arduino-esp8266littlefs-plugin/releases

  Link to Chart.js min
  https://cdn.jsdelivr.net/npm/chart.js@2.9.4/dist/Chart.min.js

  Using Wifi, Webserver, WebSocket, LittleFS (to upload a javascript libray), Ticker (a timer)
  An easier method would be connecting to wifi to download the library but the point of this lab was not to do that :^)

  Dr J + GregH updates for SP22
    Restructure code to remove the include of ESP8266Wifi.h; not needed!
    Added use of softAPIP() ot get IP address
    Added MAC address call
    Added (but commented out) heartbeat timer – interferes with update rate of Chart?
    Updates for clarity and functionality
*/
// the ESP8266WebServer.h line will not compile unless
//  you have selected nodeMCU as your board.
//  Be sure to upgrade to ESP8266 >= v3.0.2 in the Boards Manager (not Library Manager!).
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <LittleFS.h>
#include <Ticker.h>

// instantiate server object and Web Socket
ESP8266WebServer server;
WebSocketsServer webSocket = WebSocketsServer(81);

// define the network you are going to connect to
char ssid[] = "choofzone";
char password[] = "womenmoment";

// declare a timer variable
Ticker timer;

// bool for data flag
bool read_data = false;
#include "html.h";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  LittleFS.begin(); // this is serving up Chart.js

  delay(1000);
  Serial.begin(115200);
  while(!Serial){
  }
  Serial.println();
  Serial.println("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP(); // default IP should be 192.168.4.1
  Serial.print("My Access Point IP address is ");
  Serial.println(myIP);
  Serial.print("My MAC address is ");
  Serial.println(WiFi.macAddress());
  Serial.print("My SSID is ");
  Serial.print(ssid);
  Serial.println(" - YOU MUST CONNECT YOUR LAPTOP TO THIS SSID.");
  Serial.print("password: ");
  Serial.println("Shhh - don't tell anybody!!");
  // define the routes the server will use
  server.on("/", []() {
    server.send_P(200, "text/html", webpage);
  });
  server.on("/Chart.js", serveChartFile); // The route below assumes you have Chart.js downloaded into the NodeMCU's flash mem

  // Begin our processes
  server.begin();
  //Serial.println("HTTP server started");
  webSocket.begin();
  //Serial.println("WebSocket Instantiated");

  // initialize timer function
  //Serial.println("This is readData: ");
  //Serial.println(read_data);
  timer.attach(/*rate in secs*/ 0.1, /*function*/ readData);

  // not planning on receiving any data from the client but if we were:
  // webSocket.onEvent(webSocketEvent);
}

void readData() {
  Serial.println("Ticker readData() triggered!");
  // should only be used to set/unset flags
  read_data = true;
  Serial.println((read_data));
}

void serveChartFile() {
  // Stream the Chart.js file using LittleFS
  File file = LittleFS.open("/Chart.js", "r");
  server.streamFile(file, "text/javascript");
  file.close();
}


void loop() {

  //Serial.println("In the loop");
  //Serial.println(read_data);
  webSocket.loop();
  server.handleClient();
  if (read_data) {
    
    // build the JSON-formatted string for sending over the websocket
    // in this case just read the pot value from A0
    String json = "{\"value\":";
    json += analogRead(A0);
    json += "}";
    webSocket.broadcastTXT(json.c_str(), json.length());

    //   reset the flag
    read_data = false;
    // 100 ms heartbeat timer: testing only
    //    be careful, as this can heartbeat rate can interfere with the javascript timing
    //digitalWrite(LED_BUILTIN, HIGH); delay(100);
    //digitalWrite(LED_BUILTIN,  LOW); delay(100);

  }
}
