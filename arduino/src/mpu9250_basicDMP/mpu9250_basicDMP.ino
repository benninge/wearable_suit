#include "freeram.h"
#include "mpu.h"
#include "I2Cdev.h"
#include "RS485_protocol.h"

const byte ENABLE_PIN = 4;
const byte SLAVE_ID = 1;
union float2bytes { float f; byte b[sizeof(float)]; };


void fWrite (const byte content)
  {
  Serial.write (content);
  }

int fAvailable ()
  {
  return Serial.available ();
  }

 int fRead ()
  {
  return Serial.read ();
  }


int ret;
void setup() {
    Fastwire::setup(400,0);
    Serial.begin(38400);
    ret = mympu_open(200);
    pinMode (ENABLE_PIN, OUTPUT);  // driver output enable
    digitalWrite (ENABLE_PIN, LOW);

#ifdef DMP_DEBUG
    Serial.print("MPU init: "); Serial.println(ret);
    Serial.print("Free mem: "); Serial.println(freeRam());
#endif
}

unsigned int c = 0; //cumulative number of successful MPU/DMP reads
unsigned int np = 0; //cumulative number of MPU/DMP reads that brought no packet back
unsigned int err_c = 0; //cumulative number of MPU/DMP reads that brought corrupted packet
unsigned int err_o = 0; //cumulative number of MPU/DMP reads that had overflow bit set

void loop() {

    byte buffer [10];

    byte received = recvMsg (fAvailable, fRead, buffer, sizeof (buffer));

    if (received != 0)
      {
      if (buffer [0] != SLAVE_ID)
        return;  // not my device

      //TODO: remove
      if (buffer [1] != 2)
        return;  // unknown command

      ret = mympu_update(); // get new sensor data
      delay (2);  // give the master a moment to prepare to receive

      float2bytes ypr0;
      float2bytes ypr1;
      float2bytes ypr2;
      float2bytes gyro0;
      float2bytes gyro1;
      float2bytes gyro2;
      float2bytes accel0;
      float2bytes accel1;
      float2bytes accel2;

      ypr0.f = mympu.ypr[0];
      ypr1.f = mympu.ypr[1];
      ypr2.f = mympu.ypr[2];
      gyro0.f = mympu.gyro[0];
      gyro1.f = mympu.gyro[1];
      gyro2.f = mympu.gyro[2];
      accel0.f = mympu.accel[0];
      accel1.f = mympu.accel[1];
      accel2.f = mympu.accel[2];

//receiving on stm32:
//       for ( int i=0; i < sizeof(float); i++ )
//         f2b.b[i] = read_byte();
//       x = f2b.f;

      byte msg [] = {
         0,  // send to master
		 SLAVE_ID, // sent from SLAVE_ID
         ypr0.b[0],
		 ypr0.b[1],
		 ypr0.b[2],
		 ypr0.b[3],
		 ypr1.b[0],
		 ypr1.b[1],
		 ypr1.b[2],
		 ypr1.b[3],
		 ypr2.b[0],
		 ypr2.b[1],
		 ypr2.b[2],
		 ypr2.b[3],
		 gyro0.b[0],
		 gyro0.b[1],
		 gyro0.b[2],
		 gyro0.b[3],
		 gyro1.b[0],
		 gyro1.b[1],
		 gyro1.b[2],
		 gyro1.b[3],
		 gyro2.b[0],
		 gyro2.b[1],
		 gyro2.b[2],
		 gyro2.b[3],
		 accel0.b[0],
		 accel0.b[1],
		 accel0.b[2],
		 accel0.b[3],
		 accel1.b[0],
		 accel1.b[1],
		 accel1.b[2],
		 accel1.b[3],
		 accel2.b[0],
		 accel2.b[1],
		 accel2.b[2],
		 accel2.b[3],
      };

      digitalWrite (ENABLE_PIN, HIGH);  // enable sending
      sendMsg (fWrite, msg, sizeof msg);
      Serial.flush();
      digitalWrite (ENABLE_PIN, LOW);  // disable sending

     }

#ifdef DMP_DEBUG
    switch (ret) {
	case 0: c++; break;
	case 1: np++; return;
	case 2: err_o++; return;
	case 3: err_c++; return;
	default:
		Serial.print("READ ERROR!  ");
		Serial.println(ret);
		return;
    }

    if (!(c%10)) {
	    Serial.print(np); Serial.print("  "); Serial.print(err_c); Serial.print(" "); Serial.print(err_o);
	    Serial.print(" Y: "); Serial.print(mympu.ypr[0]);
	    Serial.print(" P: "); Serial.print(mympu.ypr[1]);
	    Serial.print(" R: "); Serial.print(mympu.ypr[2]);
	    Serial.print("\tgy: "); Serial.print(mympu.gyro[0]);
	    Serial.print(" gp: "); Serial.print(mympu.gyro[1]);
	    Serial.print(" gr: "); Serial.println(mympu.gyro[2]);
	    Serial.print(" a1: "); Serial.print(mympu.accel[0]);
	    Serial.print(" a2: "); Serial.print(mympu.accel[1]);
	    Serial.print(" a3: "); Serial.println(mympu.accel[2]);
    }
#endif
}
