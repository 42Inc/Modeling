#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cmath>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>

#include "../include/extralib.h"

#define MAX 100000
#define a_ -0.5379

using namespace std;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
	char* s[3] = {"./result/repeats.dat", "./result/no_repeats.dat", "./result/reject.dat"};

	with_repeats(10, s[0]);
	no_repeats(10, s[1]);
  methodReject(s[2]);

	return EXIT_SUCCESS;
}
