#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CNT 1000000

double func(double x, double k) {
  double res = 0.0;
  if (k < 0) {
    if (x >= 0 && x <= 4) {
      return 0.25;
    } else {
      return 0;
    }
  }

  if (x >= 0 && x <= 4) {
    res = x * 4;
  }
  return res;
}

int main(int argc, char** argv) {
  long long int i = 0;
  long long int j = 0;
  double k = 0;
  double r = 0.0;
  double res = 0.0;

  for (i = 0; i < CNT; ++i) {
    r = ((double)rand()) / ((double)RAND_MAX);
    res = func(r, 1);
    fprintf(stdout, "%lf\n", res);
  }

    for (k = 0; k < 5; k+=0.01) {
      res = func(k, -1);
      fprintf(stderr, "%lf\t%lf\n", k, res);
    }
  return 0;
}
