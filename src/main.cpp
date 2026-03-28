#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

#define LED 8

#define WIFI "BardzoTajneWiFi"
#define HASLO "TajneHASLO"

WebServer server(80);

void handleRoot() {
    File file = SPIFFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
}

void setup() {
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);

    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS mounting error");
        return;
    }

    WiFi.softAP(WIFI, HASLO);

    server.on("/", handleRoot);
    server.on("/on",  []() { digitalWrite(LED, LOW);  server.sendHeader("Location", "/"); server.send(303); });
    server.on("/off", []() { digitalWrite(LED, HIGH); server.sendHeader("Location", "/"); server.send(303); });
    server.begin();
}

void loop() {
    server.handleClient();
}
