#include "main.h"

//Gyro stuff
float calculateGyroDrift(){
    float gyrovalue = 0;
    for(int i = 0;i < 10000;i++){
			pros::delay(10);
			gyrovalue += gyro.get_value();
			gyro.reset();
		}
		printf("gyro value: %f \n", gyrovalue);
		float gyrodrift = gyrovalue/1000;
		printf("gyro drift: %f \n", gyrodrift);
    return gyrodrift;
}

float updateGyroValue(float gyrovalue,float gyrodrift){
  gyrovalue += (gyro.get_value()-gyrodrift);
  gyro.reset();
  return gyrovalue;
}

void resetEncoders(){
  driveFront.tare_position();
  driveLeft.tare_position();
  driveBack.tare_position();
  driveRight.tare_position();
  leftEncoder.reset();
  rightEncoder.reset();
}

double avgRotation(){
  double av_encoder = (driveFront.get_position()+driveLeft.get_position()+driveBack.get_position()+driveRight.get_position())/4;
  return av_encoder;
}

double avgEncoderValue(int angle){
  int* axis_arr = designateAxis(angle%180);
  double* scalar = designateScalars(angle);
  double* rel = getRealMovement(); //{x,xy,y,nxy}

  //When cos(theta)/sin(theta) --> 1/0 then the program spazzes so i need to add a switch case
  double av_value = 0;
  for (int i = 0; i < 4; i++){
    if (axis_arr[i] == 1){
      av_value += (rel[i]/scalar[i])/3;//measures vertical movement
      //av_value_x += (rel[(i+2)%4]/scalar_x[i])/3;//measures horiztonal movement
    }
  }
  //printf("av_value_y %f \n",av_value_y);
  //printf("av_value_x %f \n \n",av_value_x);
  return av_value;
}
//Helper functions

double* getRealMovement(){
  double* arr = new double[4];
  arr[0] = -(driveFront.get_position() - driveBack.get_position())/2;//relative X //-
  arr[1] = -leftEncoder.get_value(); //relative xy //+
  arr[2] = +(driveLeft.get_position() - driveRight.get_position())/2;  //y //+
  arr[3] = +rightEncoder.get_value(); //relative nxy (negative xy) //-
  return arr;
}

double* designateScalars(int angle){
  double theta = (angle/(double)360) * (6.283);
  double* arr = new double[4];
  arr[0] = sin(theta);
  arr[1] = cos(theta+.785);
  arr[2] = cos(theta);
  arr[3] = cos(theta-0.785);
  return arr;
}

int* designateAxis(int angle){
  int* arr = new int[4] {1,1,1,1} ;
  //arr[0] = 1;
  //arr[1] = 1;
  //arr[2] = 1;
  //arr[3] = 1;
  if ((0 <= angle && angle < 22.5)||(157.5 <= angle && angle < 180)){
  //rel_x is invalid forward and rel_y is invalid sideways
    arr[0] = 0;
  }
  else if(22.5 <= angle && angle < 67.5) {
  //rel_xy is invalid forward and rel_nxy invalid sideways
    arr[1] = 0;
  }
  else if(67.5 <= angle && angle < 112.5) {
  //rel_y is invalid forward and rel_x is invalid sideways
    arr[2] = 0;
  }
  else if(112.5 <= angle && angle < 157.5) {
  //rel_nxy is invalid forward and rel_xy invalid sideways
    arr[3] = 0;
  }
  return arr;
}
