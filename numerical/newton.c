#include <stdio.h>
#include <math.h>

double newt(double x);

int main(){
  double answer;
  answer = newt(0.1);
  printf("Montly rate: %f\n", answer);
  printf("APR:%f\n", (answer * 1200));
}

double newt(double x){
  //break down fx into sub parts for readability
  double y = pow((1 + x), 360);
  double z = (1 - (100 * x));
  double n = pow((1 + x), 359);
  //calculate fx
  double fx = (y * z) - 1;
  //calculate fpx
  double fpx = (360 * z * n) - (100 * y);
  //newton's method
  double gx = x - (fx/fpx);

  double absolute = (gx - x) < 0 ? 0 - (gx - x) : (gx - x); 

  if (absolute < .00000001)
    return x;
  else
    return newt(gx);
  
}