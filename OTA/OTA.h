#ifndef OTA_H_
#define OTA_H_

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

const char* ssid = "WASP_2.4";
const char* password = "Wasp1234";

AsyncWebServer server(80);


class OTA{
    public:

    void begin()
    {
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        Serial.println("");

        // Wait for connection
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());

        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
            request->send(200, "text/plain", "Hi! This is a sample response.");
        });

        AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
        server.begin();
        Serial.println("HTTP server started");
    }
};

#endif