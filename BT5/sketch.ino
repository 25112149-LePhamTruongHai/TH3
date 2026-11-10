#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "TruongHai";
const char* pass = "123456789";

const char* broker = "test.mosquitto.org";
const char* topicPub = "bcse/th3/nhom-7/counter";
const char* topicSub = "bcse/th3/nhom-7/led";

const int LED = 2;

WiFiClient espClient;
PubSubClient mqtt(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  
  Serial.print("Nhan lenh tu topic ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(msg);

  if (msg == "1") {
    digitalWrite(LED, HIGH);
  } else if (msg == "0") {
    digitalWrite(LED, LOW);
  }
}

void reconnect() {
  while (!mqtt.connected()) {
    Serial.print("Dang ket noi MQTT Broker...");
    if (mqtt.connect("ESP32Client_Nhom7_ID1")) {
      Serial.println("Thanh cong!");
      mqtt.subscribe(topicSub);
    } else {
      Serial.print("That bai, rc=");
      Serial.print(mqtt.state());
      Serial.println(" Thu lai sau 2 giay");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nDa ket noi Wi-Fi!");

  mqtt.setServer(broker, 1883);
  mqtt.setCallback(callback);
}

unsigned long lastMsg = 0;
int dem = 0;

void loop() {
  if (!mqtt.connected()) {
    reconnect();
  }
  mqtt.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    String payload = String(dem++);
    mqtt.publish(topicPub, payload.c_str());
    Serial.print("Da publish: ");
    Serial.println(payload);
  }
}
