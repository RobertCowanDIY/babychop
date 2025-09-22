/* 
    MiniMonster is an embedded project intended to be an upgrade to the Harbor Freight Mini Chop Saw
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

// Speed change per millisecond
// Set to current range across 1.5 seconds
const float RAMP_CONSTANT = float(HI_POWER - MIN_POWER) / 1500;

unsigned long LAST_TIME = millis(); // Time will rollover every ~50 days.
// If a rampup happens to happen across the rollover, ??? happens

int CUR_POWER = 0;

Servo ESC;

void setup() {
  Serial.begin(115200);
  pinMode(ACTIVE_SW_PIN, INPUT_PULLUP);
  pinMode(SPEED_SW_PIN,  INPUT_PULLUP);

  ESC.attach(MOTOR_PWM_PIN, MIN_POWER, MAX_POWER);
  ESC.writeMicroseconds(MIN_POWER);
}

void loop()
{
    // == Read Input
    int DESIRED_SPEED = 0;

    // ACTIVE_SW_PIN is pulled high when floating
    // so the saw should be active when the signal 
    // is low.
    if (digitalRead(ACTIVE_SW_PIN) == LOW) {

        // SPEED_SW_PIN determines how fast we chop
        // LOW signal means LO_POWER
        if (digitalRead(SPEED_SW_PIN) == LOW) {
            DESIRED_SPEED = LO_POWER;
        } else {
            DESIRED_SPEED = HI_POWER;
        }

    } else {
        // Nothing is pressed
        DESIRED_SPEED = MIN_POWER;
    }

    int ADJUSTED_SPEED = DESIRED_SPEED - MIN_POWER;

    // == Handle Prior State
    unsigned int DELTA = (millis() - LAST_TIME) * RAMP_CONSTANT;
    switch(DESIRED_SPEED) {
    case HI_POWER:
    case LO_POWER:
        CUR_POWER += DELTA;

        if (CUR_POWER > ADJUSTED_SPEED) {
          CUR_POWER = ADJUSTED_SPEED;
        }

        digitalWrite(POWER_LED_PIN, HIGH);
        break;
    case MIN_POWER:
        if (CUR_POWER > DELTA) {
          CUR_POWER -= DELTA;
        } else {
          CUR_POWER = 0;
        }

        digitalWrite(POWER_LED_PIN, LOW);
        break;
    }

    int POWER = MIN_POWER + CUR_POWER;

    // == Set the desired speed
    ESC.writeMicroseconds(POWER);
    Serial.println(POWER);

    LAST_TIME = millis();
    delay(50);
}