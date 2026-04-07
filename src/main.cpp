#include <Arduino.h>

#define in1 2
#define in2 3
#define buttonPin 4
#define switch_pin 5

int rotDirection = true; // true = right, false = left

void setup() {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(switch_pin, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);

    // Set initial direction
    rotDirection = 0;
}


void motorRight() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
}

void motorLeft() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
}

void motorStop() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
}



int checkSwitch(){
    if (digitalRead(switch_pin) == LOW) {
        return 1;
    } else {
        return 0;
    }

}

void moveDirection(bool dir) {
    rotDirection = dir;
    if (rotDirection == true) {
        motorRight();
    } else {
        motorLeft();
    }
    while (checkSwitch() == 0) {
        // Keep moving
    }
    motorStop();
}   

int checkButton(){
    if (digitalRead(buttonPin) == LOW) {
        return 1;
    } else {
        return 0;
    }
}

void blink_light(int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
}

void loop() {
    if (checkButton() == 1) {
        moveDirection(rotDirection);
        rotDirection = !rotDirection;
        delay(100); // Debounce delay
    }
    else {
        blink_light(1);  
    }
    delay(50);
}