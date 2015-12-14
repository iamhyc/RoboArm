#include "RoboArm.h"
#include "PixyModule.h"

/*********Math Constant*********/
static char IMG_SEP = 90;//图像相似度标准差(百分比)
/*********Math Constant*********/

/*********控制信号状态*********/
static int DC_DATA;
static int SERVO_DATA;
static int FIST_DATA;
/*********控制信号状态*********/

/*********状态机FSM*********/
static int status = 0;
static bool targetLock;

static block_t F1, F2;//两个分开的爪子
static block_t target;
	//图像消抖
	static block_t *arr;
  static int filter_back;
	static char try_times = 0;
/*********状态机FSM*********/

char couplingRate(block_t t1, block_t t2){
	int area_tmp;
	if (t1.y > t2.y){
		block_t tmp = t1; t1 = t2; t2 = tmp;
	}
	if (t1.x > t2.x)
		area_tmp = (t1.x+t1.width-t2.x)*(t2.height+t2.y-t1.y);
	else
		area_tmp = (t2.x+t2.width-t1.x)*(t2.y-t1.y-t1.height);
	return (char)(2*area_tmp/(t1.width*t1.height + t2.width*t2.height));
}

bool isImageSame(block_t t1, block_t t2){
	if (couplingRate(t1, t2) > IMG_SEP)
		return true;
	else
		return false;
}

block_t Img_Average(block_t t1, block_t t2){
	t1.x = (t1.x + t2.x)/2;
	t1.y = (t1.y + t2.y)/2;
	t1.width = (t1.width + t2.height)/2;
	t1.height = (t1.height + t2.height)/2;
	return t1;
}

Arm_Ctrl_t getControInfo(){
	Arm_Ctrl_t data;
	return data;
}


void copeBlocks(int blocks){//Main Function
	switch(status){
		case 0://Setup for Fist, LockLoop

		filter_back = ImgFilter(1, blocks, arr);
		if (filter_back == 2){
			/*********************/
			if (arr[0].x > arr[1].x){
					block_t tmp = arr[0]; arr[0] = arr[1]; arr[1] = tmp;
			}
			if (try_times == 0){
				F1 = arr[0];	F2 = arr[1];
			}
			else{
				if (isImageSame(F1, arr[0]) && isImageSame(F2, arr[1])){
					try_times++;
					F1 = Img_Average(F1, arr[0]);
					F2 = Img_Average(F2, arr[1]);
				}
				else
					try_times = 0;
			}

			if (try_times >= 10){
				targetLock = false;
				status = 1;
			}
			/*********************/
		}
		else{
			try_times = 0;
		}
		break;


		case 1://Signature 2 Analysis
			filter_back = ImgFilter(1, blocks, arr);
			if (filter_back > 0){
				if (try_times == 0) target = arr[0];
				else
					if (isImageSame(arr[0], target)) try_times++;
				if (try_times >= 5) {
					targetLock = true;
					status = 2;
				}
			}
		break;

		case 2:
			//(F1.x+F2.x+F1.width/2+F2.width/2)
		break;

		case 3:
		break;

		case 4:
		break;
	}
}
