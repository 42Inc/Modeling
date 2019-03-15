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
#define pi 3.14
using namespace std;

#include "../include/extralib.h"

float methodReject();
double func(double x);
void _methodRej(int n, int m, const char *filename);
void dist_with_repetition(int n, int nexp, string& filename);
void dist_wo_repetition(int n, int nexp, string& filename);

#endif
