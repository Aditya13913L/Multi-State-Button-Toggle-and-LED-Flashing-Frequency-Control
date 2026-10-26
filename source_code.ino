// ESP32 Problem 2: Multi-State Button Toggle & Non-Blocking LED Flashing
// Simple Arduino IDE Format

const int buttonPin = 14; // Push button pin
const int ledPin = 25;    // LED pin

// Button debouncing variables
int buttonState = HIGH;             
int lastButtonState = HIGH;         
unsigned long lastDebounceTime = 0; 
const unsigned long debounceDelay = 50; // 50ms debounce time

// State management
int currentMode = 0;      // 0: OFF, 1: Slow, 2: Medium, 3: Fast
const int totalModes = 4; // Total number of states

// Non-blocking LED timing variables (using millis)
unsigned long previousMillis = 0;
int ledState = LOW;

void setup() {
  Serial.begin(115200);
  
  // Configure pins
  pinMode(buttonPin, INPUT_PULLUP); // Internal pull-up (pressing = LOW)
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(ledPin, LOW); // Start with LED OFF
  
  Serial.println("System Ready!");
  Serial.println("Mode 0: OFF");
}

void loop() {
  unsigned long currentMillis = millis();

  // ==========================================
  // 1. BUTTON READING & DEBOUNCING
  // ==========================================
  int reading = digitalRead(buttonPin);

  // If state changed, reset the debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = currentMillis;
  }

  // If state has been stable longer than the debounce delay
  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    // If the button state has actually changed
    if (reading != buttonState) {
      buttonState = reading;
      
      // Only change mode on button PRESS (LOW because of INPUT_PULLUP)
      if (buttonState == LOW) {
        currentMode++; // Move to next mode
        if (currentMode >= totalModes) {
          currentMode = 0; // Loop back to 0
        }
        
        Serial.print("Button Pressed! Mode changed to: ");
        Serial.println(currentMode);
      }
    }
  }
  lastButtonState = reading;

  // ==========================================
  // 2. NON-BLOCKING LED FLASHING LOGIC
  // ==========================================
  unsigned long blinkInterval = 0;
  
  // Set interval based on current mode
  switch (currentMode) {
    case 0: blinkInterval = 0;    break; // OFF
    case 1: blinkInterval = 1000; break; // Slow Blink (1 second)
    case 2: blinkInterval = 300;  break; // Medium Blink (0.3 seconds)
    case 3: blinkInterval = 100;  break; // Fast Blink (0.1 seconds)
  }

  if (currentMode == 0) {
    // Mode 0: LED completely OFF
    ledState = LOW;
    digitalWrite(ledPin, ledState);
  } else {
    // Modes 1, 2, 3: Blink using millis() without blocking
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis; // Save the last time LED blinked
      
      // Toggle LED state
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      digitalWrite(ledPin, ledState);
    }
  }
}