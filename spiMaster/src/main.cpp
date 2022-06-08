#include <Arduino.h>
#include <SPI.h>

void setup(void)
{

    digitalWrite(SS, HIGH); // ensure SS stays high for now

    // Put SCK, MOSI, SS pins into output mode
    // also put SCK, MOSI into LOW state, and SS into HIGH state.
    // Then put SPI hardware into Master mode and turn SPI on
    SPI.begin();

    // Slow down the master a bit
    SPI.setClockDivider(SPI_CLOCK_DIV8);

} // end of setup

void loop(void)
{

    int c;
    digitalWrite(SS, LOW);
    c = SPI.transfer16(10);
    digitalWrite(SS, HIGH);
    delay(1000); 
} 