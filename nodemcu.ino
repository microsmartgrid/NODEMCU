#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <StringSplitter.h>
#include "parser.h"
#include "config.h"
#include "MQTT.hpp"
#include "ESP8266_Utils.hpp"
#include "ESP8266_Utils_MQTT.hpp"

String incomingDatos;

void setup(void)
{
  Serial.begin(115200);
  SPIFFS.begin();
  ConnectWiFi_STA(true);
  GetExternalIP();
  InitMqtt();
}

void loop()
{
  HandleMqtt();
  if (Serial.available())
  {
    incomingDatos = getFromTerminal();
    PublisMqtt(incomingDatos);
  }

}


void GetExternalIP()
{
  WiFiClient client;
  if (!client.connect("api.ipify.org", 80)) {
    Serial.println("Failed to connect with 'api.ipify.org' !");
  }
  else {
    int timeout = millis() + 5000;
    client.print("GET /?format=json HTTP/1.1\r\nHost: api.ipify.org\r\n\r\n");
    while (client.available() == 0) {
      if (timeout - millis() < 0) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    int size;
    while ((size = client.available()) > 0) {
      uint8_t* msg = (uint8_t*)malloc(size);
      size = client.read(msg, size);
      Serial.write(msg, size);
      free(msg);
    }
  }
}
