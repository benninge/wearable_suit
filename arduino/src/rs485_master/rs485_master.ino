#include "RS485_protocol.h"

const byte ENABLE_PIN = 10;
const byte LED_PIN = 13;


// callback routines
  
  void fWrite (const byte content)
    {
    Serial1.write (content);  
    }
    
  int fAvailable ()
    {
    return Serial1.available ();  
    }
  
  int fRead ()
    {
    return Serial1.read ();  
    } 
    
void setup()
{
  Serial1.begin (28800);
  pinMode (ENABLE_PIN, OUTPUT);  // driver output enable
  pinMode (LED_PIN, OUTPUT);  // built-in LED
}  // end of setup
  

void loop()
{
      
  byte msg [] = { 
     1,    // id 
     2,    // msg
     3 // test
  };

  // send to slave  
 digitalWrite (ENABLE_PIN, HIGH);  // enable sending
 sendMsg (fWrite, msg, sizeof msg);
 delayMicroseconds (660);
 digitalWrite (ENABLE_PIN, LOW);  // disable sending  

  // receive response  
  byte buffer [10];
  byte received = recvMsg (fAvailable, fRead, buffer, sizeof buffer);
  
  digitalWrite (LED_PIN, received == 0);  // turn on LED if error    

}
