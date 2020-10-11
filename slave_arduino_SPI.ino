//Slave arduino
#include<SPI.h>

#define LEDpin 7
#define pushpin 2

volatile boolean received;
volatile byte Slavereceived,Slavesend;
int pushvalue;
int x;

void setup()
{
  Serial.begin(115200);
  
  pinMode(pushpin,INPUT);               //set pin 2 as INPUT
  pinMode(LEDpin,OUTPUT);                 // set pin 7 as OUTPUT
  pinMode(MISO,OUTPUT);                   //set MISO as OUTPUT (Have to Send data to Master IN 

  SPCR |= _BV(SPE);                       //Turn on SPI in Slave Mode
  received = false;

  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
  
}

ISR (SPI_STC_vect)                        //Inerrrput routine function 
{
  Slavereceived = SPDR;         // Value received from master if store in variable slavereceived
  received = true;                        //Sets received as True 
}

void loop()
{ if(received)                            //Logic to SET LED ON OR OFF depending upon the value recerived from master
   {
      if(Slavereceived==1) 
      {
        digitalWrite(LEDpin,HIGH);         
        Serial.println("Slave LED ON");
      }else
      {
        digitalWrite(LEDpin,LOW);          
        Serial.println("Slave LED OFF");
      }
      
      pushvalue=digitalRead(pushpin);  
      
      if(pushvalue==HIGH)               //set the value of x to send to master
      {
        x=1;
      }
      else
      {
        x=0;
      }
      
  Slavesend=x;                             
  SPDR = Slavesend;          //Sends the x value to master via SPDR 
  delay(1000);
}
}
