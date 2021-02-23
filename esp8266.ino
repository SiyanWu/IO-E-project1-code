#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <PubSubClient.h>
const char* ssid = "abcd";
const char* password = "12345678";
#define IP  "183.230.40.39"
#define MQTT_PORT 6002
#define PRODUCT_ID    "404894"
#define DEVICE_ID    "684949185"
#define API_KEY    "dvGX=5TeA=dvqpt41yMSOrN0we0="
#define HOST  "api.heclouds.com"

String readString;
WiFiClient espClient;
PubSubClient client(espClient);
HTTPClient http;
void callback(char *topic, byte * payload, unsigned int length) {
  String luminance = "";
  for (int i = 0; i < length; i++) {
    luminance += (char) payload[i];
  }
  analogWrite(12, luminance.toInt());
  Serial.print(luminance);
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  pinMode(12, OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  client.setServer(IP, MQTT_PORT);
  client.setCallback(callback);
  while (!client.connected()) {

    client.connect(DEVICE_ID, PRODUCT_ID, API_KEY);

  }
}




void loop() {


  client.loop();


}
