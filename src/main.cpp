#include <HardwareSerial.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

#define RED 5
#define GREEN 6
#define BLUE 7

#define LED_CHANNELR 3
#define LED_CHANNELG 4
#define LED_CHANNELB 5

#define LED_FREQ 5000
#define LED_RESOLUTION 8

#define WIFI "BardzoTajneWiFi"
#define HASLO "TajneHASLO"

WebServer server(80);

int Rden = 60;
int Gden = 30;
int Bden = 80;

void handleNotFound() {
    server.send(404, "text/plain", "Not found");
}

void handleRoot() {
    File file = SPIFFS.open("/index.html", "r");
	if(!file) {
		server.send(500);
		return;
	}
    server.streamFile(file, "text/html");
    file.close();
}

void handleJS() {
    File file = SPIFFS.open("/script.js", "r");
    server.streamFile(file, "application/javascript");
    file.close();
}

void handleSliderR() {
  	if(server.hasArg("value")) {
		Rden = server.arg("value").toInt();
    	Serial.println(Rden);
  	}
  	server.send(200, "text/plain", "OK");
}

void handleSliderG() {
  	if(server.hasArg("value")) {
		Gden = server.arg("value").toInt();
    	Serial.println(Gden);
  	}
  	server.send(200, "text/plain", "OK");
}

void handleSliderB() {
  	if(server.hasArg("value")) {
		Bden = server.arg("value").toInt();
    	Serial.println(Bden);
  	}
  	server.send(200, "text/plain", "OK");
}

void setup() {
	Serial.begin(115200);

	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);

    ledcSetup(LED_CHANNELR, LED_FREQ, LED_RESOLUTION);
    ledcSetup(LED_CHANNELG, LED_FREQ, LED_RESOLUTION);
    ledcSetup(LED_CHANNELB, LED_FREQ, LED_RESOLUTION);

    ledcAttachPin(RED, LED_CHANNELR);
    ledcAttachPin(GREEN, LED_CHANNELG);
    ledcAttachPin(BLUE, LED_CHANNELB);

    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS mounting error");
        return;
    }

    WiFi.softAP(WIFI, HASLO);

	server.onNotFound(handleNotFound);

	server.on("/", handleRoot);
	server.on("/script.js", handleJS);
	server.on("/sliderR", handleSliderR);
	server.on("/sliderG", handleSliderG);
	server.on("/sliderB", handleSliderB);
    server.begin();
}

void loop() {
    server.handleClient();

	ledcWrite(LED_CHANNELR, Rden);
	ledcWrite(LED_CHANNELG, Gden);
	ledcWrite(LED_CHANNELB, Bden);
}
