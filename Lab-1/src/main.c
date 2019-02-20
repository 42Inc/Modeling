#include "main.h"

#define EPS 100
#define _PI 3.14

#define FUNCTION(X) \
  (0 <= (X) && (X) < (_PI/2) ? 0 : (\
  (_PI/2) <= (X) && (X) < (_PI) ? cos(X) : (\
  (_PI) <= (X) ? 0 : 0 \
  )\
  )\
  )

long length = 0;
typedef struct result {
  double num;
  long int count;
} result_t;
result_t *numeric_counts;
int getrand(int min, int max) {
  max *= EPS;
  max += 1;
  min *= EPS;
  return ((int)(rand() / (RAND_MAX + 1.0) * (max - min) + min));
}

int main(int argc, char** argv) {
  generateResulst(argc > 1 ? atol(argv[1]) : 100000);
  return 0;
}

void generateResulst(long int count) {
  int iterator = 0;
  int i = 0;
  double num = 0;
  double found = 0;
  FILE* out_descriptor = fopen("results.dat", "w");
  srand(time(NULL));
  out_descriptor = (out_descriptor == NULL) ? stdout : out_descriptor;
  numeric_counts = (result_t*)malloc(++length * sizeof(result_t));
  numeric_counts[length - 1].num = -1;
  numeric_counts[length - 1].count = 0;
  while (iterator++ < count) {
    num = getrand(0, 2*_PI);
    found = 0;
    for (i = 0; i < length; ++i) {
      if (numeric_counts[i].num == FUNCTION(num / EPS)) {
        found = 1;
        numeric_counts[i].count++;
        break;
      }
      if (numeric_counts[i].num == -1) {
        found = 1;
        numeric_counts[i].num = FUNCTION(num / EPS);
        numeric_counts[i].count++;
        break;
      }
    }
    if (!found) {
      numeric_counts = (result_t*)realloc(numeric_counts, ++length * sizeof(result_t));
      numeric_counts[length - 1].num = -1;
      numeric_counts[length - 1].count = 0;
    }
//    fprintf(out_descriptor, "%lf %lf\n", num / EPS, FUNCTION(num / EPS));
  }
  for (i = 0; i < length; ++i) {
    if (numeric_counts[i].num == 0) continue;
    fprintf(out_descriptor, "%lf %ld\n", numeric_counts[i].num, numeric_counts[i].count);
  }
}
