#define BLYNK_PRINT Serial
#include <SPI.h>
#include <SimpleTimer.h>
#include <DHT.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DHTPIN D4  // GPIO D4

#define DHTTYPE DHT11 // dht11

DHT dht (DHTPIN, DHTTYPE);
SimpleTimer timer;

char auth[] = "dEfZPRAwJA0uNLFE5s6fxnNQfJlOPjJX"; //get token from blynk app android

char ssid[] = "biarinajah"; // ssid wifi
char pass[] = "pondame126"; //password wifi

void sendSensor () {
  float h = (dht.readHumidity())-11;
  float t = (dht.readTemperature())-0.4; // or dht.readTemperature(true) for Fahrenheit
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // you can send any value at any time
  // please don't send more that 10 values per second
  Blynk.virtualWrite(V0, t); // V6 for temperature
  Blynk.virtualWrite(V1, h); // V5 for humidity
  
}

void setup() {
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();
  timer.setInterval(1000L, sendSensor);
  Serial.println("\n");
}

void loop() {
  Blynk.run();
  timer.run(); // initiates SimpleTimer
  float h = (dht.readHumidity())-11;
  float t = (dht.readTemperature())-0.4; // or dht.readTemperature(true) for Fahrenheit
  
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.print(" °C ");
  Serial.print("\t");
  Serial.print("RH: ");
  Serial.print(h);
  Serial.println("%");
  delay(1000);
}
