#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// KY-013 Temp Sensor (Analog)
#define TEMP_PIN PA0

// KY-020 Tilt Sensor (Digital)
#define TILT_PIN PB0

void setup() {
  Serial.begin(115200);

  pinMode(TILT_PIN, INPUT_PULLUP);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  int rawTemp = analogRead(TEMP_PIN);
  float voltage = rawTemp * (3.3 / 4095.0); // STM32 ADC: 12-bit (0–4095)
  float temperature = voltage * 100.0; // LM393 approx: 10mV/°C

  bool tiltDetected = !digitalRead(TILT_PIN); // Active LOW

  // OLED Output
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print("Temp Sensor (KY-013):");
  display.setCursor(0, 25);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.print(" C");

  display.setCursor(0, 40);
  display.print("Tilt Sensor (KY-020):");
  display.setCursor(0, 55);
  display.print("Tilt: ");
  display.print(tiltDetected ? "DETECTED" : "Stable");

  display.display();

  delay(500);
}