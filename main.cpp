/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/

#include "main.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>

#define NUM_LEDS 2
#define DATA_PIN 13
#define SEALEVELPRESSURE_HPA (1013.25)

void SensorValues();

Adafruit_BME280 bmp; 

const char *ssid = "ESP32-mich";
const char *password = "123456789";

WiFiServer server(80);

String header;

// Variabili per la gestione dei tempi
unsigned long currentTime = 0;
unsigned long previousTime = 0;
const long sensorInterval = 1000;

Misure misure;

void setup() {
  Serial.begin(115200);
  
  // Inizializzazione del sensore BME280
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    // Puoi scegliere di bloccare l'esecuzione oppure procedere comunque
    // while (1);
  }

  // Configurazione dell'Access Point Wi‑Fi
  Serial.print("Setting AP (Access Point)...");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  misure.tempc = 0.0;
  misure.tempf = 0.0;
  misure.press = 0.0;
  misure.altit = 0.0;

  initIOT();

  server.begin();
}

void loop() {
  currentTime = millis();
  
  if (currentTime - previousTime >= sensorInterval) {
    previousTime = currentTime;
    SensorValues();
  }

  webServer.handleClient();
  
  delay(100);
}

void SensorValues() {
  misure.tempc = bmp.readTemperature();
  misure.tempf = 1.8 * misure.tempc + 32;
  misure.press = bmp.readPressure() / 100.0F;
  misure.altit = bmp.readAltitude(SEALEVELPRESSURE_HPA);
}
