#ifndef _RoboArm_H_             //如果没有定义宏_MY_HEAD_H_
#define _RoboArm_H_             //则，定义该宏名

//以下是被保护的代码区
//进行相应的全局变量和结构体类型定义
#define   AUTO_SW     A0
#define   MOTOR_IN    A1
#define   MOVECMD_IN  A2
#define   SERVO_IN    A3
#define   FIST_IN     A5

#endif  




/**************状态分段***************/
int _pulseIn(int);
int _digiSwitch(int);
int _analogSwitch(int);
/**************状态分段***************/


/*************Servo相关函数***********/
void Servo_Reset(void);
void Servo_Drive(char);
/*************Servo相关函数***********/


/************直流电机相关*************/
void DC_Rotate(int);
void DC_SetPos(void);
/************直流电机相关*************/


/*************爪子相关****************/
void Fist_StatusChange(int);
void Hold_Tight(void);
void Hold_Release(void);
/*************爪子相关****************/


