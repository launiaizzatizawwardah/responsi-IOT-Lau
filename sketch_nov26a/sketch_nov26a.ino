#include <ESP8266WiFi.h>
#include "DHT.h"

// -----------------------------
// WiFi Configuration
// -----------------------------
const char* ssid = "GEDUNG B - WPA";
const char* password = "123123123";

// -----------------------------
// DHT22 Configuration
// -----------------------------
#define DHTPIN D5        // Pin Data DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// -----------------------------
// Sensor Cahaya (LDR DO)
// -----------------------------
#define LIGHT_PIN D7     // DO modul di D7

void setup() {
  Serial.begin(115200);

  // Start sensor DHT
  dht.begin();
  delay(2000);  // beri waktu sensor stabil

  // Setup pin LDR DO
  pinMode(LIGHT_PIN, INPUT);

  // -----------------------------
  // Connect to WiFi
  // -----------------------------
  Serial.print("Menghubungkan ke WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tries++;
    if (tries > 40) {
      Serial.println("\nGagal tersambung WiFi!");
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Tersambung!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }

  Serial.println("Sistem IoT Siap...");
}

void loop() {
  // -----------------------------
  // Baca data DHT22
  // -----------------------------
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  // Cek apakah sensor berhasil dibaca
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Gagal membaca sensor DHT22!");
  } else {
    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print("°C | Kelembapan: ");
    Serial.print(kelembapan);
    Serial.println("%");
  }

  // -----------------------------
  // Baca sensor cahaya (DO)
  // -----------------------------
  int cahaya = digitalRead(LIGHT_PIN);
  String kondisiCahaya = (cahaya == HIGH) ? "Gelap" : "Terang";

  Serial.print("Cahaya: ");
  Serial.println(kondisiCahaya);

  // -----------------------------
  // Delay antar pembacaan
  // -----------------------------
  Serial.println("------------------------------------");
  delay(2000);
}
