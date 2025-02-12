#include <Arduino.h>
#include<LoRa.h>
#include<Wire.h>


//Pins for Lora Module (Ra-01) 
#define IOO 21
#define MISO 5
#define SCK 2
#define MOSI 4
#define RESET 12 
#define NSS 13

//Pins for sensor
#define TriggerPin 17
#define EchoPin 16

long duration , distance;

String lora_message = "";

void setupLoRa(){
  //Set pins
  LoRa.setPins(NSS , RESET , IOO);
  
  Serial.println("Setting Up LoRa Module");
  // 433E6 for Asia 
  // 866E6 for Europe 
  // 915E6 for North America
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa Failed");
    delay(500);
  }

  Serial.println("LoRa Started");
  //To isolate from other LoRa Senders
  LoRa.setSyncWord(0xF0);
}

void setup() {
  Serial.begin(115200);
  setupLoRa();

  pinMode(TriggerPin , OUTPUT);
  pinMode(EchoPin , INPUT);
}

void loop() {
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  
  duration = pulseIn(EchoPin, HIGH);
  distance = duration / 58.2;
  String disp = String(distance);

  Serial.print("Distance: ");
  Serial.print(disp);
  Serial.println(" cm");

  lora_message = disp;

  // send the LoRa packet
  LoRa.beginPacket();
  LoRa.print(lora_message);
  LoRa.endPacket();
  delay(1000);

}

