#include "RS485_protocol.h"

const byte ENABLE_PIN = 10;
const byte SLAVE_ID = 1;

  void fWrite (const byte what)
    {
    Serial.write (what);  
    }
    
  int fAvailable ()
    {
    return Serial.available ();  
    }
  
  int fRead ()
    {
    return Serial.read ();  
    } 
void setup()
{
  Serial.begin (28800);
  pinMode (ENABLE_PIN, OUTPUT);  // driver output enable
}

void loop()
{
  byte buffer [10];
  
  byte received = recvMsg (fAvailable, fRead, buffer, sizeof (buffer));
  
  if (received)
    {
    if (buffer [0] != SLAVE_ID)
      return;  // not my device
      
    if (buffer [1] != 2)
      return;  // unknown command
    
    byte msg [] = {
       0,  // device 0 (master)
       3,  // turn light on command received
    };
    
    delay (1);  // give the master a moment to prepare to receive
    digitalWrite (ENABLE_PIN, HIGH);  // enable sending
    sendMsg (fWrite, msg, sizeof msg);
    delayMicroseconds (660);
    digitalWrite (ENABLE_PIN, LOW);  // disable sending
    
   }  
   
} 
