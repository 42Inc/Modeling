#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EPS 1e+3
#define CNT 1e+5
#define MIN 0
#define MAX 1
#define ln log

/* Задаем моделируемое распределение. ВАЖНО - это плотность распределения */
const double f_distribution[] = {0.01,  0.02, 0.03,  0.03, 0.04,
                                 0.045, 0.05, 0.085, 0.16, 0.53};
const double F_distribution[] = {0,     0.01,  0.03, 0.06, 0.09, 0.13,
                                 0.175, 0.225, 0.31, 0.47, 1};
const int N_f = sizeof(f_distribution) / sizeof(*f_distribution);
const int N_F = sizeof(F_distribution) / sizeof(*F_distribution);
/*
 * Функция распределения же выглядит сл. образом:
 *  0      1     2       3    4      5      6      7    8     9
 * 0.01,  0.03, 0.06,  0.09, 0.13, 0.175, 0.225, 0.31, 0.47, 1
 * Для генерации будем использовать немного измененную
 * 0, 0.01,  0.03, 0.06,  0.09, 0.13, 0.175, 0.225, 0.31, 0.47, 1
 */

/* С возвратом */
int with_returns() {
  int i = 0;
  int j = 0;
  double r = 0.0;

  for (i = 0; i < CNT; ++i) {
    r = (double)(rand()) / RAND_MAX;
    for (j = 1; j < N_F; ++j) {
      if (r < F_distribution[j]) {
        fprintf(stdout, "%d\n", j - 1);
        break;
      }
    }
  }
  return 0;
}
double get_max(double* f, int n) {
  double max = -1;
  int i = 0;
  for (i = 0; i < n; ++i) {
    if (max < f[i]) max = f[i];
  }
}

/* Без возврата */
int without_returns(int pack) {
  int i = 0;
  int j = 0;
  int k = 0;
  int t_r = 0;
  int t_g = 0;
  int* used_indexes = NULL;
  int pack_reject = pack * 0.5;
  int pack_gen = pack - pack_reject;
  double r = 0.0;
  double cursor = 0.0;
  double tmp = 0.0;
  used_indexes = (int*)calloc(N_F, sizeof(int));

  for (k = 0; k < CNT; k += pack_gen) {
    memset(used_indexes, 0, N_F * sizeof(int));
    t_r = 0;
    t_g = 0;
    for (i = 0; i < pack; ++i) {
      r = (double)(rand()) / RAND_MAX;
      for (j = 1; j < N_F; ++j) {
        if (t_r < pack_reject) {
          if (r < F_distribution[j]) {
            // used_indexes[j] = 1;
            ++t_r;
          }
          continue;
        } else {
          if (t_g < pack_gen) {
            if (r < F_distribution[j] && !used_indexes[j]) {
              fprintf(stdout, "%d\n", j - 1);
              ++t_g;
            }
          }
        }
      }
    }
  }
  free(used_indexes);
  return 0;
}

int main(int argc, char** argv) {
  int i = 0;
  for (i = 0; i < N_f; ++i) {
    fprintf(stderr, "%d\t%lf\n", i, f_distribution[i]);
    // fprintf(stdout, "%d\t%lf\n", i + 1, f_distribution[i]);
  }
  // with_returns();
  without_returns(10);
  return 0;
}