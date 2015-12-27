#include "PixyModule.h"
#include "Cart.h"
#include "RoboArm.h"
#include <Servo.h>
#include <JY901.h>
#include <Wire.h>

/********************DATA AREA**********************/
const int M1 = 6;  const int E1 = 7;//MOTOR
const int M2 = 4;  const int E2 = 5;//FLAW

const float SDE = 1; //Standard Derivation ERROR

/******POS STATUS******/
static int POS_X = 0;//DC Motor POS
static int X_times = 0;
static int X_avg[10] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};

static int POS_Y = 0;//Servo_1 POS
static int Y_times = 0;
static int Y_avg[10] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};

static int POS_Z = 0;//Servo_0 POS
static int Z_times = 0;
static int Z_avg[10] = {1500,1500,1500,1500,1500,1500,1500,1500,1500,1500};
/******POS STATUS******/

/*******DC Motor*******/
static float read_POS_X = 0;
static int DC_STATUS = 1;
static int FT_STATUS = 1;
/*******DC Motor*******/


/*SERVO Configuration*/
Servo SERVOR_0;
const static int SERVOR_0_OUT = 9;//POS_Z

Servo SERVOR_1;
const static int SERVOR_1_OUT = 10;//POS_Y
/*SERVO Configuration*/

/********************DATA AREA**********************/


/**************状态分段***************/
int sum10(int *arr){
  int tmp = 0;
  for (int i = 0; i < 10; i++)
    tmp += arr[i];
  return tmp/10;
}

int _pulseIn(int PIN){
  return pulseIn(PIN, HIGH, 35000);
}

int _digiSwitch(int data){
  //950-970, 1490-1510, 2030-2050
  if (data >= 900 && data <= 1000)
    return 0;
  else if (data >= 1400 && data <= 1600)
    return 1;
  else if (data >= 2000 && data <= 2100)
    return 2;
  else return 0;
}

int _analogSwitch(int data){
  if (data < 1400)
    return 0;
  else if (data >= 1400 && data <= 1500)
    return 1;
  else if (data >1600)
    return 2;
  else return 0;
}
/**************状态分段***************/


/***************信号控制*******************/
void readControl(){
  int ctrl_sig = _digiSwitch(_pulseIn(AUTO_SW));

  Serial.println(ctrl_sig);
  
  switch(ctrl_sig){
    //case 0://自动模式
      //Arm_Ctrl_t data = getControInfo();
      MotorControl();
      //POS_X = data.DC_DATA;
      //if (_digiSwitch(_pulseIn(MOVECMD_IN)) == 1){
      //DC_SetPosX();
      //Servo_Drive(0, data.SERVO_DATA);
      //Fist_StatusChange(data.FIST_DATA);
    //break;
    
    //case 2:
      //MotorControl();
    //break;
    case 0:
    case 2:
    case 1:
    //手动模式
      {
        X_times = (X_times+1)%10;
        X_avg[X_times] = _pulseIn(MOTOR_IN);
        POS_X = map(sum10(X_avg), 990, 2020, -30, 30);
      }
      {
        Y_times = (Y_times+1)%10;
        Y_avg[Y_times] = _pulseIn(SERVOR_1_IN);
        POS_Y = map(sum10(Y_avg), 990, 2020, 0, 180);
      }
      {
        Z_times = (Z_times+1)%10;
        Z_avg[Z_times] = _pulseIn(SERVOR_0_IN);
        POS_Z = map(sum10(Z_avg), 990, 2020, 0, 180);
      }

      int fist_data = _digiSwitch(_pulseIn(FIST_IN));
      int move_cmd = _digiSwitch(_pulseIn(MOVECMD_IN));
      
      //if (_digiSwitch(_pulseIn(MOVECMD_IN)) == 1){
      Serial.println("hehe");
      DC_SetPosX();
      Servo_Drive(1, POS_Y);
      Servo_Drive(0, POS_Z);
      Fist_StatusChange(fist_data);
    break;
  }
}
/***************信号控制*******************/

/***************Pixy Moudle****************/
#include <SPI.h>
#include <Pixy.h>
Pixy pixy;

static int ImgCount = 0;

void readPixy(){
  uint16_t blocks;
  
  blocks = pixy.getBlocks();
  if (blocks)
  {
      ImgCount ++;

      if (ImgCount % 50 == 0){
        ImgCount = 0;
        copeBlocks(blocks);
        /*for (int i = 0; i<blocks; i++){
          pixy.blocks[i].print();
          //sig: 1 x: 159 y: 109 width: 61 height: 61
          //pixy.blocks[i].signature, pixy.blocks[i].x, pixy.blocks[i].y, 
          //pixy.blocks[i].width, pixy.blocks[i].height
        }*/
      }
  }
}

int ImgFilter(int sig, int blocks, block_t *arr){
  int len = 10;
  int count = 0;
  arr = (block_t *)malloc(len * sizeof(block_t));
  block_t *pt = arr;

  for (int i = 0; i < blocks; i++){
    if (sig == pixy.blocks[i].signature){
      if (pt == arr + len * sizeof(block_t)){
        arr = (block_t *)realloc(arr, (len+10) * sizeof(block_t));
        pt = arr + len * sizeof(block_t);
        len += 10;
      }
      block_t tmp = {pixy.blocks[i].x, pixy.blocks[i].y, pixy.blocks[i].width, pixy.blocks[i].height};
      *pt = tmp;
      pt++;count++;
    }
  }
  return count;
}
/***************Pixy Module****************/


void serialEvent(){
  while(Serial.available()){
    JY901.CopeSerialData(Serial.read());
  }
}

void setup() {
  pinMode(E1, OUTPUT);  pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT);  pinMode(M2, OUTPUT);
  
  SERVOR_0.attach(SERVOR_0_OUT);
  SERVOR_1.attach(SERVOR_1_OUT);
  Serial.begin(9600);

  pinMode(13, OUTPUT);

  Serial.println("HEHEHE");
  
  Servo_Reset();
  Fist_StatusChange(2);
  delay(800);
  Fist_StatusChange(1);
}

void loop() {
  read_POS_X = ((float)JY901.stcAngle.Angle[0]/32768*180);
  readPixy();
  Serial.println("HAHA");
  readControl();
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
}


/*Abandoned Code

int motor_data = _analogSwitch(_pulseIn(MOTOR_IN));
    int servo_data = _pulseIn(SERVO_IN);
        servo_data = map(servo_data, 990, 2020, 0, 180);
    int fist_data = _digiSwitch(_pulseIn(FIST_IN));
  
    DC_Rotate(motor_data);
    Servo_Drive(servo_data);
    Fist_StatusChange(fist_data);

*/
