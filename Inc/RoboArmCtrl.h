#include "stdint.h"

#ifndef _RoboArmCtrl_H_             //如果没有定义宏_MY_HEAD_H_
#define _RoboArmCtrl_H_             //则，定义该宏名

static int POS_X;//DC Motor POS
static int POS_Y;//YAW
static int POS_Z;//ROLL
static char FIST_STAT;
static float read_POS_X;

/*************Servo相关函数***********/
void Servo_Reset(void);//初始化两个舵机
void Servo_Drive(unsigned char, char);//(char ServoSelect, char data);
/*************Servo相关函数***********/


/************直流电机相关*************/
void DC_Rotate(uint16_t);
void DC_SetPosX(void);
/************直流电机相关*************/


/*************爪子相关****************/
void Fist_StatusChange(unsigned char);
void Hold_Tight(void);
void Hold_Release(void);
/*************爪子相关****************/

void DC_Rotate(uint16_t);
void DC_pwmMove(void);

#endif


