#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
#include <GSM.h>

#define BME_SDA 4
#define BME_SCL 5
#define BME_ADDRESS 0x76
#define GSM_RX 2
#define GSM_TX 3

const char* ssid = "IhrWiFiSSID";
const char* password = "IhrWiFiPasswort";
const char* serverURL = "https://example.com/api";
const char* gsmAPN = "IhrGSM-APN";
const char* gsmUser = "IhrGSM-Benutzername";
const char* gsmPass = "IhrGSM-Passwort";
const char* phoneNumber = "+1234567890";

Adafruit_BME280 bme(BME_ADDRESS);
GSM gsmAccess;

void setup() {
  Serial.begin(9600);
  Wire.begin(BME_SDA, BME_SCL);
  bme.begin(0x76);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Verbindung zum Wi-Fi-Netzwerk...");
  }

  gsmAccess.begin(gsmAPN, gsmUser, gsmPass);
  gsmAccess.wakeUp();
}

void loop() {
  delay(60000); // Messwerte alle 60 Sekunden senden

  if (WiFi.status() == WL_CONNECTED) {
    float temperature = bme.readTemperature();
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure() / 100.0F;

    if (temperature > 30.0 || humidity > 70.0 || pressure < 900.0) {
      sendAlertSMS("Umweltbedingungen außerhalb des Normalbereichs - Temperatur, Luftfeuchtigkeit oder Druck.");
      sendAlertEmail("Umweltbedingungen außerhalb des Normalbereichs - Temperatur, Luftfeuchtigkeit oder Druck.");
    }
  }
}

void sendAlertSMS(String message) {
  GSM_SMS sms;
  if (sms.beginSMS(phoneNumber)) {
    sms.print(message);
    sms.endSMS();
  }
}

void sendAlertEmail(String message) {
  WiFiClientSecure client;
  if (client.connect(serverURL, 443)) {
    String payload = "message=" + message;
    HTTPClient http;
    http.begin(client, serverURL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.POST(payload);
    http.end();
  }
}
