#include "RS485_protocol.h"

const byte ENABLE_PIN = 4;
const byte LED_PIN = 13;
union float2bytes { float f; byte b[sizeof(float)]; };
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
  Serial1.begin(38400);
  Serial.begin(38400);
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
 //digitalWrite (ENABLE_PIN, HIGH);  // enable sending
 //sendMsg (fWrite, msg, sizeof msg);
 //Serial1.flush();
 //digitalWrite (ENABLE_PIN, LOW);  // disable sending

  // receive response
 float2bytes ypr0;
 float2bytes ypr1;
 float2bytes ypr2;
 float2bytes gyro0;
 float2bytes gyro1;
 float2bytes gyro2;
 float2bytes accel0;
 float2bytes accel1;
 float2bytes accel2;

  byte buffer [60];
  byte received = recvMsg (fAvailable, fRead, buffer, sizeof (buffer));

  //receiving on stm32:
         for ( int i=0; i < sizeof(float); i++ )
           ypr0.b[i] = buffer[2+i];
         for ( int i=0; i < sizeof(float); i++ )
           ypr1.b[i] = buffer[2+4+i];
         for ( int i=0; i < sizeof(float); i++ )
           ypr2.b[i] = buffer[2+8+i];
         for ( int i=0; i < sizeof(float); i++ )
           gyro0.b[i] = buffer[12+2+i];
         for ( int i=0; i < sizeof(float); i++ )
           gyro1.b[i] = buffer[12+2+4+i];
         for ( int i=0; i < sizeof(float); i++ )
           gyro2.b[i] = buffer[12+2+8+i];
         for ( int i=0; i < sizeof(float); i++ )
           accel0.b[i] = buffer[24+2+i];
         for ( int i=0; i < sizeof(float); i++ )
           accel1.b[i] = buffer[24+2+4+i];
         for ( int i=0; i < sizeof(float); i++ )
           accel2.b[i] = buffer[24+2+8+i];

  digitalWrite (LED_PIN, received == 0);  // turn on LED if error
  Serial.print("counter:");
  Serial.println(counter);
  counter++;
  if (received != 0) {
      Serial.print("Target:"); Serial.println(buffer [0]);
      Serial.print("Source:"); Serial.println(buffer [1]);
	    Serial.print(" Y: "); Serial.print(ypr0.f);
	    Serial.print(" P: "); Serial.print(ypr1.f);
	    Serial.print(" R: "); Serial.print(ypr2.f);
	    Serial.print("\tgy: "); Serial.print(gyro0.f);
	    Serial.print(" gp: "); Serial.print(gyro1.f);
	    Serial.print(" gr: "); Serial.println(gyro2.f);
	    Serial.print(" a1: "); Serial.print(accel0.f);
	    Serial.print(" a2: "); Serial.print(accel1.f);
	    Serial.print(" a3: "); Serial.println(accel2.f);

  }
  delay(100);

}
