#include <Arduino.h>
#include<LoRa.h>
#include <WiFi.h>
#include<SPI.h>

// Write API Key
String API_key = "UR7UOIWRZE6EE0Q1";

/// Network credentials
const char* ssid = "böööh";
const char* password = "pisssslik";

//Server Address
const char* adress = "api.thingspeak.com";

//Pins for Lora Module (Ra-01) 
#define IOO 21
#define MISO 5
#define SCK 2
#define MOSI 4
#define RESET 12 
#define NSS 13

String lora_data = "";

WiFiClient client; //Initialize WiFi as client

void wifiConnect() {
  // Connect WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(" . ");
  }

  // Print IP and status
  Serial.println("\nWiFi Connected :)");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setupLoRa(){
  //Set pins
  SPI.begin(SCK , MISO , MOSI , NSS);
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
  wifiConnect();
}

String prepareData(String API_key, String data) {
    String str_data = "api_key=" + API_key;
    str_data += "&field1=" + data;
    str_data += "&field2=bumbum";  
    return str_data;
}

void sendDataThingSpeak(WiFiClient client, String server, String API_key, String str_data) {
    if (client.connect(server.c_str(), 80)) {
        Serial.println("Connected to ThingSpeak server!");

        client.print("POST /update HTTP/1.1\r\n");
        client.print("Host: " + server + "\r\n");
        client.print("Connection: close\r\n");
        client.print("Content-Type: application/x-www-form-urlencoded\r\n");
        client.print("Content-Length: " + String(str_data.length()) + "\r\n\r\n");
        client.print(str_data);

        Serial.println("Data sent to ThingSpeak!");

        delay(1000); // Wait response
        while (client.available()) {
            Serial.write(client.read());  // Print response
        }
        client.stop();
    } else {
        Serial.println("Connection to ThingSpeak failed.");
    }
}

void loop() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        lora_data = "";
        while (LoRa.available()) {
            lora_data += (char)LoRa.read();
        }
        Serial.println("Received: " + lora_data);

        // print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());

        String dataToSend = prepareData(API_key, lora_data);
        sendDataThingSpeak(client, adress, API_key, dataToSend);
    }
}

