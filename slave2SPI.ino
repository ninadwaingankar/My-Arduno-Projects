#include <SPI.h> 
volatile char incoming; 
volatile boolean process; 
void setup() 
{ 
Serial.begin(9600); 
SPCR |= _BV(SPE); 
process = false; 
SPI.attachInterrupt(); 
} 
ISR (SPI_STC_vect) 
{ 
incoming = SPDR; 
process = true; 
} 
void loop()
{ 
if(process) 
{ 
Serial.println(incoming); 
} 
} 
