#include "main.h"



//helper functions
void setDrive(int chy, int chx,int anglular,double angle) { //Channel X and Channel Y
  double theta = ConvertRads(angle);

  driveFront = (cos(theta)*chx-sin(theta)*chy)+anglular;
  driveLeft = (cos(theta)*chy+sin(theta)*chx)+anglular;
  driveBack = -(cos(theta)*chx-sin(theta)*chy)+anglular;
  driveRight = -(cos(theta)*chy+sin(theta)*chx)+anglular;
}

//Driver control
void setDriveMotors(double angle){
  int l_vertical_stick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int l_horizontal_stick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  int r_horizontal_stick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  if (((abs(l_vertical_stick) > 10)||(abs(l_horizontal_stick)>10))|| abs(r_horizontal_stick)>10){
    setDrive(l_vertical_stick,l_horizontal_stick,r_horizontal_stick,angle);
  }
  else {
    setDrive(0,0,0,angle);
  }
}
