#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

const char* dbPath = "./files/database.txt";

typedef struct numbers {
  int* numbers;
  int elm_count;
} numbers;

int ctoi(char c) { return c - '0'; }

int* biggerBuffer(int* arr, size_t capacity) {
  return realloc(arr, 2 * capacity * sizeof(int));
}

numbers readAll(FILE* fp) {
  numbers n1;
  size_t capacity = 10;
  int* numbers = malloc(capacity * sizeof(int));
  size_t elm_count = 0;
  for (size_t i = 0; !feof(fp); i++) {
    fscanf(fp, "%d ", (numbers + i));
    if (i >= capacity) {
      numbers = biggerBuffer(numbers, capacity);
    }
    elm_count++;
  }
  n1.numbers = numbers;
  n1.elm_count = elm_count;
  return n1;
}

int SumSingle(int* numbers, int first_idx, int second_idx) {
  return *(numbers + first_idx) + *(numbers + second_idx);
}

int sumAll(int* numbers, size_t len) {
  int sum = 0;
  for (size_t i = 0; i < len; i++) {
    sum += *(numbers + i);
  }
  return sum;
}

void print(char* str) {
  for (size_t i = 0; *(str + i) != '\0'; i++) {
    printf("%zu. elm: %c\n", i, *(str + i));
  }
}

void swap(int* a, int* b) {
  *a += *b;
  *b = *a - *b;
  *a -= *b;
}

int SumRange(numbers numbers, int start_idx, int end_idx) {
  size_t size = numbers.elm_count;

  if (start_idx > end_idx) {
    swap(&start_idx, &end_idx);
  }

  int* rangedNums = malloc(size * sizeof(int));
  size_t ranged_idx = 0;

  for (size_t i = start_idx; i <= end_idx; i++) {
    *(rangedNums + ranged_idx) = *(numbers.numbers + i);
    ranged_idx++;
  }

  return sumAll(numbers.numbers, size);
}

int main(int argc, char const* argv[]) {
  char calcMode = *(*(argv + 1));
  int start_idx = atoi(*(argv + 2));
  int end_idx = atoi(*(argv + 3));

  FILE* fp = fopen(dbPath, "r");
  numbers numbers = readAll(fp);

  if (start_idx > numbers.elm_count || end_idx > numbers.elm_count) {
    return -1;
  }

  if (start_idx < 0 || end_idx < 0) {
    return -1;
  }

  int result = calcMode == 's' ? SumSingle(numbers.numbers, start_idx, end_idx)
                               : SumRange(numbers, start_idx, end_idx);
  return result;
}
