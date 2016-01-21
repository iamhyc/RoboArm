#include "stdint.h"
#include "RoboArmCtrl.h"

#ifndef _RoboArm_H_             //如果没有定义宏_MY_HEAD_H_
#define _RoboArm_H_             //则，定义该宏名

//以下是被保护的代码区
//进行相应的全局变量和结构体类型定义

typedef struct{
	uint32_t FIST_IN;
	uint32_t DM_IN;
	uint32_t YAW_IN;
	uint32_t ROLL_IN;
	uint32_t AutoSw;
}signal_t;

void Initialize(void);
void readControl(signal_t);

#endif

