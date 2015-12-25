#include "RoboArm.h"


//
const int LEFT_Ctrl = A1;
const int RIGHT_Ctrl = A3;
/********************DATA AREA**********************/
typedef struct
{
	short pPin;
	short nPin;
	short ENPin;
}AWHEEL;

AWHEEL L_wheel = {22, 11};
AWHEEL R_wheel = {24, 12};

//LEFT
static int LEFT_times = 0;
static int LEFT_avg[10] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};

//RIGHT
static int RIGHT_times;
static int RIGHT_avg[10] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};
/********************DATA AREA**********************/

void WheelDrive(AWHEEL *wheel, int val){
	if (val > 0){//正向转动
		digitalWrite(wheel.pPin, HIGH);
		digitalWrite(wheel.nPin, LOW);
		analogWrite(wheel.ENPin, val);
	}
	else if (val < 0){//反向转动
		digitalWrite(wheel.nPin, HIGH);
		digitalWrite(wheel.pPin, LOW);
		analogWrite(wheel.ENPin, -val);
	}
	else{//STOP
		digitalWrite(wheel.ENPin, LOW);
	}
}

void MotorControl(){//Main
	int val = 0;
	{
        LEFT_times = (LEFT_times+1)%10;
        LEFT_avg[LEFT_times] = _pulseIn(LEFT_Ctrl);
        val = map(sum10(LEFT_avg), 990, 2020, -255, 255);
        WheelDrive(L_wheel, val);
    }
    {
    	RIGHT_times = (RIGHT_times+1)%10;
        RIGHT_avg[RIGHT_times] = _pulseIn(RIGHT_Ctrl);
        val = map(sum10(RIGHT_avg), 990, 2020, -255, 255);
        WheelDrive(R_wheel, val);
    }
}