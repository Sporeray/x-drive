#include "main.h"

//MOTORS

pros::Motor driveFront(2,pros::E_MOTOR_GEARSET_18,false,pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveLeft(3,pros::E_MOTOR_GEARSET_18,false,pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveBack(4,pros::E_MOTOR_GEARSET_18,false,pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor driveRight(1,pros::E_MOTOR_GEARSET_18,false,pros::E_MOTOR_ENCODER_DEGREES);

//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//Sensors
pros::ADIGyro gyro('B', 0.972); //Gyro Scale
pros::ADIEncoder leftEncoder('G','H');
pros::ADIEncoder rightEncoder('F','E');
