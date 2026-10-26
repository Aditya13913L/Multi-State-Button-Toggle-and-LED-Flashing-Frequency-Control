# Multi-State-Button-Toggle-and-LED-Flashing-Frequency-Control
Multi-State Button Toggle and LED Flashing Frequency Control based on IOT &amp; Robotics @UNLOX

## Overview
This project implements a multi-state LED flashing system on an ESP32 using the Arduino IDE. A single push button is used to cycle through four different operating modes: **OFF, Slow Blink, Medium Blink, and Fast Blink**. 

The code uses **non-blocking timing** (`millis()`) to ensure that the LED flashes concurrently without stopping the microcontroller from instantly reading new button presses.

## Components Required
* 1x ESP32 Development Board
* 1x Tactile Push Button
* 1x LED (Green or any color)
* 1x 220-ohm Resistor
* Breadboard and Jumper Wires

## Evidence 
The circuit digram screenshot and simulation video are attached in the project file.

## Pin Configuration (Wiring)

| Component | ESP32 Pin | Type | Notes |
| :--- | :--- | :--- | :--- |
| **Mode Button** | `GPIO 14` | Input | Connect other pin to GND (Uses `INPUT_PULLUP`) |
| **Status LED** | `GPIO 25` | Output | Connect through 220Ω resistor to GND |

## How to Run in Wokwi Simulator
1. Go to [Wokwi ESP32 Simulator] - https://wokwi.com/projects/478967539892003841
2. Copy the contents of the provided `problem2.ino` into the code editor (`sketch.ino`).
3. Open the `diagram.json` tab and paste the provided JSON configuration for Problem 2.
4. Click the **Play** button to start the simulation.
5. Click the button on the screen to cycle through the different flashing speeds.

## Project Logic Highlights
* **Software Debouncing:** Mechanical buttons "bounce", causing one press to register as many. A `50ms` software timer ignores these false signals.
* **Non-Blocking Timer (`millis()`):** Instead of using `delay()` which pauses the entire system, `millis()` is used to track how much time has passed. This allows the ESP32 to blink the LED and listen for button presses at the exact same time.
* **State Machine:** A variable `currentMode` keeps track of the system state (0 to 3) and loops back to 0 when the maximum is reached.
