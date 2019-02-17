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

int numeric_count[EPS + 1];
int length = 0;
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
  double num = 0;
  FILE* out_descriptor = fopen("result.dat", "w");
  out_descriptor = (out_descriptor == NULL) ? stdout : out_descriptor;
  while (iterator++ < count) {
    num = getrand(0, 2*_PI);
    fprintf(out_descriptor, "%lf %lf\n", num / EPS, FUNCTION(num / EPS));
  }
}
