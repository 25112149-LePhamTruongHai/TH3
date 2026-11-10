#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);
const int LED = 2; 
bool ledState = false;

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>ESP32 Web Server LED Control</h1>";
  html += "<p>Trang thai LED: ";
  html += (ledState ? "<b style='color:green;'>DANG BAT</b>" : "<b style='color:red;'>DANG TAT</b>");
  html += "</p>";
  html += "<a href='/on'><button style='font-size:20px;padding:10px;'>Bat LED</button></a> ";
  html += "<a href='/off'><button style='font-size:20px;padding:10px;'>Tat LED</button></a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  ledState = true;
  digitalWrite(LED, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  ledState = false;
  digitalWrite(LED, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  WiFi.begin("TruongHai", "123456789");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nDia chi IP cua Web Server: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  
  server.begin();
}

void loop() {
  server.handleClient();
}
