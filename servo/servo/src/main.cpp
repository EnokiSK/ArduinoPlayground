#include <Arduino.h>
#include <Servo.h>

Servo servo_1;

int servo_pin = 2;
int pos = 0;

void setup()
{
  servo_1.attach(servo_pin);
  servo_1.write(pos);
}

void loop()
{
  for (pos = 0; pos < 175; pos++)
  {

    servo_1.write(pos);
    delay(5);
  }
  delay(1000);

  for (; pos > 10; pos--)
  {
    servo_1.write(pos);
    delay(5);
  }
  delay(1000);
}
