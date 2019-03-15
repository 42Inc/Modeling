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
#define pi 3.14
using namespace std;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
	string s[3] = {"./result/A.dat", "./result/A_.dat", "./result/rej.dat"};

	dist_wo_repetition(10, 10000, s[1]);
	dist_with_repetition(10, 10000, s[0]);
	_methodRej(40, 100000, s[2].c_str());

	return EXIT_SUCCESS;
}
