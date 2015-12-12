#define   AUTO_SW     A0
#define   MOTOR_IN    A1
#define   MOVECMD_IN  A2
#define   SERVO_IN    A3
#define   FIST_IN     A5


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


