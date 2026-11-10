#include <WiFi.h>

const char* ssid = "Nhom7";
const char* pass = "123456789";

void setup() {
Serial.begin(115200);
WiFi.begin(ssid, pass);
while (WiFi.status()!=WL_CONNECTED){
delay(500); Serial.print(".");
}
Serial.print("\nIP: ");
Serial.println(WiFi.localIP());
}
void loop() {}
