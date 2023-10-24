import time
from Adafruit_BME280 import BME280
import smtplib
from email.mime.text import MIMEText
import json
from twilio.rest import Client

# BME280 Sensor-Initialisierung
bme = BME280()

# Wi-Fi-Konfiguration
WIFI_SSID = 'Ihr_WiFi_SSID'
WIFI_PASSWORD = 'Ihr_WiFi_Passwort'

# SMTP-Konfiguration für E-Mail
SMTP_SERVER = 'smtp.example.com'
SMTP_PORT = 587
SMTP_USERNAME = 'Ihre_Email@example.com'
SMTP_PASSWORD = 'Ihr_Email_Passwort'
SMTP_TO = 'ziel@email.com'

# Twilio-Konfiguration für SMS
TWILIO_SID = 'Ihr_Twilio_SID'
TWILIO_AUTH_TOKEN = 'Ihr_Twilio_Authentifizierungstoken'
TWILIO_PHONE_NUMBER = 'Ihre_Twilio_Rufnummer'
DEST_PHONE_NUMBER = 'Ziel_Rufnummer'

def send_email(subject, message):
    msg = MIMEText(message)
    msg['From'] = SMTP_USERNAME
    msg['To'] = SMTP_TO
    msg['Subject'] = subject

    server = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)
    server.starttls()
    server.login(SMTP_USERNAME, SMTP_PASSWORD)
    server.sendmail(SMTP_USERNAME, SMTP_TO, msg.as_string())
    server.quit()

def send_sms(message):
    client = Client(TWILIO_SID, TWILIO_AUTH_TOKEN)
    client.messages.create(
        to=DEST_PHONE_NUMBER,
        from_=TWILIO_PHONE_NUMBER,
        body=message
    )

while True:
    temperature = bme.read_temperature()
    humidity = bme.read_humidity()
    pressure = bme.read_pressure() / 100.0

    if temperature > 30.0 or humidity > 70.0 or pressure < 900.0:
        alert_message = "Umweltbedingungen außerhalb des Normalbereichs - Temperatur, Luftfeuchtigkeit oder Druck."
        send_email("Alarm - Umweltbedingungen", alert_message)
        send_sms(alert_message)

    time.sleep(60)  # Überprüfen Sie alle 60 Sekunden
