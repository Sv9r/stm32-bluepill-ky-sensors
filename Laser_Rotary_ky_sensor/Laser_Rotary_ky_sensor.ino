#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin Definitions
#define ENCODER_CLK PA0
#define ENCODER_DT  PA1
#define ENCODER_SW  PA2
#define LASER_PIN   PA3
#define BUZZER_PIN  PA4  // Passive buzzer (PWM capable)

int position = 0;           // Rotary position counter
int lastStateCLK;           // Last read CLK state

void setup() {
  // Encoder and output pin setup
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  pinMode(LASER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // STM32 I2C pin mapping
  Wire.setSDA(PB7);
  Wire.setSCL(PB6);
  Wire.begin();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); // Hang if OLED init fails
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Initial CLK state
  lastStateCLK = digitalRead(ENCODER_CLK);

  updateDisplay(); // Show initial status
}

void loop() {
  // Debounced rotary encoder reading
  static unsigned long lastEncoderTime = 0;
  int currentStateCLK = digitalRead(ENCODER_CLK);

  if (currentStateCLK != lastStateCLK && (millis() - lastEncoderTime > 5)) {
    // Determine direction
    if (digitalRead(ENCODER_DT) != currentStateCLK) {
      position++;  // Clockwise
    } else {
      position--;  // Counter-clockwise
    }

    lastEncoderTime = millis();
    lastStateCLK = currentStateCLK;

    // Toggle laser and buzzer on even/odd position
    bool even = (position % 2 == 0);
    digitalWrite(LASER_PIN, even ? HIGH : LOW);

    if (even) {
      tone(BUZZER_PIN, 2000); // 2kHz tone
    } else {
      noTone(BUZZER_PIN);
    }

    updateDisplay(); // Update OLED info
  }

  // Reset with button press (debounced)
  static unsigned long lastButtonTime = 0;
  if (digitalRead(ENCODER_SW) == LOW && (millis() - lastButtonTime > 300)) {
    lastButtonTime = millis();
    position = 0;
    digitalWrite(LASER_PIN, LOW);
    noTone(BUZZER_PIN);
    updateDisplay(); // Refresh OLED after reset
  }
}

// OLED display function
void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Position: ");
  display.print(position);

  display.setCursor(0, 20);
  display.print("Laser: ");
  display.print(digitalRead(LASER_PIN) ? "ON" : "OFF");

  display.setCursor(0, 40);
  display.print("Buzzer: ");
  display.print(digitalRead(LASER_PIN) ? "ON" : "OFF"); // Mirrors laser state

  display.display(); // Render all changes
}
