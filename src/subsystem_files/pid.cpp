int getError(int error,int target){
  int sensor_value = 0; //temp until we actually get values
  error = target - sensor_value;
  return error;
}

int getIntergral(int intergral,int error){
  intergral = intergral + error;
  return intergral;
}

int getDerivative(int error, int prev_error){
  int derivite = error - prev_error;
  return derivite;
}
