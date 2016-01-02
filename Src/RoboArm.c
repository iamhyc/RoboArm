#include "Cart.h"
#include "usart.h"
#include "RoboArm.h"
#include "RoboArmCtrl.h"

/********************DATA AREA**********************/

static const uint16_t TL = 1000;
static const uint16_t TH = 3000;
/********************DATA AREA**********************/


void Initialize()
{
		POS_X = 0;//DC Motor POS
		POS_Y = 0;
		POS_Z = 0;
		FIST_STAT = 0;
		read_POS_X = 0;
}


/**************状态分段***************/
uint16_t _digiSwitch(uint16_t data){
  //950-970, 1490-1510, 2030-2050
  if (data >= 900 && data <= 1000)
    return 0;
  else if (data >= 1400 && data <= 1600)
    return 1;
  else if (data >= 2000 && data <= 2100)
    return 2;
  else return 0;
}

uint16_t _analogSwitch(uint16_t data){
  if (data < 1400)
    return 0;
  else if (data >= 1400 && data <= 1500)
    return 1;
  else if (data >1600)
    return 2;
  else return 0;
}

uint32_t map(uint32_t val, int eL, int eH, int nL, int nH)
{
	if (eL > eH){
		uint16_t tmp = eL; eL = eH; eH = tmp;
	}
	uint32_t ans = (val * (nH - nL) / (eH - eL)) + eL;
	return ans;
}
/**************状态分段***************/


/***************信号控制*******************/
void readControl(signal_t data){
  
  //switch(ctrl_sig){
    //手动模式
		read_POS_X = ((float)stcAngle.Angle[0]/32768*180);
		POS_X = map(data.DM_IN, TL, TH, -30, 30);
		POS_Y = map(data.YAW_IN, TL, TH, 0, 180);
		POS_Z = map(data.ROLL_IN, TL, TH, 0, 180);
    FIST_STAT = _digiSwitch(data.FIST_IN);
    
    DC_SetPosX();
    Servo_Drive(1, POS_Y);
    Servo_Drive(0, POS_Z);
    Fist_StatusChange(FIST_STAT);
    //break;
		//MoveControl();
		//LEFT_VAL = map(data.YAW_IN, TL, TH, -100, 100);
		//RIGHT_VAL = map(data.ROLL_IN, TL, TH, -100, 100);
  //}
}
/***************信号控制*******************/
