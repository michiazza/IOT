#ifndef main_h
#define main_h

#include "Arduino.h"

// Load Wi-Fi library
#include <WiFi.h>

#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include <time.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

#include "pagine.h"

class Misure
{
public:
    float tempc;
    float tempf;
    float press;
    float altit;
};

extern Misure misure;

#endif // #ifndef pagine_h
