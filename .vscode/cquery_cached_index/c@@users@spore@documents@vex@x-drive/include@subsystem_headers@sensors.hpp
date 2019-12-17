#include "main.h"

float calculateGyroDrift();

float updateGyroValue(float gyrovalue,float gyrodrift);

double avgEncoderValue(int angle);

void resetEncoders();

double avgRotation();

//Helper functions
double* getRealMovement();

double* designateScalars(int angle);

int* designateAxis(int angle);
