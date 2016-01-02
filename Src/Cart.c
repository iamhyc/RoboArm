#include "Cart.h"
#include "tim.h"
#include "mxconstants.h"

/********************DATA AREA**********************/

/********************DATA AREA**********************/

void WheelDrive_L(float val){
	if (val > 0){//正向转动
		HAL_GPIO_WritePin(GPIOA, nPinL_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, pPinL_Pin, GPIO_PIN_SET);
		pwm_write(3, 2, val);
	}
	else if (val < 0){//反向转动
		HAL_GPIO_WritePin(GPIOA, nPinL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, pPinL_Pin, GPIO_PIN_RESET);
		pwm_write(3, 2, -val);
	}
	else{//STOP
		HAL_GPIO_WritePin(GPIOA, nPinL_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, pPinL_Pin, GPIO_PIN_RESET);
	}
}

void WheelDrive_R(float val){
	if (val > 0){//正向转动
		HAL_GPIO_WritePin(GPIOA, nPinR_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, pPinR_Pin, GPIO_PIN_SET);
		pwm_write(3, 2, val);
	}
	else if (val < 0){//反向转动
		HAL_GPIO_WritePin(GPIOA, nPinR_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, pPinR_Pin, GPIO_PIN_RESET);
		pwm_write(3, 2, -val);
	}
	else{//STOP
		HAL_GPIO_WritePin(GPIOA, nPinR_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, pPinR_Pin, GPIO_PIN_RESET);
	}
}

void MotorControl(){//Main
	
    WheelDrive_L(LEFT_VAL);
		WheelDrive_R(RIGHT_VAL);
}
