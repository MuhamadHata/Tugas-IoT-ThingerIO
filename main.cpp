#include <ThingerESP32.h> // Ganti ke ThingerESP8266 jika menggunakan NodeMCU

// Konfigurasi Akun Thinger.io
#define USERNAME "Hatzwle"
#define DEVICE_ID "esp32_hcsr04"
#define DEVICE_CREDENTIAL "cekultrasonik"

// Konfigurasi WiFi
#define SSID "BIBD"
#define SSID_PASSWORD "modalbro"

// Pin Sensor HC-SR04
const int trigPin = 5;
const int echoPin = 18;

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // Resource Thinger.io untuk mengirim data jarak
  thing["ultrasonic"] >> [](pson& out){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.034 / 2; // Rumus konversi ke cm
    
    out = distance; // Mengirim nilai ke platform
  };
}

void loop() {
  thing.handle();
}