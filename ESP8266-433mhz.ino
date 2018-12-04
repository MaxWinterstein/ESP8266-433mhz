#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <RCSwitch.h>

// --- Replace with your network credentials ---
const char* ssid = "";
const char* password = "";
// --- Replace with your network credentials ---

RCSwitch mySwitch = RCSwitch();
MDNSResponder mdns;
ESP8266WebServer server(80);

const String helpStr = "Usage: \n"
  "/changestate/housecode=<housecode>&socketcode=<socketcode>&state=<state> \n"
  "e.g.: \n"
  "/changestate/housecode=01001&socketcode=10001&state=on";


void setup(void) {
  Serial.begin(115200);
  
  mySwitch.enableTransmit(2);
  delay(1000);
  
  WiFi.mode(WIFI_STA);
  WiFi.hostname("ESP-433-Gateway");
  WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // serial output of connection details
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (mdns.begin("ESP-433-Gateway", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() {
    server.send(200, "text/plain", helpStr);
  });
  
  server.on("/changestate", changestate);

  server.begin();
  Serial.println("HTTP server started");
}


void changestate() {
  String house = server.arg("housecode");
  const char*  housecode = house.c_str();
  String socket = server.arg("socketcode");
  const char*  socketcode = socket.c_str();
  String state = server.arg("state").c_str();

  Serial.println("/changestate");
  Serial.print("housecode:\t");
  Serial.println(housecode);
  Serial.print("socketcode:\t");
  Serial.println(socketcode);
  Serial.print("state:\t\t");
  Serial.println(state);

  if (state == "off")
  {
    mySwitch.switchOff(housecode, socketcode);
    server.send(200, "text/plain", "ok");
  }
  else if (state == "on")
  {
    mySwitch.switchOn(housecode, socketcode);
    server.send(200, "text/plain", "ok");
  }

}


void loop(void) {
  server.handleClient();
}
