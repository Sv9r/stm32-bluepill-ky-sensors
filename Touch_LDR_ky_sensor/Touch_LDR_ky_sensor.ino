#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128   // OLED display width, in pixels
#define SCREEN_HEIGHT 64   // OLED display height, in pixels

// Initialize OLED display with I2C address 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Sensor and buzzer pin definitions
#define TOUCH_SENSOR_PIN PA1 // KY-036 Digital Output (DO)
#define LDR_SENSOR_PIN PA2    // KY-018 Analog Output (AO)
#define BUZZER_PIN PA3    // Buzzer pin

void setup() {
  pinMode(TOUCH_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.begin(115200);
  
  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 initialization failed!");
    for (;;);  // Halt execution
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  int touchState = digitalRead(TOUCH_SENSOR_PIN);  // Read touch sensor
  int lightValue = analogRead(LDR_SENSOR_PIN);    // Read light sensor

  // Print raw sensor data
  Serial.print("LDR Value: ");
  Serial.println(lightValue); // Debugging LDR value

  // Auto-adjust threshold if needed
  int LDR_THRESHOLD = 200;  // Adjust based on Serial Monitor values

  // Update OLED Display
  display.clearDisplay();
  display.setCursor(10, 10);
  display.print("Light: ");
  display.print(lightValue > LDR_THRESHOLD ? "YES" : "NO");

  display.setCursor(10, 30);
  display.print("Touch: ");
  display.print(touchState == HIGH ? "YES" : "NO");

  display.display();

  // Activate buzzer when touch is detected
  if (touchState == HIGH || lightValue > LDR_THRESHOLD){
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);  // Delay for stability
}
