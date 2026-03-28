#include <HardwareSerial.h>
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

void handleSlider() {
  	if(server.hasArg("value")) {
		sliderValue = server.arg("value").toInt();
    	Serial.println(sliderValue);
  	}
  	server.send(200, "text/plain", "OK");
}

void setup() {
	Serial.begin(115200);

	pinMode(LED, OUTPUT);
    ledcSetup(LED_CHANNEL, LED_FREQ, LED_RESOLUTION);
    ledcAttachPin(LED, LED_CHANNEL);

    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS mounting error");
        return;
    }

    WiFi.softAP(WIFI, HASLO);

	server.on("/slider", handleSlider);
	// It's like if someone asks for anything search it in root and if exists give it to them
	server.serveStatic("/", SPIFFS, "/");
    server.begin();
}

void loop() {
    server.handleClient();

	ledcWrite(LED_CHANNEL, sliderValue);
}
