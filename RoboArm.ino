#define MOTOR_IN   A1
#define MOVECMD_IN A3
#define FIST_IN    A5
#define AUTO_SW A0

#include <JY901.h>

const int M1 = 6;  const int E1 = 7;//MOTOR
const int M2 = 4;  const int E2 = 5;//FLAW

const int SDE = 3; //Standard Derivation ERROR

/*DC Motor*/
int POS_X;
int DC_POS = 0;
/*DC Motor*/

/*Fist*/
bool LAST_FIST_FLAG = true;
bool FIST_FLAG = true;
/*Fist*/

/*SERVO Configuration*/
#include <Servo.h> 
Servo SERVO1;
int SERVO_POS = 0;
bool LAST_SERVO1_FLAG = true;
bool SERVO1_FLAG = true;
/*SERVO Configuration*/


/**************状态分段***************/
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
  else if (data >= 1400 && data <= 1600)
    return 1;
  else if (data >1600)
    return 2;
  else return 0;
}
/**************状态分段***************/


/***************Servo相关函数*******************/
void Servo_Reset(){
  SERVO1.write(0);
  delay(1000);
}

void Servo1_Drive(int data){
  switch(data){
    case 0://PWDown
    LAST_SERVO1_FLAG = true;
    return;
    break;
    case 2:
    if (LAST_SERVO1_FLAG){
      LAST_SERVO1_FLAG = false;
      SERVO1_FLAG = !SERVO1_FLAG;
    }
    
    if (SERVO1_FLAG)
      SERVO1.write(++SERVO_POS);
    else
      SERVO1.write(--SERVO_POS);
    break;
    default:
    break;
  }
}
/***************Servo相关函数*******************/

/***************直流电机相关*******************/
void DC_Rotate(int data){
  
  switch(data){
    case 0://Backward
    //Serial.println("DC is ROTATING BACKWARD");
    digitalWrite(E1, HIGH);
    digitalWrite(M1, LOW);
    break;
    case 1://No Reaction
    digitalWrite(M1, LOW);
    digitalWrite(E1, LOW);
    break;
    case 2://Forward
    //Serial.println("DC is ROTATING FORWARD");
    digitalWrite(E1, HIGH);
    digitalWrite(M1, HIGH);
    break;
    default:
    break;
  }
  
}



void DC_SetPos(){
  //Serial.print(POS_X);
  //Serial.print("\t");
  //Serial.println(DC_POS);
  if (POS_X - DC_POS > SDE){// SDE == 0
    //Serial.println("DC is ROTATING FOREWARD");
    DC_Rotate(0);
  }
  if (DC_POS - POS_X> SDE){
    //Serial.println("DC is ROTATING BACKWARD");
    DC_Rotate(2);
  }
}

/***************直流电机相关*******************/

/***************爪子相关*******************/
void Fist_StatusChange(int data){
    switch(data){
    case 0:
      Hold_Tight();
    break;
    case 1://PWDown
      digitalWrite(E2, LOW);
      digitalWrite(M2, LOW);
    break;
    case 2:
      Hold_Release();
    break;
    default:
    break;
  }
}

void Hold_Tight(){
  digitalWrite(E2, HIGH);
  digitalWrite(M2, LOW);
}

void Hold_Release(){
  digitalWrite(E2, HIGH);
  digitalWrite(M2, HIGH);
}
/***************爪子相关*******************/

/***************Pixy Moudle****************/
#include <SPI.h>  
#include <Pixy.h>
Pixy pixy;

typedef{
  
}

static int ImgCount = 0;

void readPixy(){
  uint16_t blocks;
  
  blocks = pixy.getBlocks();
  if (blocks){
    ImgCount ++;
 
    if (ImgCount % 50 == 0){
      imgCount = 0;
      for (int i = 0; i<blocks; i++){
        pixy.blocks[i].print();
        //sig: 1 x: 159 y: 109 width: 61 height: 61
        //pixy.blocks[i].signature, pixy.blocks[i].x, pixy.blocks[i].y, pixy.blocks[i].width, pixy.blocks[i].height
      }
    }

  }
}
/***************Pixy Module****************/

/***************信号控制*******************/
void readControl(){
  
  if (_digiSwitch(pulseIn(AUTO_SW, HIGH)) == 0){
    int motor_data = _analogSwitch(pulseIn(MOTOR_IN, HIGH));  
    //int servo1_data = _digiSwitch(pulseIn(SERVO1_IN, HIGH));
    int fist_data = _digiSwitch(pulseIn(FIST_IN, HIGH));

    //Serial.print(motor_data);
    //Serial.print("\t");
    //Serial.print(servo1_data);
    //Serial.print("\t");
    //Serial.println(fist_data);
  
    DC_Rotate(motor_data);
    //Servo1_Drive(servo1_data);
    Fist_StatusChange(fist_data);
  }
  else{
    int val = pulseIn(MOTOR_IN, HIGH);
    DC_POS = map(val, 990, 2020, 0, 90);
    //Serial.print("1pos: "+ DC_POS);
    //int servo1_data = _digiSwitch(pulseIn(SERVO1_IN, HIGH));
    int fist_data = _digiSwitch(pulseIn(FIST_IN, HIGH));
    int move_cmd = _digiSwitch(pulseIn(MOVECMD_IN, HIGH));

    if (1){
      DC_SetPos();
    }
    //Servo1_Drive(servo1_data);
    Fist_StatusChange(fist_data);
  }
}

void serialEvent(){
  while(Serial1.available()){
    JY901.CopeSerialData(Serial1.read());
  }
}
/***************信号控制*******************/

void setup() {
  pinMode(E1, OUTPUT);  pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT);  pinMode(M2, OUTPUT);

  Serial.begin(9600);
  Serial1.begin(9600);
  //SERVO1.attach(SERVO1_OUT);
  //Servo_Reset();
  Hold_Tight();
  delay(500);
}

void loop() {
  POS_X = (int)((float)JY901.stcAngle.Angle[0]/32768*180);
  readPixy();
  readControl();
}
