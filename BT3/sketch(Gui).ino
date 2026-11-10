#include <WiFi.h>
#include <esp_now.h>

uint8_t macNhan[] = {0x24, 0x0A, 0xC4, 0x12, 0x34, 0x56};

typedef struct { int dem; } GoiTin;
GoiTin goi;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  esp_now_init();

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, macNhan, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  esp_now_add_peer(&peerInfo);
}

void loop() {
  goi.dem++;
  esp_now_send(macNhan, (uint8_t *)&goi, sizeof(goi));
  delay(2000);
}
