//SPI probelm statement 2: slave code

#include <SPI.h> 
int incoming = 0; 

void setup() 
{ 
Serial.begin(9600); 
SPI.begin(); 
digitalWrite(SS,HIGH); 
} 
void loop() 
{ 
if(serial.available() != 0) 
{ 
digitalWrite(SS,LOW); 
SPI.transfer(“NINADWAINGANKAR”); 
} 
} 
