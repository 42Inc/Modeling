#include "../include/main.h"

using namespace std;

void xi_2(double *masNum) {
	int mas[I], i;
	double sum = 0, V = 0;

  string fname = "./result/v.dat";
	ofstream fout(fname.c_str());

	for(int j = 0; j < Nexp; j++) {
		memset(mas, 0, sizeof(mas));
		sum = 0;

		for(i = 0; i < N; i++) {
			masNum[i] = (double)rand() / RAND_MAX;
			mas[(int)(masNum[i] * I)] += 1;
		}

		for(i = 0; i < I; i++)
			sum += mas[i] * mas[i] * I;
		V += sum / N - N;
	}

	V /= Nexp;
	fout << V << endl;

	fout.close();
}

void autoCor(double *masNum) {
	int i;
	double x = 0, y = 0, xy = 0,
		Gx = 0, Gy = 0, Acor = 0;

  string fname = "./result/autocor.dat";
	ofstream fout(fname.c_str());

  for (L = 1; L < N / 2; L++) {
		for(i = L; i < N; i++) {
			x += masNum[i];
			y += masNum[i - L];
			xy += masNum[i] * masNum[i - L];
		}

		x /= N - L; y /= N - L; xy /= N - L;
		for(i = L; i < N; i++) {
			Gx += pow(masNum[i] - x, 2);
			Gy += pow(masNum[i - L] - y, 2);
		}

		Gx = sqrt(Gx / (N - L));
		Gy = sqrt(Gy / (N - L));
		Acor = (xy - x * y) / (Gx * Gy);
		fout << L << " " << Acor << endl;
	}

  fout.close();
}

int main(int argc, char **argv) {
  srand(time(NULL));
	double masNum[N];

	xi_2(masNum);
	autoCor(masNum);

  return EXIT_SUCCESS;
}
