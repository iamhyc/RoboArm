#include "stdint.h"

#ifndef _Cart_H_             //如果没有定义宏_MY_HEAD_H_
#define _Cart_H_             //则，定义该宏名

static int LEFT_VAL;
static int RIGHT_VAL;

void WheelDrive_L(float);
void WheelDrive_R(float);
void MotorControl(void);

#endif
