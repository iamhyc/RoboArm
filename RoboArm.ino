#define   AUTO_SW     A0
#define   MOTOR_IN    A1
#define   MOVECMD_IN  A2
#define   SERVO_IN    A3
#define   FIST_IN     A5

#include <JY901.h>
#include <Wire.h>

const int M1 = 6;  const int E1 = 7;//MOTOR
const int M2 = 4;  const int E2 = 5;//FLAW

const int SDE = 1; //Standard Derivation ERROR

/*DC Motor*/
static int POS_X = 0;
static int DC_POS = 0;
/*DC Motor*/

/*Fist*/
bool LAST_FIST_FLAG = true;
bool FIST_FLAG = true;
/*Fist*/

/*SERVO Configuration*/
#include <Servo.h>
const int SERVOR_OUT = 9;
Servo SERVOR;
/*SERVO Configuration*/


/**************状态分段***************/
int _pulseIn(int PIN){
  return pulseIn(PIN, HIGH, 30000);
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
  else if (data >= 1400 && data <= 1600)
    return 1;
  else if (data >1600)
    return 2;
  else return 0;
}
/**************状态分段***************/


/***************Servo相关函数*******************/
void Servo_Reset(){
  SERVOR.write(0);
  delay(200);
}

void Servo_Drive(char pos){
  SERVOR.write(pos);
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
  Serial.print(POS_X);
  Serial.print("\t");
  Serial.println(DC_POS);
  if (POS_X - DC_POS > SDE){// SDE == 0
    //Serial.println("DC is ROTATING FOREWARD");
    DC_Rotate(0);
  }
  else if (DC_POS - POS_X> SDE){
    //Serial.println("DC is ROTATING BACKWARD");
    DC_Rotate(2);
  }
  else {
    DC_Rotate(1);
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

static int ImgCount = 0;

void readPixy(){
  uint16_t blocks;
  
  blocks = pixy.getBlocks();
  if (blocks){
    ImgCount ++;
 
    if (ImgCount % 50 == 0){
      ImgCount = 0;
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
  if (_digiSwitch(_pulseIn(AUTO_SW)) != 2){//手动模式
    int motor_data = _analogSwitch(_pulseIn(MOTOR_IN));
    int servo_data = _pulseIn(SERVO_IN);
        servo_data = map(servo_data, 990, 2020, 0, 180);
    int fist_data = _digiSwitch(_pulseIn(FIST_IN));
  
    DC_Rotate(motor_data);
    Servo_Drive(servo_data);
    Fist_StatusChange(fist_data);
  }
  else{//自动模式
    int val = _pulseIn(MOTOR_IN);
        DC_POS = map(val, 990, 2020, -30, 30);
    int servo_data = _pulseIn(SERVO_IN);
        servo_data = map(servo_data, 990, 2020, 0, 180);

    int fist_data = _digiSwitch(_pulseIn(FIST_IN));
    int move_cmd = _digiSwitch(_pulseIn(MOVECMD_IN));

    //if (_digiSwitch(_pulseIn(MOVECMD_IN)) == 1){
    if (1){
        DC_SetPos();
    }

    Servo_Drive(servo_data);
    Fist_StatusChange(fist_data);
  }
}

void serialEvent(){
  while(Serial.available()){
    JY901.CopeSerialData(Serial.read());
  }
}
/***************信号控制*******************/

void setup() {
  pinMode(E1, OUTPUT);  pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT);  pinMode(M2, OUTPUT);
  Serial.begin(9600);
  SERVOR.attach(SERVOR_OUT);
  
  Servo_Reset();
  Hold_Tight();
  delay(300);
}

void loop() {
  POS_X = (int)((float)JY901.stcAngle.Angle[0]/32768*180);
  readPixy();
  readControl();
}
