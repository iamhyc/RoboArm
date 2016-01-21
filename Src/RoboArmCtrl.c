#include "tim.h"
#include "usart.h"
#include "RoboArmCtrl.h"
#include "mxconstants.h"

//const static int SDE = 1;

/**************DATA AREA**************/
int POS_X = 0;//DC Motor POS
int POS_Y = 0;//YAW
int POS_Z = 0;//ROLL
float read_POS_X = 0;
char FIST_STAT = 0;
char AutoSw;
/**************DATA AREA**************/

/***************Servo相关函数*******************/
float Pos2Per(int angle)
{
	float Per = 7.5 + (angle * 5 / 90);
	return Per;
}

void Servo_Reset(){
  Servo_Drive(0, 0);
  Servo_Drive(1, 0);
}

void Servo_Drive(int servor, int pos){

	float pert = Pos2Per(pos);

  switch(servor){
    case 0://ROLL SERVO
			HAL_Delay(1);
			pwm_write(4, 2, pert);
		break;
    case 1://YAW SERVO
			HAL_Delay(1);
			pwm_write(4, 1, pert);
		break;
  }
}
/***************Servo相关函数*******************/

/***************直流电机相关*******************/
void DC_Rotate(uint16_t data){

  switch(data){
    case 0://Backward
			HAL_GPIO_WritePin(GPIOB, nPinM_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, pPinM_Pin, GPIO_PIN_RESET);
    break;
    case 1://No Reaction
      HAL_GPIO_WritePin(GPIOB, nPinM_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, pPinM_Pin, GPIO_PIN_RESET);
    break;
    case 2://Forward
      HAL_GPIO_WritePin(GPIOB, nPinM_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, pPinM_Pin, GPIO_PIN_SET);
    break;
  }
  
}

void DC_Move()
{
	
	float pert = POS_X;
	
	if (pert > 1){
		DC_Rotate(2);
		pwm_write(3, 1, pert);
		return;
	}
	
	if (pert < -1){
		DC_Rotate(0);
		pwm_write(3, 1, -pert);
		return;
	}
	DC_Rotate(1);
}

void DC_pwmMove(){
  float diff = read_POS_X - POS_X;
  int pwm = 100 * diff / 10;
	
  if (pwm > 0)
	{
		HAL_GPIO_WritePin(GPIOB, nPinM_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, pPinM_Pin, GPIO_PIN_SET);
		pwm_write(3, 1, pwm);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, nPinM_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, pPinM_Pin, GPIO_PIN_RESET);
		pwm_write(3, 1, -pwm);
	}
}

/***************直流电机相关*******************/

/***************爪子相关*******************/
void Fist_StatusChange(char data){
    switch(data){
    case 0:
        Hold_Tight();
    break;
    case 1://RESET
        HAL_GPIO_WritePin(GPIOB, nPinF_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, pPinF_Pin, GPIO_PIN_RESET);
    break;
    case 2:
        Hold_Release();
    break;
    default:
    break;
  }
}

void Hold_Tight(){
  HAL_GPIO_WritePin(GPIOB, nPinF_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, pPinF_Pin, GPIO_PIN_RESET);
}

void Hold_Release(){
	HAL_GPIO_WritePin(GPIOB, nPinF_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, pPinF_Pin, GPIO_PIN_SET);
}
/***************爪子相关*******************/
