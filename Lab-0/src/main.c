#include "main.h"

#define EPS 100
#define INTERVALS 10
#define FUNCTION(X) X

int *numeric_count;
int length = 0;
int _count = 0;
int getrand(int min, int max) {
  max *= EPS;
  max += 1;
  min *= EPS;
  return ((int)(rand() / (RAND_MAX + 1.0) * (max - min) + min));
}

double xi_quad() {
  double result;
  double *counts = (double *)malloc((INTERVALS) * sizeof(double));
  double *th_counts = (double *)malloc((INTERVALS) * sizeof(double));
  double probability = 1.0 / INTERVALS;
  int interval = EPS / INTERVALS;
  result = 0;
  memset(counts, 0, sizeof(double) * INTERVALS);
  memset(th_counts, 0, sizeof(double) * INTERVALS);

  for (int position = 0; position < length; ++position) {
    if (numeric_count[position] != -1) {
      counts[(int)((position) / interval)] += numeric_count[position];
      th_counts[(int)(position * probability)]++;
    }
  }

  for (int position = 0; position < INTERVALS; ++position) {
    result += (pow(counts[position] - probability * _count, 2) /
               (probability * _count));
  }
  result = (result);

  return result;
}

void function_autocorrelation() {
  double dispersion;
  double squares_mat_expectation, mat_expectation;
  double autocorrelation;

  mat_expectation = 0.0, squares_mat_expectation = 0.0;
  for (int j = 0; j < length; ++j) {
    if (numeric_count[j] != -1) {
      mat_expectation += (j / EPS)*numeric_count[j];
      squares_mat_expectation += pow(j / EPS, 2)*numeric_count[j];
    }
  }
  mat_expectation = mat_expectation / _count;
  squares_mat_expectation = squares_mat_expectation / _count;
  dispersion = squares_mat_expectation - pow(mat_expectation, 2);

  double average_cor = 0;
  double param1, param2;
  int offset_val = -1;
  for (int offset = 1; offset < 10; ++offset) {
    autocorrelation = 0.0;
    offset_val = -1;
    for (int position = 0; position < length; ++position) {
      if (numeric_count[position] != -1) {
        param1 = (position / EPS - mat_expectation);
        for (int k = position + 1, l = offset; k != position; ++k) {
          if (numeric_count[k % length] != -1) {
            if (--l == 0) {
              offset_val = k;
              break;
            }
          }
        }
        if (offset_val == -1)
          offset_val = 0;
        param2 = (((offset_val) / EPS) - mat_expectation);
        autocorrelation += param1 * param2*numeric_count[position];
      }
    }
    autocorrelation /= (dispersion * _count);
    average_cor += fabs(autocorrelation);
    printf("autocorrelation - %lf\n", fabs(autocorrelation));
  }
  printf("average autocorrelation - %lf\n", average_cor / 10);
}

int main(int argc, char **argv) {
  generateCounts(argc > 1 ? atol(argv[1]) : 100000);
  return 0;
}

void generateCounts(long int count) {
  _count = count;
  int iterator = 0;
  int num = 0;
  int i;
  numeric_count = (int *)malloc((EPS + 1) * sizeof(int));
  FILE *out_descriptor = fopen("counts.dat", "w");
  out_descriptor = out_descriptor == NULL ? stdout : out_descriptor;
  length = EPS + 1;
  srand(time(NULL));
  for (i = 0; i < length; ++i)
    numeric_count[i] = -1;
  while (iterator++ < count) {
    num = getrand(0, 1);
    if (numeric_count[num] == -1)
      numeric_count[num] = 1;
    else
      numeric_count[num]++;
  }
  printf("Xi : %.12lf\n", xi_quad());
  function_autocorrelation();
  for (i = 0; i < length; ++i) {
    fprintf(out_descriptor, "%lf\t%d\n", (((double)i) / EPS), numeric_count[i]);
  }
}
