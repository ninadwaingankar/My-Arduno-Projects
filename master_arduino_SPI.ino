
//SPI MASTER (ARDUINO)
//SPI communication protocol  between 2 Arduino UNO

#include<SPI.h>                             
#define LED 7           
#define ippush 2

int pushvalue;
int x;
void setup()

{
  Serial.begin(115200);                   //Serial Communication at Baud Rate 115200 
  
  pinMode(ippush,INPUT);                  //pin 2 as input 
  pinMode(LED,OUTPUT);                    //pin 7 as Output
  
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //sets clock for SPI communication at 8 (16/8=2Mhz)
  digitalWrite(SS,HIGH);                  //sets SlaveSelect as HIGH (master disconnnect with slave)
}

void loop(void)
{
  byte Mastersend,Mastereceive;          
  pushvalue=digitalRead(ippush);   
  
  if(pushvalue==HIGH)                //set x value (To be sent to slave
  {
    x=1;
  }
  else
  {
    x=0;
  }
  
  digitalWrite(SS,LOW);                  //Starts communication with Slave connected to master
  
  Mastersend = x;                            
  Mastereceive=SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave
  
  if(Mastereceive == 1)                   //set LED output with value received from slave
  {
    digitalWrite(LED,HIGH);              
    Serial.println("Master LED ON");
  }
  else
  {
   digitalWrite(LED,LOW);               
   Serial.println("Master LED OFF");
  }
  delay(1000);
}
