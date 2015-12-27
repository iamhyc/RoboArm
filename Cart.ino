 #include "Cart.h"
#include "RoboArm.h"

const int LEFT_Ctrl = A1;
const int RIGHT_Ctrl = A3;
/********************DATA AREA**********************/


AWHEEL L_wheel = {22, 23, 2};
AWHEEL R_wheel = {24, 25, 3};

//LEFT
static int LEFT_times = 0;
static int LEFT_avg[10] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};

//RIGHT
static int RIGHT_times = 0;
static int RIGHT_avg[10] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};
/********************DATA AREA**********************/

void WheelDrive(AWHEEL wheel, int val){
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
        LEFT_avg[LEFT_times] = 1000;//_pulseIn(LEFT_Ctrl);
        val = map(sum10(LEFT_avg), 990, 2020, -255, 255);
        WheelDrive(L_wheel, 100);
    }
    {
    	RIGHT_times = (RIGHT_times+1)%10;
        RIGHT_avg[RIGHT_times] = 2000;//_pulseIn(RIGHT_Ctrl);
        val = map(sum10(RIGHT_avg), 990, 2020, -255, 255);
        WheelDrive(R_wheel, 200);
    }
}
