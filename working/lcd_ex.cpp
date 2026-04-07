#include <Arduino.h>
#include <LiquidCrystal.h>

//
char array1[] = "Hypoxia Counter";
char array2[] = "0";
int tim = 500;

// initialize pins
LiquidCrystal lcd(4, 6, 10, 11, 12, 13);

//

void setup() {
  lcd.begin(16, 2);
}

//
void loop() {
  lcd.setCursor(15, 0);
  for (int positionCounter1 = 0; positionCounter1 < 15; positionCounter1++) {
    lcd.scrollDisplayLeft();
    lcd.print(array1[positionCounter1]);
    delay(tim);
  }
  lcd.clear();
  lcd.setCursor(15,1);
  for (int positionCounter2 = 0; positionCounter2 < 1; positionCounter2++) {
    lcd.scrollDisplayLeft();
    lcd.print(array2[positionCounter2]);
    delay(tim);
  }
  lcd.clear();
}