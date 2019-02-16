#include "main.h"

int numeric_count[EPS + 1][2];
int length = 0;

int getrand(int min, int max)
{
  max *= EPS;
  max += 1;
  min *= EPS;
  return ((int)(rand() / (RAND_MAX + 1.0) * (max - min) + min));
}

void generateNumbers(long int cnt)
{
  int iterator = 0;
  int num = 0;
  int i;
  FILE* fd_out = fopen("result.dat", "w");
  fd_out = fd_out == NULL ? stdout : fd_out;
  length = EPS + 1;
  while (iterator++ < cnt) {
    num = getrand(0, 1);
    if (numeric_count[num][0] == num)
      numeric_count[num][1]++;
    else {
      numeric_count[num][0] = num;
      numeric_count[num][1] = 1;
    }
  }
  for (i = 0; i < length; ++i) {
    fprintf(fd_out, "%lf\t%d\n", (((double)numeric_count[i][0]) / EPS), numeric_count[i][1]) ;
  }
}

int main(int argc, char** argv)
{
  generateNumbers(argc > 1 ? atol(argv[1]) : 100000);
  return EXIT_SUCCESS;
}
