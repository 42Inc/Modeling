#include "../include/extralib.h"


double func(double x) {
  double a = 0.125;
  double y = 0.0;
  if ((x > -4) && (x <= 5))
    y = sqrt(x + 4) * a;
  return y;
}

/*	Метод отбраковки	*/
float methodReject() {
	float a = 0, b = pi, c = 1, x1, x2;
	do {
		x1 = (float) rand() / RAND_MAX;
		x2 = (float) rand() / RAND_MAX;
	} while (func(a + (b - a) * x1) < c * x2);

	return a + (b - a) * x1;
}

/*	Распределение без повторений */
void dist_wo_repetition(int n, int nexp, string& filename) {
	vector<int> nums, temp;
	int it, k = 3 * n / 4, mas[n], part = nexp / k + 1;
	float p;

	memset(mas, 0, sizeof(int) * n);
	for(int i = 0; i < n; i++)
		temp.push_back(i);
	for(int j = 0; j < part; j++) {
		nums = temp;
		if (j == part - 1) k = nexp % k;
		for(int i = 0; i < k; i++) {
			p = 1.0 / (n - i);
			it = (float) rand() / RAND_MAX / p;
			++mas[nums[it]];
			nums.erase(nums.begin() + it);
		}
	}

	FILE *fd_out = fopen(filename.c_str(), "w");
  if (fd_out) {
    for(int i = 0; i < n; i++)
      fprintf(fd_out, "%d\t%.4f\n", i, (float) mas[i] / nexp);
    fclose(fd_out);
  }
}

/*	Распределение с повторением */
void dist_with_repetition(int n, int nexp, string& filename) {
	float p = 1, intervals[n], x, sum;
	int mas[n];

	memset(mas, 0, sizeof(int) * n);
	for(int i = 0; i < n - 1; i++) {
		intervals[i] = abs(remainder((float) rand() / RAND_MAX, p));
		p -= intervals[i];
	}

	intervals[n - 1] = p;
	for(int i = 0; i < nexp; i++) {
		x = (float) rand() / RAND_MAX;
		sum = 0;
		for (int j = 0; j < n; j++) {
			sum += intervals[j];
			if (x < sum) {
				++mas[j];
				break;
			}
		}
	}

	FILE *fd_out = fopen(filename.c_str(), "w");
  if (fd_out) {
    for(int i = 0; i < n; i++)
      fprintf(fd_out, "%d\t%.4f\t%.4f\n", i, intervals[i], (float) mas[i] / nexp);
    fclose(fd_out);
  }
}

void _methodRej(int n, int m, const char *filename) {
	float x;
	int mas[n];

	memset(mas, 0, sizeof(int) * n);
	for (int i = 0; i < m; i++) {
		x = methodReject();
		++mas[(int)(x / pi * n)];
	}

  FILE *fd_out = fopen(filename, "w");
  if (fd_out) {
    for (int i = 0; i < n; i++)
      fprintf(fd_out, "%d\t%d\n", i, mas[i]);
    fclose(fd_out);
  }
}
