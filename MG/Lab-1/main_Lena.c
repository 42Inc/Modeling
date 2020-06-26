#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define EPS 1e+3
#define CNT 1000000
#define ln log

const double e = 2.71828182890459027;
/*
 * Task
 * a       | [0; a_x]
 * 4e^(-x)| (a_x; +inf)
 * a_x можно выразить: Известно, что 4e^(-4a_x) = a
 * Отсюда:
 * a/4 = e^(-a_x) => ln(a/4) = ln(e^(-4a_x)) => ln(a/4) = -4a_x =>
 * a_x = -ln(a/4)
 *
 * Теперь интереснее. Берем интеграл кусочной функции. И находим ФР.
 * (Интеграл как I(a,b)). А ещё смешнее то,
 * что на [0; a_x] равномерное распределение.
 * I(0, x) = a * x                        | [0; a_x]
 * I(a_x, +inf{x}) = -4e^(-x) + 4 * e^(-a_x) + a * a_x | (a_x; +inf)
 *                   -4e^(-x) + a + a * a_x
 * И переходим к магии. Имеем СВ k, равномерно распределенную в [0:1].
 * И приравниваем к нашей функции распределения
 * Получим:
 * a * x = k
 * a - 4e^(-x) = k
 * Отсюда выразим x:
 * x = k / a | [0; a*a_x]
 * x = -ln((a - k) / 4) | (a*a_x; +inf)
 *
 */

double a = 0;

double f(double x, double a_x) {
  double res = 0.0;
  double r = 0.0;
  double _a_x = -ln(a / 4);
  if (a_x < 0) {
    if (x < _a_x) {
      return a;
    } else {
      return 4 * pow(e, -x);
    }
  }

  a_x = -ln(a / 4);
  if (x < a * a_x) {
    res = x / a;
  } else {
    r = (a - x + a * a_x) / 4;
    if (r < 0) {
      res = -1;
    } else {
      res = -ln(r);
    }
  }
  return res;
}

int main(int argc, char** argv) {
  long long int i = 0;
  long long int j = 0;
  double k = 0;
  double r = 0.0;
  double res = 0.0;

  double a_x = 0;
  double amin = 0;
  double amax = 4;
  double eps = 1E-6;
  double epsc = 0;
  while (1) {
    epsc = a - a * ln(a / 4) - 1;
    if (fabs(epsc) < eps) break;
    if (epsc > 0) {
      amax = a;
      a = (amax - amin) / 2 + amin;
    } else {
      amin = a;
      a = (amax - amin) / 2 + amin;
    }
  }

  fprintf(stdout, "-1\t%lf\t%lf\n", a, -ln(a/4));
  for (i = 0; i < CNT; ++i) {
    r = ((double)rand()) / ((double)RAND_MAX);
    res = f(r, 1);
    fprintf(stdout, "%lf\n", res);
    }

    for (k = 0; k < 10; k+=0.01) {
      res = f(k, -1);
      fprintf(stderr, "%lf\t%lf\n", k, res);
    }
  return 0;
}
