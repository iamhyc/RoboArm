#ifndef _PixyModule_H_             //如果没有定义宏_MY_HEAD_H_
#define _PixyModule_H_             //则，定义该宏名

//以下是被保护的代码区
//进行相应的全局变量和结构体类型定义
typedef struct
{
	short DC_DATA;
	short SERVO_DATA;
	short FIST_DATA;
}Arm_Ctrl_t;

typedef struct
{
	short x;
	short y;
	short width;
	short height;
}block_t;

#endif  

Arm_Ctrl_t getControInfo(void);
