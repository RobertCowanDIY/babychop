/* 

BabyChop is an embedded project intended to be an upgrade to the Harbor Freight Mini Chop Saw
https://www.harborfreight.com/2-in-mini-bench-top-cut-off-saw-62136.html

*/

#include <Servo.h>

//         Pins
const byte POWER_LED_PIN = 13,
           MOTOR_PWM_PIN = 11,
           ACTIVE_SW_PIN = 5,
            SPEED_SW_PIN = 4;

//        Config
const int MIN_POWER = 800,
          ARM_POWER = 1000,
          MAX_POWER = 2000,
           LO_POWER = 800,
           HI_POWER = 1100;

Servo ESC;

void setup() {
  pinMode(ACTIVE_SW_PIN, INPUT_PULLUP);
  pinMode(SPEED_SW_PIN,  INPUT_PULLUP);

  ESC.attach(11, MIN_POWER, MAX_POWER);
  ESC.writeMicroseconds(ARM_POWER);
}

void loop()
{
    if (shouldChop()) {
         if (digitalRead(SPEED_SW_PIN) == LOW) {
            lowChop();
        } else {
            highChop();
        }
    } else {
        noChop();
    }

    delay(50);
}

bool shouldChop() {
    // ACTIVE_SW_PIN is pulled high when floating so saw should be active
    // when signal is low
    return digitalRead(ACTIVE_SW_PIN) == LOW;
}

void highChop() {
    ESC.writeMicroseconds(HI_POWER);
    digitalWrite(POWER_LED_PIN, HIGH);
}

void lowChop() {
    ESC.writeMicroseconds(LO_POWER);
    digitalWrite(POWER_LED_PIN, HIGH);
}

void noChop() {
    ESC.writeMicroseconds(MIN_POWER);
    digitalWrite(POWER_LED_PIN, LOW);
}