#include "main.h"

#define EPS 100
#define FUNCTION(X) X

int numeric_count[EPS + 1][2];
int length = 0;

int getrand(int min, int max)
{
  max *= EPS;
  max += 1;
  min *= EPS;
  return ((int)(rand() / (RAND_MAX + 1.0) * (max - min) + min));
}

int main(int argc, char** argv)
{
  generateCounts(argc > 1 ? atol(argv[1]) : 100000);
  return 0;
}

void generateCounts(long int count)
{
  int iterator = 0;
  int num = 0;
  int i;
  FILE* out_descriptor = fopen("counts.dat", "w");
  out_descriptor = out_descriptor == NULL ? stdout : out_descriptor;
  length = EPS + 1;
  while (iterator++ < count) {
    num = getrand(0, 1);
    if (numeric_count[num][0] == num)
      numeric_count[num][1]++;
    else {
      numeric_count[num][0] = num;
      numeric_count[num][1] = 1;
    }
  }
  for (i = 0; i < length; ++i) {
    fprintf(out_descriptor, "%lf\t%d\n", (((double)numeric_count[i][0]) / EPS), numeric_count[i][1]) ;
  }
}
