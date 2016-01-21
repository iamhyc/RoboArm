#include "Cart.h"
#include "usart.h"
#include "RoboArm.h"

/********************DATA AREA**********************/
extern int POS_X;//DC Motor POS
extern int POS_Y;//YAW
extern int POS_Z;//ROLL
extern float read_POS_X;
extern char FIST_STAT;
extern char AutoSw;

extern int LEFT_VAL;
extern int RIGHT_VAL;

static const uint16_t TL = 87;
static const uint16_t TM = 118;
static const uint16_t TH = 179;
static const uint16_t delta = 5;
/********************DATA AREA**********************/


void Initialize()
{
		POS_X = 0;//DC Motor POS
		POS_Y = 0;
		POS_Z = 0;
		read_POS_X = 0;
}


/**************状态分段***************/
int SwSwitch(int data)
{
	if (data == 8571)
		return 2;
	if (data == 118)
		return 0;
	if (data == 176)
		return 1;
	return -1;
}

uint16_t _digiSwitch(uint16_t data){
  
  if (data >= TL && data <= TL + delta)
    return 0;
  else if (data >= TM && data <= TM + delta)
    return 1;
  else if (data >= TH - delta && data <= TH + delta)
    return 2;
  else return 1;
}

int __map(int level, int LR, int HR)
{
	if (level > TH || level < TL)
		return 0;
	
	level = level - TM;
	
	if (level >= 0)
		return level * HR / (TH - TM);
	else if (level < 0){
		return (-1) * level * LR / (TM - TL);
	}
	return 0;
}


/**************状态分段***************/
void getchaa(char ch[9],uint16_t in)
{
	int i;
	for(i=7;i>=0;i--)
	{
		ch[i]=in%10+'0'-0;
		in=in/10;
	}
	ch[8] = '\n';
}

/***************信号控制*******************/


void readControl(signal_t data){
	
		int tmp = SwSwitch(data.AutoSw);
		if (tmp != -1)
			AutoSw = tmp;
	
  switch(AutoSw){
    case 1://手动模式
		POS_X = __map(data.DM_IN, -100, 100);
		POS_Y = __map(data.YAW_IN, -90, 90)  + 30;
		POS_Z = __map(data.ROLL_IN, -90, 90) + 30;
    FIST_STAT = _digiSwitch(data.FIST_IN);
    
    //DC_SetPosX();
		DC_Move();
    Servo_Drive(1, POS_Y);
		HAL_Delay(10);
    Servo_Drive(0, POS_Z);
    Fist_StatusChange(FIST_STAT);
		
		break;
		
		case 2:
			//read_POS_X = ((float)stcAngle.Angle[0]/32768*180);
			LEFT_VAL = __map(data.YAW_IN, -100, 100);
			RIGHT_VAL = __map(data.ROLL_IN, -100, 100);
			MotorControl();
		break;
		
		case 0:
		default:
			break;
  }
}
/***************信号控制*******************/
