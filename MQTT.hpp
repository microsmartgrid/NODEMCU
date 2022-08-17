
const char* MQTT_BROKER_ADRESS = "20.125.125.87";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_CLIENT_NAME = "nashey";


WiFiClient espClient;
PubSubClient mqttClient(espClient);

void SuscribeMqtt()
  {
	//mqttClient.subscribe("/edificio1");
  }

String payload;
void PublisMqtt(String data)
{
  mqttClient.publish("/edificio1", (char*)data.c_str());
}

String content = "";
void OnMqttReceived(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Received on ");
  Serial.print(topic);
  Serial.print(": ");

  content = "";
  for (size_t i = 0; i < length; i++) {
    content.concat((char)payload[i]);
  }
  Serial.print(content);
  Serial.println();
}
