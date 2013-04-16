#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char const *argv[])
{
  int i, j;
  float theta = 0.1;
  float r = 0.05;
  float S = 100;
  float E = 102;
  float dt = 0.1;
  int n = 10;

  float T, u, v, p, q;  

  float temp;
  //calculate the parameters
  T = n * dt;
  u = exp((theta * sqrt(dt)));
  v = 1/u;
  p = 0.5 + (((r - (0.5 * pow(theta,2))) * sqrt(dt))/(2 * theta));
  q = 1 - p;

  float stock[n + 1][n + 1], value[n + 1][n + 1], w[n + 1][n + 1];

  // calculate values at expiry 
  for (i = 0; i <= n; i++)
    stock[i][n] = S * (pow(u,(n-(2*i))));

  memset(value, 0, sizeof(value[0][0]) * ((n+1)*(n+1)));
  memset(w, 0, sizeof(w[0][0]) * ((n+1)*(n+1)));

  for(i = 0; i <= n; i++)
    value[i][n] = fmax((stock[i][n] - E), 0);

  for (j = n - 1; j >= 0; j--)
    for (i = 0; i <= j; i++)
      value[i][j] = exp((-1 * r * dt)) * ((p * value[i][j+1]) + (q * value[i+1][j+1]));

  printf("%s\n", "=============V==============");
  for (i = 0; i < n; i++)
  {
    for (j = 0; j <= n; j++){
      // printf("I = %i J= %i \n",i, j);
      printf("| %.2F |", value[i][j]);
    }
    printf("%s\n", "");
  }
  printf("%s\n", "============================");
  printf("FINAL V  %F\n\n", value[0][0]);

  for (i = 0; i <= n; i++)
    stock[i][n] = S * (pow(u,(n-(2*i))));  

  for(i = 0; i < n; i++)
    w[i][n] = fmax((stock[i][n] - E), 0);

  for (j = n - 1; j >= 0; j--)
    for (i = 0; i <= j; i++)
      w[i][j] = (p * w[i][j+1]) + (q * w[i+1][j+1]);

  printf("%s\n", "=============W==============");
  for (i = 0; i < n; i++)
  {
    for (j = 0; j <= n; j++){
      // printf("I = %i J= %i \n",i, j);
      printf("| %.2f |", w[i][j]);
    }
    printf("%s\n", "");
  }    
  printf("%s\n", "============================");
  printf("FINAL W %F\n\n", exp(-1 * r * T) * w[0][0]);

  return 0;
}