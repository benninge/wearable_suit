#include "RS485_protocol.h"

const byte ENABLE_PIN = 4;
const byte LED_PIN = 13;
int counter = 0;

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
  Serial1.begin(28800);
  Serial.begin(28800);
  pinMode (ENABLE_PIN, OUTPUT);  // driver output enable
  pinMode (LED_PIN, OUTPUT);  // built-in LED
  digitalWrite (ENABLE_PIN, LOW);  // disable sending
}


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
 Serial1.flush();
 digitalWrite (ENABLE_PIN, LOW);  // disable sending

  // receive response
  byte buffer [10];
  byte received = recvMsg (fAvailable, fRead, buffer, sizeof (buffer));

  digitalWrite (LED_PIN, received == 0);  // turn on LED if error
  Serial.print("counter:");
  Serial.println(counter);
  counter++;
  if (received != 0) {
      Serial.println(buffer [0]);
      Serial.println(buffer [1]);
  }
  delay(1000);

}
