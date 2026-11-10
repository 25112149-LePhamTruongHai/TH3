#include <WiFi.h>
#include <esp_now.h>

typedef struct { int dem; } GoiTin;
GoiTin goi;

void onRecv(const uint8_t *mac, const uint8_t *data, int len) {
  memcpy(&goi, data, sizeof(goi));
  Serial.print("Nhan dem = ");
  Serial.println(goi.dem);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(onRecv);
}

void loop() {}
