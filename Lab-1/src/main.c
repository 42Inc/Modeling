#include "main.h"

#define EPS 100
#define _PI 3.14f
#define INF -999.9
double a = INF;
#define LEFT -_PI
#define RIGHT _PI
#define COUNT 3

double function(double x) {
  return cos(x);
}

double retnull(double x) {
  return 0.0;
}
typedef struct table {
  double left;
  int leftassign;
  int leftunknown;
  double right;
  int rightassign;
  int rightunknown;
  double (*functor)(double);
} table_t;

long length = 0;
typedef struct result {
  double num;
  double val;
  long int count;
} result_t;

result_t *numeric_counts;
table_t tablef[COUNT] = {
  {0,1,0,_PI/2,0,0,retnull},
  {_PI/2,1,0,_PI,0,0,function},
  {_PI,1,0,100,0,0,retnull},
};


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

void integration() {

}

void generateResulst(long int count) {
  int iterator = 0;
  int i = 0;
  int j = 0;
  double num = 0;
  double found = 0;
  FILE* out_descriptor = fopen("results.dat", "w");
  srand(time(NULL));
  out_descriptor = (out_descriptor == NULL) ? stdout : out_descriptor;
  numeric_counts = (result_t*)malloc(++length * sizeof(result_t));
  numeric_counts[length - 1].num = -1;
  numeric_counts[length - 1].val = 0;
  while (iterator++ < count) {
    num = getrand(0, 2*_PI);
    num = num / EPS;
    found = 0;
    for (i = 0; i < length; ++i) {
      if (numeric_counts[i].num == num) {
        found = 1;
        for (j = 0; j < COUNT; ++j) {
          if (tablef[j].leftassign == 1 && num >= tablef[j].left || num > tablef[j].left) {
              if (tablef[j].rightassign == 1 && num <= tablef[j].right || num < tablef[j].right) {
                numeric_counts[i].val = tablef[j].functor(num);
              }
          }
        }
        break;
      }
      if (numeric_counts[i].num == -1) {
        found = 1;
        for (j = 0; j < COUNT; ++j) {
          if (tablef[j].leftassign == 1 && num >= tablef[j].left || num > tablef[j].left) {
              if (tablef[j].rightassign == 1 && num <= tablef[j].right || num < tablef[j].right) {
                numeric_counts[i].val = tablef[j].functor(num);
              }
          }
        }
        numeric_counts[i].num = num;
        break;
      }
    }
    if (!found) {
      numeric_counts = (result_t*)realloc(numeric_counts, ++length * sizeof(result_t));
      numeric_counts[length - 1].num = num;
      for (j = 0; j < COUNT; ++j) {
        if (tablef[j].leftassign == 1 && num >= tablef[j].left || num > tablef[j].left) {
            if (tablef[j].rightassign == 1 && num <= tablef[j].right || num < tablef[j].right) {
              numeric_counts[length - 1].val = tablef[j].functor(num);
            }
        }
      }
      numeric_counts[length - 1].count = 0;
    }
//    fprintf(out_descriptor, "%lf %lf\n", num / EPS, FUNCTION(num / EPS));
  }
  for (i = 0; i < length; ++i) {
    if (numeric_counts[i].num == 0) continue;
    fprintf(out_descriptor, "%lf %lf\n", numeric_counts[i].num, numeric_counts[i].val);
  }
}
