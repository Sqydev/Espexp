#include "HardwareSerial.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

#define LED 2
#define LED_CHANNEL 0
#define LED_FREQ 5000
#define LED_RESOLUTION 8

#define WIFI "BardzoTajneWiFi"
#define HASLO "TajneHASLO"

WebServer server(80);

int sliderValue = 0;

void handleRoot() {
    File file = SPIFFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
}

void handleSlider() {
  if (server.hasArg("value")) {
    sliderValue = server.arg("value").toInt();
    Serial.println(sliderValue);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
	pinMode(LED, OUTPUT);
    ledcSetup(LED_CHANNEL, LED_FREQ, LED_RESOLUTION);
    ledcAttachPin(LED, LED_CHANNEL);

    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS mounting error");
        return;
    }

    WiFi.softAP(WIFI, HASLO);

    server.on("/", handleRoot);
	server.on("/slider", handleSlider);
    server.begin();
}

void loop() {
    server.handleClient();

	ledcWrite(LED_CHANNEL, sliderValue);
}
