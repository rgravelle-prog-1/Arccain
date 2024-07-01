#include <ESP8266WiFi.h> // For ESP8266
// #include <WiFi.h>      // For ESP32

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

const int soilMoisturePin = A0; // Change to appropriate pin for ESP32
const int ledPin = D4; // Use built-in LED (ESP8266) or GPIO2
// const int ledPin = 2; // Uncomment this line for ESP32 and comment the above line

// Calibration values
const int dryValue = 645; // 0% moisture
const int wetValue = 285; // 100% moisture

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize the soil moisture sensor and LED pin
  pinMode(soilMoisturePin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Turn off the LED initially
}

void loop() {
  int rawValue = analogRead(soilMoisturePin);
  int soilMoisturePercent = map(rawValue, dryValue, wetValue, 0, 100);

  // Ensure percentage is within bounds
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);

  Serial.print("Raw Sensor Value: ");
  Serial.print(rawValue);
  Serial.print(" -> Soil Moisture: ");
  Serial.print(soilMoisturePercent);
  Serial.println("%");

  // Control LED based on soil moisture percentage
  if (soilMoisturePercent < 15) {
    // Blink the LED if soil moisture is below 15%
    digitalWrite(ledPin, HIGH); // Turn on the LED
    delay(500); // Wait for 500 milliseconds
    digitalWrite(ledPin, LOW); // Turn off the LED
    delay(500); // Wait for 500 milliseconds
  } else if (soilMoisturePercent > 85) {
    // Turn off the LED if soil moisture is above 85%
    digitalWrite(ledPin, LOW);
  } else {
    // Turn on the LED solid if soil moisture is between 15% and 85%
    digitalWrite(ledPin, HIGH);
  }

  delay(2000); // Read every 2 seconds
}
