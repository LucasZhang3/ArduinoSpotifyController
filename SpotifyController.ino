#include <LiquidCrystal.h>

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int joyX = A0;
const int joyBtn = 2;

String fullLine1 = "";
String fullLine2 = "";
int scroll1 = 0;
int scroll2 = 0;
int scrollTarget = 0;

bool lastButtonState = HIGH;

unsigned long lastScrollTime = 0;
const unsigned long scrollInterval = 150;

void setup() {
  pinMode(joyBtn, INPUT_PULLUP);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Spotify Ready!");
}

void loop() {
  bool currentButtonState = digitalRead(joyBtn);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    scrollTarget = 1 - scrollTarget;
    delay(200);
  }
  lastButtonState = currentButtonState;

  int x = analogRead(joyX);

  unsigned long now = millis();

  bool left = x < 400;
  bool right = x > 600;

  if ((left || right) && now - lastScrollTime > scrollInterval) {
    lastScrollTime = now;

    if (left) {
      if (scrollTarget == 0 && scroll1 > 0) scroll1--;
      else if (scrollTarget == 1 && scroll2 > 0) scroll2--;
    } else if (right) {
      if (scrollTarget == 0 && scroll1 < fullLine1.length() - 16) scroll1++;
      else if (scrollTarget == 1 && scroll2 < fullLine2.length() - 16) scroll2++;
    }
    displayScroll();
  }

  if (!left && !right && now - lastScrollTime > 1000) {
    lastScrollTime = now;
    displayScroll();
  }

  if (Serial.available()) {
    String fullData = Serial.readStringUntil('\n');
    fullData.replace("\r", "");
    fullData.replace("\n", "");

    if (fullData.length() >= 96) {
      fullLine1 = fullData.substring(0, 48);
      fullLine2 = fullData.substring(48, 96);
      scroll1 = 0;
      scroll2 = 0;
      displayScroll();
    }
  }
}

void displayScroll() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(fullLine1.substring(scroll1, min(scroll1 + 16, fullLine1.length())));

  lcd.setCursor(0, 1);
  lcd.print(fullLine2.substring(scroll2, min(scroll2 + 16, fullLine2.length())));

  lcd.setCursor(15, scrollTarget);
  lcd.print(">");
}
