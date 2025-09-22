/* 

BabyChop is an embedded project intended to be an upgrade to the Harbor Freight Mini Chop Saw
https://www.harborfreight.com/2-in-mini-bench-top-cut-off-saw-62136.html

*/

#include <Servo.h>

//         Pins
const byte POWER_LED_PIN = 13,
           MOTOR_PWM_PIN = 11,
           ACTIVE_SW_PIN =  5,
            SPEED_SW_PIN =  4;

//        Config
const int MIN_POWER =  800, // Match MIN_POWER and MAX_POWER to your ESC config
          MAX_POWER = 2000,
           LO_POWER = 1000,
           HI_POWER = 1200;

Servo ESC;

void setup() {
  pinMode(ACTIVE_SW_PIN, INPUT_PULLUP);
  pinMode(SPEED_SW_PIN,  INPUT_PULLUP);

  ESC.attach(MOTOR_PWM_PIN, MIN_POWER, MAX_POWER);
  ESC.writeMicroseconds(MIN_POWER);
}

void loop()
{
    // ACTIVE_SW_PIN is pulled high when floating
    // so the saw should be active when the signal 
    // is low.
    if (digitalRead(ACTIVE_SW_PIN) == LOW) {

        // SPEED_SW_PIN determines how fast we chop
        // LOW signal means LO_POWER

        if (digitalRead(SPEED_SW_PIN) == LOW) {
            ESC.writeMicroseconds(LO_POWER);
            digitalWrite(POWER_LED_PIN, HIGH);
        } else {
            ESC.writeMicroseconds(HI_POWER);
            digitalWrite(POWER_LED_PIN, HIGH);
        }

    } else {
        // Disable/turn off the saw
        ESC.writeMicroseconds(MIN_POWER);
        digitalWrite(POWER_LED_PIN, LOW);
    }

    delay(50);
}