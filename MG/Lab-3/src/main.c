#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define eps 1000.0
#define MIN(x, y) (x < y ? x : y)
#define ABS(x) ((x) < 0 ? (-(x)) : (x))
#define SWAP(x, y, tmp) \
  {                     \
    tmp = x;            \
    x = y;              \
    y = tmp;            \
  }
#define EPS (int)(log10(eps))

#define CHECKSUM 0
#define WITH_VECTOR 1

#define MAX_BUFFER_SIZE 256
static char buffer[MAX_BUFFER_SIZE];

/* Подсчет суммы строки матрицы */
double rowsum(int row, int n, double** matrix) {
  int i = 0;
  double result = 0.0;
  for (i = 0; i < n; ++i) {
    result += matrix[row][i];
  }
  return result;
}

/* Подсчет суммы столбца матрицы */
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
  /* Печать матрицы в EPS знаков + печать контрольных сумм */
  for (i = 0; i < n; ++i) {
    sprintf(buffer, "%%.0%dlf ", EPS);
    for (j = 0; j < n; ++j) fprintf(stderr, buffer, matrix[i][j]);
#if CHECKSUM == 1
    /* Контрольная сумма строки */
    sprintf(buffer, "%%.0%dlf\n", EPS);
    fprintf(stderr, buffer, rowsum(i, n, matrix));
#else
    fprintf(stderr, "\n");
#endif
  }
#if CHECKSUM == 1
  /* Контрольная сумма столбцов */
  sprintf(buffer, "%%.0%dlf ", EPS);
  for (i = 0; i < n; ++i) fprintf(stderr, buffer, colsum(i, n, matrix));
#endif

  fprintf(stderr, "\n");
  return 0;
}

#if WITH_VECTOR == 1
/* Умножение матрицы на вектор */
void dgemv(double** matrix, double* vector, double* result, int n, int m) {
  int i = 0;
  int j = 0;
  for (i = 0; i < n; ++i) {
    result[i] = 0.0;
    for (j = 0; j < m; ++j) result[i] += matrix[j][i] * vector[j];
  }
}

/* Проверка вектора на равновероятность */
int is_equal_prob_vector(double* vector, int n) {
  int i = 0;
  double s = 1.0 / n;
  for (i = 0; i < n; ++i) {
    if ((ABS(vector[i] - s) > (1 / eps))) {
      return 0;
    }
  }
  return 1;
}

#endif

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
  /* Вектор встречаемости состояний */
  int* state_entries = NULL;

  /* Размер матрицы - по умолчанию 5 */
  int n = argv[1] ? atoi(argv[1]) : 5;

  /* Количество переходов в имитации */
  int repeats = 10000;
  /* Текущий шаг в имитации */
  int step = 0;
  /* Состояние. Стартовое - 0 */
  int state = 0;
  /* Псевдослучайная вероятность для перехода. Точность - до eps-ых */
  double prob = 0.0;

#if WITH_VECTOR == 1
  double* tmp_double_ptr = NULL;
  /* Вектор вероятности переходов */
  double* vector = NULL;
  double* vector_c = NULL;
  int equal_state = state;
  int save_trigger = 0;
#endif

  /* Выделение памяти под матрицу и вектор(а) */
  matrix = (double**)malloc(n * sizeof(double*));
  state_entries = (int*)calloc(n, sizeof(int));
  /* Не выделилась память */
  if (!matrix || !state_entries) return 255;
#if WITH_VECTOR == 1
  vector = (double*)calloc(n, sizeof(double));
  vector_c = (double*)calloc(n, sizeof(double));
  /* Не выделилась память */
  if (!vector || !vector_c) return 255;
  vector[state] = 1.0;
#endif

  for (i = 0; i < n; ++i) {
    matrix[i] = (double*)malloc(n * sizeof(double));
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
      sprintf(buffer, "%%.0%dlf ", EPS);
      for (j = 0; j < n; ++j) fprintf(stderr, buffer, matrix[i][j]);
#if CHECKSUM == 1
      /* Контрольная сумма строки */
      sprintf(buffer, "%%.0%dlf\n", EPS);
      fprintf(stderr, buffer, rowsum(i, n, matrix));
#else
      fprintf(stderr, "\n");
#endif
    }

#if CHECKSUM == 1
    /* Контрольная сумма столбцов */
    sprintf(buffer, "%%.0%dlf ", EPS);
    for (i = 0; i < n; ++i) fprintf(stderr, buffer, colsum(i, n, matrix));
    fprintf(stderr, "\n");
#endif
  }

#if WITH_VECTOR == 1
  fprintf(stderr, "\n");
  /* Вывод вектора вероятностей переходов */
  sprintf(buffer, "%%.0%dlf ", EPS);
  for (i = 0; i < n; ++i) fprintf(stderr, buffer, vector[i]);
#if CHECKSUM == 1
  sprintf(buffer, "%%.0%dlf", EPS);
  fprintf(stderr, buffer, rowsum(0, n, &vector));
#endif
  fprintf(stderr, "\n");
#endif

  do {
    /* Сохранение вхождения в состояние */
    ++state_entries[state];
#if WITH_VECTOR == 1
    if (!is_equal_prob_vector(vector, n)) {
      /* Просчет вероятностей переходов */
      dgemv(matrix, vector, vector_c, n, n);
      /* Вывод вектора вероятностей переходов */
      sprintf(buffer, "%%.0%dlf ", EPS);
      for (i = 0; i < n; ++i) fprintf(stderr, buffer, vector_c[i]);
#if CHECKSUM == 1
      sprintf(buffer, "%%.0%dlf", EPS);
      fprintf(stderr, buffer, rowsum(0, n, &vector_c));
#endif
      fprintf(stderr, "\n");
      SWAP(vector, vector_c, tmp_double_ptr);
    } else {
      if (!save_trigger) {
        equal_state = step;
        save_trigger = 1;
      }
    }
#endif
    /* Генерация вероятности перехода */
    prob = getrand(0, eps) / eps;
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

#if WITH_VECTOR == 1
  fprintf(stderr, "Equal state : %d\n", equal_state);
#endif
  /* Печать состояния. Состояние - количество */
  for (i = 0; i < n; ++i) fprintf(stdout, "%d %d\n", i, state_entries[i]);
  /*
   * Mr. TeamLead, why only here you use a predefined constant,
   * ignoring all other returns?
   */
  return EXIT_SUCCESS;
}
