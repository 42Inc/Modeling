#ifndef EXTRALIB_H
#define EXTRALIB_H

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

#include "../include/extralib.h"

float func(float x);
void methodReject(const char* filename);
void with_repeats(int N, const char * filename);
void no_repeats(int N, const char * filename);

#endif
