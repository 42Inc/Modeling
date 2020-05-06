#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EPS 1e+3
#define CNT 1e+5
#define MIN 0
#define MAX 1
#define ln log

const double e = 2.71828182890459027;
const double a = 1.0;
/*
 * Task
 * a      | [0; a_x]
 * 4e^(-4x)| (a_x; +inf)
 * a_x можно выразить: Известно, что 4e^(-4a_x) = a
 * Отсюда:
 * a/4 = e^(-4a_x) => ln(a/4) = ln(e^(-4a_x)) => ln(a/4) = -4a_x =>
 * a_x = -ln(a/4)/4
 *
 * Теперь интереснее. Берем интеграл кусочной функции.
 * (Интеграл как I(a,b))
 * I(0, a_x) = a * x         | [0; a_x]
 * I(a_x, +inf{x}) = e^(-4a_x) - e^(-4x)  + a * a_x  | (a_x; +inf)
 *
 * I(a_x, +inf{x}) = a/4 - e^(-4x)  + a * a_x
 * a * (a_x + 0.25) - e^(-4x)
 *
 * И переходим к магии. Имеем СВ k, равномерно распределенную в [0:1].
 * И приравниваем к нашей функции распределения
 * Получим:
 * a * (a_x + 0.25) - e^(-4x) = k
 * Отсюда выразим x
 * e^(-4x) = a * (a_x + 0.25) - k
 * -4x = ln(a * (a_x + 0.25) - k)
 * x = -ln(a * (a_x + 0.25) - k)/4
 *
 * x = a * x         | [0; a_x]
 * x = -ln(a * (a_x + 0.25) - k)/4 | [a_x; +inf)
 *
 * И еще магии:
 * Функция случайной величины k имеет такое же распределение, что и сама
 * случайная величина k (Насколько помню)
 */

double f(double x, double a_x) {
  double res = 0.0;
  if (a_x < 0) {
    if (x <= -ln(a / 4) / 4) {
      return a;
    } else {
      return 4 * pow(e, -4 * x);
    }  // return 4 - 4 * pow(e, -x);
  }
  if (x < 0) {
    return 0;
  } else if (x < a_x) {
    return x / a;
  } else {
    // res = a * (a_x + 0.25) - pow(e, -4 * x);
    res = -ln(a * (a_x + 0.25) - x) / 4;
    // res = -ln(x) / 4;
    // res = -ln((a * (a_x + 1) - x) / 4);
    // res = -ln(x / 4);
    return res;
  }
}

int main(int argc, char** argv) {
  long long int i = 0;
  long long int j = 0;
  long long int count = 0;
  int min = MIN * EPS;
  int max = MAX * EPS;
  double r = 0.0;
  double res = 0.0;
  double a_x = 0.0;
  double* array = (double*)calloc(CNT, sizeof(double));
  srand(time(NULL));
  // a_x = 4 * pow(e, -a);
  a_x = -ln(a / 4) / 4;
  // a_x = -ln(a / 4);
  // fprintf(stdout, "+0\t%lf\n", a_x);
  for (i = 0; i < CNT; ++i) {
    r = ((double)rand()) / RAND_MAX;
    // r = r / EPS;
    res = ((int)(f(r, a_x) * EPS)) / EPS;
    // index = (int)(res * EPS);
    // printf("%d\n", index);
    // array[i] = res;
    fprintf(stdout, "%ld\t%lf\n", i, res);
    // ++array[index];
    // fprintf(stderr, "%lld\n", i);
    fprintf(stderr, "%lf\t%lf\n", r, f(r, -1));
  }

  free(array);
  return 0;
}
