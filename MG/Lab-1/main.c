#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define EPS 1e+3
#define CNT 100000
#define ln log

const double e = 2.71828182890459027;
/*
 * Task
 * a       | [0; a_x]
 * 4e^(-4x)| (a_x; +inf)
 * a_x можно выразить: Известно, что 4e^(-4a_x) = a
 * Отсюда:
 * a/4 = e^(-4a_x) => ln(a/4) = ln(e^(-4a_x)) => ln(a/4) = -4a_x =>
 * a_x = -ln(a/4)/4
 *
 * Теперь интереснее. Берем интеграл кусочной функции. И находим ФР.
 * (Интеграл как I(a,b)). А ещё смешнее то,
 * что на [0; a_x] равномерное распределение.
 * I(0, x) = a * x                        | [0; a_x]
 * I(a_x, +inf{x}) = e^(-4*a_x) - e^(-4x) | (a_x; +inf)
 *
 * И переходим к магии. Имеем СВ k, равномерно распределенную в [0:1].
 * И приравниваем к нашей функции распределения
 * Получим:
 * a * x = k
 * e^(-4*a_x) - e^(-4x) + a * a_x = k
 * Отсюда выразим x:
 * x = k / a | [0; a_x]
 * x = -ln(a * (a_x + 0.25) - k) / 4 | (a_x; +inf)
 *
 */

const double a = 4;

double f(double x, double a_x) {
  double res = 0.0;
  double r = 0.0;
  double _a_x = -ln(a / 4) / 4;
  if (a_x < 0) {
    // return 1 - pow(e, -4 * (x));
    if (x < _a_x) {
      return a;
    } else {
      return 4 * pow(e, -4 * x);
    }
  }

  a_x = -ln(a / 4) / 4;
  if (x < a * a_x) {
    res = x / a;
  } else {
    r = a_x * a  + a * 0.25 - x;
    if (r < 0) {
      res = -1;
      // res = -ln(-a * 0.25 - a_x * a + x) / 4;
    } else {
      res = -ln(r) / 4;
    }
    // res = x;
  }
  return res;
}

int main(int argc, char** argv) {
  long long int i = 0;
  long long int j = 0;
  double r = 0.0;
  double res = 0.0;
  // srand(time(NULL));
  // a_x = 4 * pow(e, -a);
  // a_x = -ln(a / 4);
  // fprintf(stdout, "+0\t%lf\n", a_x);
  for (i = 0; i < CNT; ++i) {
    r = ((double)rand()) / ((double)RAND_MAX);
    res = f(r, 1);
    fprintf(stdout, "%lf\n", res);
    res = f(r, -1);
    fprintf(stderr, "%lf\t%lf\n", r, res);
  }
  return 0;
}
