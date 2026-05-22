// Updated Arduino Uno code for DRV8825 stepper motor
// DIR on pin 2, STEP on pin 3
// Button on pin 4 (internal pull-up) — press to trigger oxygen_cycle()
// oxygen_cycle() = forward STEPNO steps → delay DELAY seconds → backward STEPNO steps
#include <Arduino.h>

#define DIR_PIN     3
#define STEP_PIN    2
#define BUTTON_PIN  4

// ================== CONFIGURE THESE ==================
const uint16_t STEPNO = 560;      // Number of steps to move in each direction (200 = 1 full revolution on most 1.8° motors)
const uint16_t DELAY_NORM  = 65;        // Delay in seconds at Normoxia
const uint16_t DELAY_HYPOXIA = 90;      // Delay in seconds at Hypoxia
const uint16_t PULSE_DELAY   = 1200; // Target (fastest) delay in microseconds per step at full speed
                                // (smaller = faster, larger = more torque at top speed)
const uint16_t ACCEL_STEPS   = 60;   // Number of steps used for acceleration AND deceleration ramp
                                // (higher = gentler/smoother ramp, but takes longer to reach speed)
                                // Good starting value for most NEMA17/23 motors: 30-60
const uint16_t START_DELAY   = 3000;// Starting (slowest) delay in microseconds
                                // Higher value = slower start (more torque at beginning)
const uint8_t CYCLES_BEFORE_SLEEP = 5; // Number of complete oxygen cycles before putting the motor to sleep (optional power-saving feature)
// =====================================================

bool buttonPressed = false;
unsigned long lastButtonChangeMs = 0;
int lastButtonReading = HIGH;
int stableButtonState = HIGH;

// moveSteps with linear acceleration ramp-up + deceleration ramp-down
void moveSteps(bool forward, int steps) {
  digitalWrite(DIR_PIN, forward ? HIGH : LOW);  // HIGH = forward, LOW = backward
  
  int accelSteps = ACCEL_STEPS;
  if (accelSteps * 2 > steps) {
    accelSteps = steps / 2;  // Handle very short moves gracefully
  }
  
  long minDelay = PULSE_DELAY;
  
  // === ACCELERATION PHASE (ramp up to full speed) ===
  for (int i = 0; i < accelSteps; i++) {
    long currentDelay = (long)START_DELAY - ((long)START_DELAY - minDelay) * i / accelSteps;
    
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(currentDelay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(currentDelay);
  }
  
  // === CONSTANT SPEED PHASE ===
  int constSteps = steps - 2 * accelSteps;
  for (int i = 0; i < constSteps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(minDelay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(minDelay);
  }
  
  // === DECELERATION PHASE (ramp down to stop smoothly) ===
  for (int i = 0; i < accelSteps; i++) {
    long currentDelay = minDelay + ((long)START_DELAY - minDelay) * i / accelSteps;
    
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(currentDelay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(currentDelay);
  }
}

void oxygen_cycle() {
  // Move forward STEPNO steps
  moveSteps(true, STEPNO);
  
  // Wait Normoxia seconds
  delay((unsigned long)DELAY_NORM * 1000UL);

  // Wait Hypoxia seconds
  delay((unsigned long)DELAY_HYPOXIA * 1000UL);

  // Move backward STEPNO steps
  moveSteps(false, STEPNO);
}

void setup() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Button with internal pull-up (press = LOW)
  
  digitalWrite(STEP_PIN, LOW);  // Start STEP pin low
  Serial.begin(9600);
  Serial.println("Stepper motor control initialized. Press the button to start the oxygen cycle.");
}

void loop() {
  // Debounced edge detection: trigger once on press transition (HIGH -> LOW).
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonReading) {
    lastButtonChangeMs = millis();
    lastButtonReading = reading;
  }

  if ((millis() - lastButtonChangeMs) > 30 && reading != stableButtonState) {
    stableButtonState = reading;
    if (stableButtonState == LOW) {
      buttonPressed = true;
      Serial.println("Button press detected. Starting oxygen cycles.");
    }
  }

  if (buttonPressed) {
    for (int i = 0; i < CYCLES_BEFORE_SLEEP; i++) {
      oxygen_cycle();
    }
    buttonPressed = false;
  }
}