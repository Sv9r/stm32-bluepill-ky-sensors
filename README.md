# stm32-bluepill-ky-sensors
   My project demonstrating how to interface the STM32 Blue Pill (STM32F103C8T6) with KY series sensors. Includes circuit diagrams and source code for connecting and     reading data from various KY modules. Useful for learning microcontroller sensor interfacing and building sensor projects.
_______________________________________________________________________________________________________________________________________________________________________
Project Structure
_______________________________________________________________________________________________________________________________________________________________________

  1) Laser_Rotary_ky_sensor.ino: Demonstrates using a rotary encoder to control a laser module and buzzer, with live feedback on an OLED display.

  2) RGB_Rotary_Encoder_1.ino: Shows how to use a rotary encoder to adjust the color channels of an RGB LED, with OLED display of the current color values.

  3) Tilt_Temp_ky_sensor.ino: Reads data from a tilt switch and analog temperature sensor, displaying the results on the OLED.

  4) Touch_LDR_ky_sensor.ino: Integrates a touch sensor and LDR (light-dependent resistor), activating a buzzer based on input, with status displayed on the OLED.
_______________________________________________________________________________________________________________________________________________________________________

Hardware Requirements
_______________________________________________________________________________________________________________________________________________________________________

To replicate these examples, you will need:

  > STM32F103C8T6 (“Blue Pill”) development board

  > 0.96" I2C OLED display (SSD1306, 128x64)

  > KY-040 Rotary Encoder

  > KY-008 Laser Module

  > KY-016 RGB LED

  > KY-036 Touch Sensor

  > KY-018 LDR Module

  > KY-013 Analog Temperature Sensor

  > KY-020 Tilt Switch

  > Passive buzzer

  > Breadboard and jumper wires

Ensure all modules share a common ground and are powered according to their specifications (typically 3.3V for STM32 peripherals).
_______________________________________________________________________________________________________________________________________________________________________

Pin Assignments
_______________________________________________________________________________________________________________________________________________________________________

Each example sketch contains detailed comments specifying which STM32 pins are connected to each sensor or actuator. Please refer to the top of each .ino file for exact wiring instructions.

For I2C OLED display, the standard connections are:

  > SDA connected to PB7

  > SCL connected to PB6

Other connections (rotary encoder, RGB LED, sensors, laser, buzzer) are clearly indicated in each respective sketch.

