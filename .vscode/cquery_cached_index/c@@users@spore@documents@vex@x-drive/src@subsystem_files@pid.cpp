#include "main.h"

void getPIDValues(double* arr,double encoder){
  arr[0] = encoder-arr[1]; //D
  arr[1] = encoder;			   //V
  arr[2] = arr[2]+encoder; //I
}
