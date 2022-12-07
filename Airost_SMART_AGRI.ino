#define BLYNK_TEMPLATE_ID "TMPLVusWwc0f"
#define BLYNK_DEVICE_NAME "Smart AGRI"
#define BLYNK_AUTH_TOKEN "qFd7eGMfgSkrARr_w6wVIIYc6_UqqOgp"

char ssid[] = "Tungzh";
char pass[] = "0125056881tzh";


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>
#include <Simpletimer.h>

//Temperature sensor
#define Type DHT11
#define sensePin D4
DHT HT(sensePin,Type);
#define sensor A0

char auth[] = BLYNK_AUTH_TOKEN;

SimpleTimer timer; //BlynkTimer

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors


//BlynkTimer timer;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
HT.begin();
timer.setInterval(100L, sendSensor);//temperature
timer.setInterval(100L, soilMoistureSensor);
Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
  
}

void sendSensor()
{
  float h = HT.readHumidity();
  float t = HT.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);
}

void soilMoistureSensor() 
{
  int value = analogRead(sensor);
  Serial.print(value);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V2, value);
  Serial.println(value);
  delay(500);


}
