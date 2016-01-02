#include "tim.h"
#include "RoboArmCtrl.h"
#include "mxconstants.h"

const static int SDE = 1;

/***************Servo相关函数*******************/
float Pos2Per(char angle)
{
	float Per = 7.5 + (angle * 1.5 / 90);
	return Per;
}

void Servo_Reset(){
  Servo_Drive(0, 90);
  Servo_Drive(1, 90);
}

void Servo_Drive(unsigned char servor, char pos){
	float pert = Pos2Per(pos);
  switch(servor){
    case 0:
			pwm_write(4, 2, pert);
		break;
    case 1:
			pwm_write(4, 1, pert);
		break;
  }
}
/***************Servo相关函数*******************/

/***************直流电机相关*******************/
void DC_Rotate(uint16_t data){
  
  switch(data){
    case 0://Backward
			pwm_write(3, 1, 1);
			HAL_GPIO_WritePin(GPIOB, nPinM_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, pPinM_Pin, GPIO_PIN_RESET);
    break;
    case 1://No Reaction
      HAL_GPIO_WritePin(GPIOB, nPinM_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, pPinM_Pin, GPIO_PIN_RESET);
    break;
    case 2://Forward
			pwm_write(3, 1, 1);
      HAL_GPIO_WritePin(GPIOB, nPinM_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, pPinM_Pin, GPIO_PIN_SET);
    break;
  }
  
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
		pwm_write(3, 1, (-1)*pwm);
	}
}


void DC_SetPosX(){
  if (read_POS_X == 0) return;
  //pwmMove();
	{/******************************************/
		if (read_POS_X - POS_X > SDE){
			DC_Rotate(0);
		}
		else if (POS_X - read_POS_X> SDE){
			DC_Rotate(2);
		}
		else {
			DC_Rotate(1);
		}
	}/******************************************/
}

/***************直流电机相关*******************/

/***************爪子相关*******************/
void Fist_StatusChange(unsigned char data){
    switch(data){
    case 0:
      if (FIST_STAT != 0){
        FIST_STAT = 0;
        Hold_Tight();
      }
    break;
    case 1://RESET
      if (FIST_STAT != 1){
        FIST_STAT = 1;
        HAL_GPIO_WritePin(GPIOB, nPinF_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, pPinF_Pin, GPIO_PIN_RESET);
      }
    break;
    case 2:
      if (FIST_STAT != 2){
        FIST_STAT = 2;
        Hold_Release();
      }
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
