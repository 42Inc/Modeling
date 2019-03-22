#include "../include/extralib.h"

float func(float x) {
	float y;
	if (x <= -4 && x >= (5 * a_) ) {
		y = sqrt(x + 4);
	} else {
		y = 0;
	}
	return y;
}

void methodReject(const char* filename) {
	float x1, x2;
	int hit[20];
	memset(hit, 0, sizeof(int) * 20);

	for (int i = 0; i < MAX; i++) {
		float a = -4, b = 5 * a_, c = 1.1832;
		do {
      x1 = a + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(b-a)));
			x2 = a + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(b-a)));
		} while (func(a + (b - a) * x1) < c * x2);
		x2 *= c;
		x1 = a + (b - a) * x1;
		hit[(int)(x1 / 0.1)]++;
    printf("%d\n", hit[(int)(x1 / 0.1)]);
  }
	FILE *fd_out = fopen(filename, "w");
  if (fd_out) {
    for (int i = 0; i < 20; i++) {
      fprintf(fd_out, "%d\n", hit[i]);
    }
    fclose(fd_out);
  }
}

void with_repeats(int N, const char * filename) {
	float a = 1, mas[N], chance;
	int hit[N];
	memset(hit, 0, sizeof(int) * N);

	for (int i = 0; i < N - 1; i++)
	{
		mas[i] = abs(remainder((float) rand() / RAND_MAX, a));
		a -= mas[i];
	}

	mas[N - 1] = a;

	for (int i = 0; i < MAX; i++) {
		chance = (float) rand() / RAND_MAX;
		float sum = 0;
		for (int j = 0; j < N; j++) {
			sum += mas[j];
			if (chance < sum) {
				++hit[j];
				break;
			}
		}
	}

	FILE *fd_out = fopen(filename, "w");
  if (fd_out) {
    for (int i = 0; i < N; i++) {
      fprintf(fd_out, "%d\t%.4f\t%.d\n", i, mas[i] * MAX, hit[i]);
    }
    fclose(fd_out);
  }
}

void no_repeats(int N, const char * filename) {
	vector<int> nums, temp;
	int it, k = 3 * N / 4;
	int hit[N], part = MAX / k + 1;
	float p;

	memset(hit, 0, sizeof(int) * N);
	for(int number = 0; number < N; number++) {
		temp.push_back(number);
	}
	for(int j = 0; j < part; j++) {
		nums = temp;
		if (j == part - 1) k = MAX % k;
		for(int i = 0; i < k; i++) {
			p = 1.0 / (N - i);
			it = (float) rand() / RAND_MAX / p;
			++hit[nums[it]];
			nums.erase(nums.begin() + it);
		}
	}
	FILE *fd_out = fopen(filename, "w");
  if (fd_out) {
    for(int number = 0; number < N; number++) {
      fprintf(fd_out, "%d\t%.d\n", number, hit[number]);
    }
    fclose(fd_out);
  }
}
