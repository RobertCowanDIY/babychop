/*
Copyright (c) <2014> <Ankur Mohan>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

Note: Select the mode (program mode/throttle setting mode/normal mode), run this code, 
then power on the ESC. Don't power on the ESC before this code is executing, otherwise
the ESC will see random values on the PWM pin.
*/
// Need the Servo library
#include <Servo.h>

int power = 0;

Servo ESC;

void setup() {
  //delay(1000);
  pinMode(4, INPUT_PULLUP);
  ESC.attach(11, 800, 2000);
  ESC.writeMicroseconds(1000);
  //delay(4000);
}

void loop()
{
  if (digitalRead(4)== LOW) {
    //ESC.attach(11, 1000, 2000);
    //ESC.writeMicroseconds(1000);
    ESC.writeMicroseconds(1100);
    digitalWrite(13, HIGH);
    delay(100);
  } else {
    ESC.writeMicroseconds(800);
    //ESC.detach();
  }
  digitalWrite(13, LOW);
}
