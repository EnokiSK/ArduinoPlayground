#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>
int seconds = 0;
int x;
int y;
int z;

LiquidCrystal lcd_1(7, 6, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  digitalWrite(SS, HIGH);
  x = 1;
  lcd_1.begin(20, 4);
  lcd_1.clear();
  lcd_1.print("--------------------");
}

void printHex(uint8_t num) {
  char hexCar[2];

  sprintf(hexCar, " %02X", num);
  Serial.print(hexCar);
}

void loop()
{
  byte m_send, m_receive;
  lcd_1.setCursor(5, 1);
  lcd_1.print("Sekundy: ");
  lcd_1.print(seconds);
  lcd_1.print(" s  ");
  lcd_1.setCursor(5, 2);
  lcd_1.print("Teplota: ");
  lcd_1.print(z);
  lcd_1.print(" C ");
  lcd_1.setCursor(5, 3);
  lcd_1.print("Vlhkost: ");
  lcd_1.print(y);

  lcd_1.print(" %rH ");
  seconds++;
  if (x == 1)
  {
    x = 0;
  }
  else
  {

    x = 1;
  }

  delay(1000);
  digitalWrite(SS, LOW);
  /*
    m_receive = SPI.transfer(x);

    Serial.println(m_receive);


  if(x==1){

  z = m_receive;

  }
  else{

    y=m_receive;
  }
  */

  char buf[10];

  buf[0] = '$';
  SPI.transfer(buf, sizeof(buf));
  for(char i=0; i<sizeof(buf); i++)
    printHex(buf[i]);
  Serial.println();

  if(buf[9] == '#')
  {
    float teplota;
    float vlhkost;
    memcpy(&teplota, buf, 4);
    memcpy(&vlhkost, buf + 4, 4);
    Serial.println(teplota);
    Serial.println(vlhkost);
  }
  memset(buf, 0, sizeof(buf));
}
