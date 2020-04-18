#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define eps 100.0
#define MIN(x, y) (x < y ? x : y)

double rowsum(int row, int n, double** matrix) {
  int i = 0;
  double result = 0.0;
  for (i = 0; i < n; ++i) {
    result += matrix[row][i];
  }
  return result;
}

double colsum(int col, int n, double** matrix) {
  int i = 0;
  double result = 0.0;
  for (i = 0; i < n; ++i) {
    result += matrix[i][col];
  }
  return result;
}

int getrand(int min, int max) {
  return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

/* Генератор матрицы */
int generator(int n, double** matrix) {
  int i = 0;
  int j = 0;

  /* Компенсирующие координаты */
  int row = 0;
  int col = 0;

  /* 0 минус, 1 плюс */
  int direction = 0;

  /* На сколько меняется элемент матрицы */
  double value = 0.0;
  /*
   * Если размерность матрицы меньше или 0 - ошибка.
   * Если указатель - NULL, тоже.
   */
  if (n <= 0 || !matrix) return 1;

  for (i = 0; i < n; ++i)
    if (!matrix[i]) return 2;

  /* Процесс генерации. Заполняем матрицу значениями 1/n */
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j) matrix[i][j] = 1.0 / n;

  srand(time(NULL));
  /* Изменение матрицы методом квадратов. Меняются 4 элемента за раз */
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      /* Генерация направления изменения */
      direction = getrand(0, 2);
      /* Генерация компенсирующих координат */
      while ((row = getrand(0, n)) == i)
        ;
      while ((col = getrand(0, n)) == j)
        ;
      /*
       * Изменяем квадрат значений в матрице в соответствии с выбранным
       * направлением.
       * Выбор минимального значения необходим, чтобы не уйти в минус.
       * Генерация с точностью до eps-ых.
       * Прим. eps = 100 -> с точностью до сотых
       */
      if (direction) {
        value = getrand(0, MIN(matrix[row][j], matrix[i][col]) * eps) / eps;
        matrix[i][j] += value;
        matrix[row][j] -= value;
        matrix[i][col] -= value;
        matrix[row][col] += value;
      } else {
        value = getrand(0, MIN(matrix[i][j], matrix[row][col]) * eps) / eps;
        matrix[i][j] -= value;
        matrix[row][j] += value;
        matrix[i][col] += value;
        matrix[row][col] -= value;
      }
    }
  }

  /* Печать матрицы в 2 знака + печать контрольных сумм */
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) fprintf(stderr, "%.02lf ", matrix[i][j]);
    /* Контрольная сумма строки */
    fprintf(stderr, "%.02lf\n", rowsum(i, n, matrix));
  }

  /* Контрольная сумма столбцов */
  for (i = 0; i < n; ++i) fprintf(stderr, "%.02lf ", colsum(i, n, matrix));

  fprintf(stderr, "\n");
  return 0;
}

int main(int argc, char** argv) {
  int i = 0;
  int j = 0;
  double tmp_double = 0.0;

  char* filename = "matrix.dat";
  FILE* fd = NULL;
  enum method { gen, file };
  enum method m = gen;

  /* Матрица */
  double** matrix = NULL;

  /* Размер матрицы - по умолчанию 5 */
  int n = argv[1] ? atoi(argv[1]) : 5;

  /* Количество переходов в имитации */
  int repeats = 10;
  /* Текущий шаг в имитации */
  int step = 0;
  /* Состояние. Стартовое - 0 */
  int state = 0;
  /* Псевдослучайная вероятность для перехода. Точность - до eps-ых */
  double prob = 0.0;

  /* Выделение памяти под матрицу */
  matrix = malloc(n * sizeof(double));
  /* Не выделилась память */
  if (!matrix) return 255;
  for (i = 0; i < n; ++i) {
    matrix[i] = malloc(n * sizeof(double));
    /* Не выделилась память */
    if (!matrix[i]) {
      for (j = 0; j < i; ++j) free(matrix[j]);
      free(matrix);
      return 254;
    }
  }

  /* Если задан вызов из генератора */
  if (argv[2] && !strcmp(argv[2], "gen")) {
    m = gen;
  } else if (argv[2] && !strcmp(argv[2], "file")) {
    /* Если вызов из файла */
    if (argv[3]) filename = argv[3];
    m = file;
  } else {
    m = gen;
  }

  /* Вызов генератора матрицы. Вернет 0, если успешно сгенерируется */
  if (m == gen) {
    if (generator(n, matrix)) return 253;
  } else {
    /* Чтение из файла */
    /* Ошибка открытия файла */
    if (!(fd = fopen(filename, "r"))) {
      return 252;
    }

    /* Читаем матрицу */
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
        fscanf(fd, "%lf", &matrix[i][j]);
      }
    }

    /* Печать матрицы в 2 знака + печать контрольных сумм */
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) fprintf(stderr, "%.02lf ", matrix[i][j]);
      /* Контрольная сумма строки */
      fprintf(stderr, "%.02lf\n", rowsum(i, n, matrix));
    }

    /* Контрольная сумма столбцов */
    for (i = 0; i < n; ++i) fprintf(stderr, "%.02lf ", colsum(i, n, matrix));
    fprintf(stderr, "\n");
  }

  do {
    /* Генерация вероятности перехода */
    prob = getrand(0, eps) / eps;
    /* Печать состояния. Шаг - состояние */
    fprintf(stdout, "%d %d\n", step, state);
    /* Переход в состояние на основе вероятности */
    tmp_double = 0.0;
    for (i = 0; i < n; ++i) {
      tmp_double += matrix[state][i];
      if (prob < tmp_double) {
        state = i;
        break;
      }
    }
    ++step;
  } while (step < repeats);

  /*
   * Mr. TeamLead, why only here you use a predefined constant,
   * ignoring all other returns?
   */
  return EXIT_SUCCESS;
}
