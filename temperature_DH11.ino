/*
//////////////////YUKTAHA 2023////////////////
pin configuration
pin 1-Signal pin-Arduino 7
pin 2-Vcc pin-Arduino Vcc
pin 3-Gnd pin-Arduino Gnd 
*/
#include <dht.h>

dht DHT;

#define DHT11_PIN 7

void setup(){
  Serial.begin(9600);
}

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);
}