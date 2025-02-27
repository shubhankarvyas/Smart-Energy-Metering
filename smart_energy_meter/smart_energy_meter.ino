#include "EmonLib.h" // Include EmonLib for energy monitoring
#include <EEPROM.h>  // Include EEPROM for saving data
#include <WiFi.h>    // Include WiFi library
#include <PubSubClient.h> // Include PubSubClient for MQTT

// Constants for calibration
const float vCalibration = 41.5;
const float currCalibration = 0.15;

// WiFi credentials
const char* ssid = "vivo Y35";
const char* password = "12345678";

// MQTT broker details
const char* mqtt_server = "192.168.1.100"; // Replace with your MQTT broker IP
const char* mqtt_topic = "energy_meter/data";

// EnergyMonitor instance
EnergyMonitor emon; 

// MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

// Variables for energy calculation
float kWh = 0.0;
unsigned long lastMillis = millis();

// EEPROM addresses for variables
const int addrKWh = 0;

// Function prototypes
void connectWiFi();
void connectMQTT();
void sendEnergyDataToNodeRed();
void readEnergyDataFromEEPROM();
void saveEnergyDataToEEPROM();

void setup()
{
  Serial.begin(115200);

  // Connect to WiFi
  connectWiFi();

  // Configure MQTT
  client.setServer(mqtt_server, 1883);

  // Initialize EEPROM
  EEPROM.begin(32);

  // Read stored kWh value
  readEnergyDataFromEEPROM();

  // Setup voltage and current inputs
  emon.voltage(35, vCalibration, 1.7); // Voltage: input pin, calibration, phase_shift
  emon.current(34, currCalibration);  // Current: input pin, calibration

  // Allow the system to stabilize
  delay(1000);
}

void loop()
{
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();

  // Measure and send energy data
  sendEnergyDataToNodeRed();
  delay(5000); // Send data every 5 seconds
}

void connectWiFi()
{
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
}

void connectMQTT()
{
  Serial.println("Connecting to MQTT...");
  while (!client.connected()) {
    if (client.connect("ESP32_EnergyMeter")) {
      Serial.println("Connected to MQTT broker.");
    } else {
      Serial.print("Failed to connect. Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void sendEnergyDataToNodeRed()
{
  emon.calcVI(20, 2000); // Calculate all. No.of half wavelengths (crossings), time-out

  // Calculate energy consumed in kWh
  unsigned long currentMillis = millis();
  kWh += emon.apparentPower * (currentMillis - lastMillis) / 3600000000.0;
  lastMillis = currentMillis;

  // Print data to Serial Monitor
  Serial.printf("Vrms: %.2fV\tIrms: %.4fA\tPower: %.4fW\tkWh: %.5fkWh\n",
                emon.Vrms, emon.Irms, emon.apparentPower, kWh);

  // Save the latest kWh value to EEPROM
  saveEnergyDataToEEPROM();

  // Prepare JSON payload for Node-RED
  String payload = "{";
  payload += "\"Vrms\":" + String(emon.Vrms) + ",";
  payload += "\"Irms\":" + String(emon.Irms) + ",";
  payload += "\"Power\":" + String(emon.apparentPower) + ",";
  payload += "\"kWh\":" + String(kWh);
  payload += "}";

  // Publish data to MQTT topic
  if (client.publish(mqtt_topic, payload.c_str())) {
    Serial.println("Data sent to Node-RED.");
  } else {
    Serial.println("Failed to send data.");
  }
}

void readEnergyDataFromEEPROM()
{
  EEPROM.get(addrKWh, kWh);
  if (isnan(kWh)) {
    kWh = 0.0;
    saveEnergyDataToEEPROM();
  }
}

void saveEnergyDataToEEPROM()
{
  EEPROM.put(addrKWh, kWh);
  EEPROM.commit();
}
