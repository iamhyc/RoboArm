#include "RoboArm.h"

/***************Servo相关函数*******************/
void Servo_Reset(){
  SERVOR_0.write(90);
  SERVOR_1.write(90);
  delay(400);
}

void Servo_Drive(char servor, char pos){
  switch(servor){
    case 0:SERVOR_0.write(pos);break;
    case 1:SERVOR_1.write(pos);break;
  }
}
/***************Servo相关函数*******************/

/***************直流电机相关*******************/
void DC_Rotate(int data){
  
  switch(data){
    case 0://Backward
    //Serial.println("DC is ROTATING BACKWARD");
    if (DC_STATUS != 0){
      DC_STATUS = 0;
      digitalWrite(E1, HIGH);
      digitalWrite(M1, LOW);
    }
    break;
    case 1://No Reaction
    if (DC_STATUS != 1){
      DC_STATUS = 1;
      digitalWrite(M1, LOW);
      digitalWrite(E1, LOW);
    }
    break;
    case 2://Forward
    //Serial.println("DC is ROTATING FORWARD");
    if (DC_STATUS != 2){
      DC_STATUS = 2;
      digitalWrite(E1, HIGH);
      digitalWrite(M1, HIGH);
    }
    break;
    default:
    break;
  }
  
}

void DC_pwmForward(){
  float diff = read_POS_X - POS_X;
  int pwm = 255*(diff/10);
  if (pwm > 255) pwm = 255;
  digitalWrite(E1, HIGH);
  analogWrite(M1, pwm);
}


void DC_SetPosX(){
  Serial.print(read_POS_X);
  Serial.print("\t");






  
  Serial.println(POS_X);
  if (read_POS_X == 0) return;
  if (read_POS_X - POS_X > SDE){// SDE == 0
    //Serial.println("DC is ROTATING FOREWARD");
    DC_Rotate(0);
    //DC_pwmForward();
  }
  else if (POS_X - read_POS_X> SDE){
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
      if (FT_STATUS != 0){
        FT_STATUS = 0;
        Hold_Tight();
      }
    break;
    case 1://PWDown
      if (FT_STATUS != 1){
        FT_STATUS = 1;
        digitalWrite(E2, LOW);
        digitalWrite(M2, LOW);
      }
    break;
    case 2:
      if (FT_STATUS != 2){
        FT_STATUS = 2;
        Hold_Release();
      }
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
