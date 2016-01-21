#include "Cart.h"
#include "tim.h"
#include "usart.h"
#include "mxconstants.h"

/********************DATA AREA**********************/
int LEFT_VAL;
int RIGHT_VAL;
/********************DATA AREA**********************/

void WheelDrive_L(float val){
	if (val > 10){//正向转动
		HAL_GPIO_WritePin(GPIOA, nPinL_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, pPinL_Pin, GPIO_PIN_SET);
		//callMessage("positive");
		pwm_write(3, 2, val);
	}
	else if (val < -10){//反向转动
		HAL_GPIO_WritePin(GPIOA, nPinL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, pPinL_Pin, GPIO_PIN_RESET);
		//callMessage("negative");
		pwm_write(3, 2, -val);
	}
	else{//STOP
		HAL_GPIO_WritePin(GPIOA, nPinL_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, pPinL_Pin, GPIO_PIN_RESET);
	}
}

void WheelDrive_R(float val){
	if (val > 5){//正向转动
		HAL_GPIO_WritePin(GPIOA, nPinR_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, pPinR_Pin, GPIO_PIN_SET);
		pwm_write(3, 3, val);
	}
	else if (val < -5){//反向转动
		HAL_GPIO_WritePin(GPIOA, nPinR_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, pPinR_Pin, GPIO_PIN_RESET);
		pwm_write(3, 3, -val);
	}
	else{//STOP
		HAL_GPIO_WritePin(GPIOA, nPinR_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, pPinR_Pin, GPIO_PIN_RESET);
	}
}

void MotorControl(){//Main
    WheelDrive_L(LEFT_VAL);
		HAL_Delay(10);
		WheelDrive_R(RIGHT_VAL);
}
