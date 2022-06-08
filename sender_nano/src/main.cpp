#include <Arduino.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;
void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  if (!aht.begin())
  {
    Serial.println("Could not find AHT? Check wiring");
    while (1)
      delay(10);
  }
  Serial.println("AHT10 or AHT20 found\n");
  Adafruit_Sensor *temperature_sensor = aht.getTemperatureSensor();
}

void loop()
{
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  Serial.write(10);
  delay(1000);
}