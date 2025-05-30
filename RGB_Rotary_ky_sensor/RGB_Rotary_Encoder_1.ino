#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define ENCODER_CLK PA0
#define ENCODER_DT PA1
#define ENCODER_SW PA2

#define RED_PIN PB0
#define GREEN_PIN PB1
#define BLUE_PIN PA7

int colorValues[3] = {0, 0, 0};
int currentColor = 0;
int lastStateCLK;

void setup() {
    pinMode(ENCODER_CLK, INPUT);
    pinMode(ENCODER_DT, INPUT);
    pinMode(ENCODER_SW, INPUT_PULLUP);
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    
    Wire.setSDA(PB7);
    Wire.setSCL(PB6);
    Wire.begin();
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        for (;;);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    
    lastStateCLK = digitalRead(ENCODER_CLK);
    updateDisplay();
}

void loop() {
    int currentStateCLK = digitalRead(ENCODER_CLK);
    if (currentStateCLK != lastStateCLK) {
        if (digitalRead(ENCODER_DT) != currentStateCLK) {
            colorValues[currentColor] = min(255, colorValues[currentColor] + 5);
        } else {
            colorValues[currentColor] = max(0, colorValues[currentColor] - 5);
        }
        updateDisplay();
        updateLED();
    }
    lastStateCLK = currentStateCLK;
    
    if (digitalRead(ENCODER_SW) == LOW) {
        delay(200);
        currentColor = (currentColor + 1) % 3;
        updateDisplay();
    }
}

void updateDisplay() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("R:"); display.print(colorValues[0]);
    display.print(" G:"); display.print(colorValues[1]);
    display.print(" B:"); display.print(colorValues[2]);
    
    display.setCursor(0, 20);
    display.print("Editing: ");
    if (currentColor == 0) display.print("Red");
    else if (currentColor == 1) display.print("Green");
    else display.print("Blue");
    
    display.display();
}

void updateLED() {
    analogWrite(RED_PIN, colorValues[0]);
    analogWrite(GREEN_PIN, colorValues[1]);
    analogWrite(BLUE_PIN, colorValues[2]);
}
