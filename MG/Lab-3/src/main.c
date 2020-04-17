#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Генератор матрицы */
int generator(int n, double** matrix) {
  int i = 0;
  int j = 0;
  /*
   * Если размерность матрицы меньше или 0 - ошибка.
   * Если указатель - NULL, тоже.
   * */
  if (n <= 0 || !matrix)
    return 1;

  for (i = 0; i < n; ++i)
    if (!matrix[i])
      return 2;

  /* Процесс генерации. Заполняем матрицу значениями 1/n */
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      matrix[i][j] = 1.0 / n;

  /* Печать матрицы в 2 */
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j)
      fprintf(stderr, "%.02lf ", matrix[i][j]);
    fprintf(stderr, "\n");
	}
  return 0;
}

int main(int argc, char** argv) {
  int i = 0;
  int j = 0;

  char* filename = "matrix.dat";
  enum method { gen, file };
  enum method m = gen;

  /* Матрица */
  double** matrix = NULL;
  /* Размер матрицы - по умолчанию 5 */
  int n = argv[1] ? atoi(argv[1]) : 5;

  matrix = malloc(n * sizeof(double));
  /* Не выделилась память */
  if (!matrix) return 255;

  for (i = 0; i < n; ++i) {
    matrix[i] = malloc(n * sizeof(double));
    /* Не выделилась память */
    if (!matrix[i]) {
      for (j = 0; j < i; ++j)
        free(matrix[j]);
      free(matrix);
      return 254;
    }
  }

  /* Если задан вызов из генератора */
  if (argv[2] && !strcmp(argv[2], "gen")) {
    m = gen;
	} else if (argv[2] && !strcmp(argv[2], "file")) {
    /* Если вызов из файла */
    if (argv[3])
      filename = argv[3];
    m = file;
  } else {
    m = gen;
  }
  /* Вызов генератора матрицы. Вернет 253, если будет ошибка */
  if (m == gen) {
    if (generator(n, matrix)) return 253;
  } else {
    /* Чтение из файла*/
  }

  /* TODO: Имитация переходов*/
  return EXIT_SUCCESS;
}
