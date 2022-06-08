#include <Arduino.h>

const int trig = 2;
const int echo = 3;

long cas;
float vzdialenost;
float vzdialenost_v_m;
void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}
void loop()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  cas = pulseIn(echo, HIGH);
  vzdialenost = cas * 0.034 / 2;
  Serial.print("Vzdialenosťje : ");
  Serial.print(vzdialenost);
  Serial.print(" CM = ");
  vzdialenost_v_m = vzdialenost / 100;
  Serial.print(vzdialenost_v_m);
  Serial.println(" M");
}