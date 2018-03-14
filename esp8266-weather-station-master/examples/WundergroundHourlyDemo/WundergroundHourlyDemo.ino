/**The MIT License (MIT)

Copyright (c) 2017 by Daniel Eichhorn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See more at https://blog.squix.org
*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <JsonListener.h>
#include "WundergroundHourly.h"

/**
 * Wunderground Settings
 */
const String  WUNDERGRROUND_API_KEY = "API_KEY";
const String  WUNDERGR_UND_STATE_OR_COUNTRY = "CH";
const String  WUNDERGR_UND_CITY = "ZURICH";
const String  WUNDERGRROUND_LANGUAGE = "EN";
const boolean IS_METRIC = true;
const boolean IS_24HOURS = false;

// initiate the WundergoundClient
WundergroundHourly wunderground(IS_METRIC, IS_24HOURS);


/**
 * WiFi Settings
 */
const char* ESP_HOST_NAME = "esp-" + ESP.getFlashChipId();
const char* WIFI_SSID     = "yourssid";
const char* WIFI_PASSWORD = "yourpassw0rd";

// initiate the WifiClient
WiFiClient wifiClient;



/**
 * Helping funtions
 */
void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println(WiFi.localIP());
  Serial.println();
}


/**
 * SETUP
 */
void setup() {
  Serial.begin(115200);
  delay(500);
  connectWifi();

  Serial.println();
  Serial.println("\n\nNext Loop-Step: " + String(millis()) + ":");

  WGHourly hourlies[24];
  wunderground.setMetric(true);
  wunderground.set24Hours(true);
  wunderground.updateHourly(hourlies, WUNDERGRROUND_API_KEY, WUNDERGRROUND_LANGUAGE, WUNDERGR_UND_STATE_OR_COUNTRY, WUNDERGR_UND_CITY);
  for (int i = 0; i < 24; i++) {
    Serial.println("------------------------------------");
    Serial.println("icon: " + hourlies[i].icon);
    Serial.println("title: " + hourlies[i].title);
    Serial.println("temp: " + hourlies[i].temp);
    Serial.println("hour: " + hourlies[i].hour);
    Serial.println("PoP: " + hourlies[i].PoP);
  }
  wunderground.setMetric(false);
  wunderground.set24Hours(false);
  wunderground.updateHourly(hourlies, WUNDERGRROUND_API_KEY, WUNDERGRROUND_LANGUAGE, WUNDERGR_UND_STATE_OR_COUNTRY, WUNDERGR_UND_CITY);
  for (int i = 0; i < 24; i++) {
    Serial.println("------------------------------------");
    Serial.println("icon: " + hourlies[i].icon);
    Serial.println("title: " + hourlies[i].title);
    Serial.println("temp: " + hourlies[i].temp);
    Serial.println("hour: " + hourlies[i].hour);
    Serial.println("PoP: " + hourlies[i].PoP);
  }


  Serial.println();
  Serial.println("---------------------------------------------------/\n");

}


/**
 * LOOP
 */
void loop() {

}
