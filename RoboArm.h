#ifndef _RoboArm_H_             //如果没有定义宏_MY_HEAD_H_
#define _RoboArm_H_             //则，定义该宏名

//以下是被保护的代码区
//进行相应的全局变量和结构体类型定义
#define   AUTO_SW     A0
#define   MOTOR_IN    A1
#define   MOVECMD_IN  A2
#define   SERVOR_0_IN  A3//POS_Z
#define	  SERVOR_1_IN  A4//POS_Y
#define   FIST_IN     A5

#endif  




/**************状态分段***************/
int _pulseIn(int);
int _digiSwitch(int);
int _analogSwitch(int);
/**************状态分段***************/


/*************Servo相关函数***********/
void Servo_Reset(void);//初始化两个舵机
void Servo_Drive(char, char);//(char ServoSelect, char data);
/*************Servo相关函数***********/


/************直流电机相关*************/
void DC_Rotate(int);
void DC_SetPosX(void);
/************直流电机相关*************/


/*************爪子相关****************/
void Fist_StatusChange(int);
void Hold_Tight(void);
void Hold_Release(void);
/*************爪子相关****************/


/*************Pixy主体****************/
int ImgFilter(int, int, block_t);
/*************Pixy主体****************/