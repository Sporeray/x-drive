#include "main.h"

void updatePIDValues(double* arr,int target,double encoder){
  double old_error = arr[0];
  arr[0] = target - arr[3];	   //Error
  arr[1] = arr[1] + arr[0];    //Intergral
  arr[2] = arr[0] - old_error; //derivative
  arr[3] = arr[3] + encoder;   //Sensor Value
}

//Auton
void move(double y_units,double x_units,double rot_units,double angle){
  double y_k[3] = {0,0,0};//{1,0,7}; //{kP,kI,kD}
  double x_k[3] = {0,0,0}; //{kP,kI,kD}
  double rot_k[3] = {0.5,0,0}; //{kP,kI,kD}
  double y[4] = {0,0,0,0}; //{error,intergral,derivative,sensor}
  double x[4] = {0,0,0,0}; //{error,intergral,derivative,sensor}
  double rot[4] = {0,0,0,0};//{error,intergral,derivative,sensor}
  while (true){
    updatePIDValues(y,y_units,avgEncoderValue(angle));
    updatePIDValues(x,x_units,avgEncoderValue(angle+270));
    updatePIDValues(rot,rot_units,avgRotation());
    resetEncoders();
    double y_input = y[0]*y_k[0]+y[1]*y_k[1]+y[2]*y_k[2];
    double x_input = x[0]*x_k[0]+x[1]*x_k[1]+x[2]*x_k[2];
    double rot_input = rot[0]*rot_k[0]+rot[1]*rot_k[1]+rot[2]*rot_k[2];
    setDrive(y_input,x_input,rot_input,0);
    pros::delay(10);
    printf("Sensor %f \n",y[0]);
    printf("Error %f \n",y[1]);
    printf("Intergral %f \n",y[2]);
    printf("Derivative %f \n",y[3]);
    printf("\n");
  }
}

//Helper
/*
double getAngle(int x,int y){
  double xy = x*y;
  double sub_angle = 0;
  if(xy < 0){
    sub_angle = atan(x/y);
  }else if(xy == 0){

  }else{
    sub_angle = atan(y/x);
  }
}
*/
