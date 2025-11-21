#include <WiFi.h>
#include <PubSubClient.h>
#include "ACS712.h"
#include <ZMPT101B.h>

// --- CONFIGURE THESE ---
const char* ssid = "qwerty";
const char* password = "12345678";
const char* mqtt_server = "192.168.6.213"; // Edge device (MQTT broker)
// ------------------------

WiFiClient espClient;
PubSubClient client(espClient);

#define RELAY_PIN 25 // change pin if needed for Node2 wiring

// Sensors: Node2 uses a different sensitivity in the report
ACS712 ACS(34, 3.3, 4095, 185);   // calibration for node2 (from report)
ZMPT101B voltageSensor(35, 50.0);

float current_mA = 0.0;
float voltage_V = 0.0;

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) message += (char)payload[i];
  message.trim();

  if (message == "OFF") {
    digitalWrite(RELAY_PIN, LOW);
  } else if (message == "ON") {
    digitalWrite(RELAY_PIN, HIGH);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("node2")) {
      client.subscribe("ems/node2/control");
    } else {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay default ON

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

float readCurrent_mA() {
  float sum = 0.0;
  for (int i = 0; i < 200; i++) {
    sum += ACS.mA_AC();
  }
  float avg_mA = sum / 200.0;
  return (avg_mA > 1.0) ? avg_mA : 0.0; // filter tiny noise
}

float readVoltage_V() {
  float v = voltageSensor.getRmsVoltage();
  return (v > 50.0) ? v : 0.0;
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  current_mA = readCurrent_mA();
  voltage_V = readVoltage_V();

  float current_A = current_mA / 1000.0;
  char payload[80];
  snprintf(payload, sizeof(payload), "{\"voltage\":%.2f,\"current\":%.3f}", voltage_V, current_A);

  client.publish("ems/node2/data", payload);
  delay(2000); // publish every 2 seconds
}
