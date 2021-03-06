#include "freeram.h"
#include "mpu.h"
#include "I2Cdev.h"
#include "RS485_protocol.h"

//#define DMP_DEBUG

const byte ENABLE_PIN = 3;
const byte RECEIVE_PIN = 4;
const byte SLAVE_ID = 4;
union float2bytes { float f; byte b[sizeof(float)]; };
float2bytes ypr0;
float2bytes ypr1;
float2bytes ypr2;
float2bytes gyro0;
float2bytes gyro1;
float2bytes gyro2;
float2bytes accel0;
float2bytes accel1;
float2bytes accel2;


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
    Serial.begin(57600);
    ret = mympu_open(100);
    pinMode (ENABLE_PIN, OUTPUT);
    pinMode (RECEIVE_PIN, OUTPUT);// driver output enable
    digitalWrite (ENABLE_PIN, LOW);
    digitalWrite (RECEIVE_PIN, LOW);

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
    ret = mympu_update(); // get new sensor data

    byte buffer [10];

    byte received = recvMsg (fAvailable, fRead, buffer, sizeof (buffer), 50);

      if (received != 0){

		  if (buffer [0] != SLAVE_ID)
			return;  // not me

		  if (buffer [1] != 0)
			return;  // sender not master


		  ypr0.f = mympu.ypr[0];
		  ypr1.f = mympu.ypr[1];
		  ypr2.f = mympu.ypr[2];
		  gyro0.f = mympu.gyro[0];
		  gyro1.f = mympu.gyro[1];
		  gyro2.f = mympu.gyro[2];
		  accel0.f = mympu.accel[0];
		  accel1.f = mympu.accel[1];
		  accel2.f = mympu.accel[2];

		  //delay (1);  // give the master a moment to prepare to receive

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
		  digitalWrite (RECEIVE_PIN, HIGH);  // enable sending
		  delay(1);
		  sendMsg (fWrite, msg, sizeof msg);
		  Serial.flush();
		  digitalWrite (ENABLE_PIN, LOW);  // disable sending
		  digitalWrite (RECEIVE_PIN, LOW);  // disable sending
		  //delay (100);

     }

#ifdef DMP_DEBUG
    switch (ret) {
	case 0: c++; break;
	case 1: np++; break;
	case 2: err_o++; break;
	case 3: err_c++; break;
	default:
		Serial.print("READ ERROR!  ");
		Serial.println(ret);
		break;;
    }

	    Serial.print(c); Serial.print(np); Serial.print("  "); Serial.print(err_c); Serial.print(" "); Serial.print(err_o);
	    Serial.print(" Y: "); Serial.print(mympu.ypr[0]);
	    Serial.print(" P: "); Serial.print(mympu.ypr[1]);
	    Serial.print(" R: "); Serial.print(mympu.ypr[2]);
	    Serial.print("\tgy: "); Serial.print(mympu.gyro[0]);
	    Serial.print(" gp: "); Serial.print(mympu.gyro[1]);
	    Serial.print(" gr: "); Serial.println(mympu.gyro[2]);
	    Serial.print(" a1: "); Serial.print(mympu.accel[0]);
	    Serial.print(" a2: "); Serial.print(mympu.accel[1]);
	    Serial.print(" a3: "); Serial.println(mympu.accel[2]);
#endif
}
