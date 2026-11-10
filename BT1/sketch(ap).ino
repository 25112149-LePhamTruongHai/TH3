#include <WiFi.h>

const char* ssid = "Nhom7";
const char* pass = "123456789";

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, pass);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {}
