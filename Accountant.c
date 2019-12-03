#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/kutuphanem.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

size_t get_space_count(char *str, size_t len);
char **split(char *cmd, size_t len, size_t space_count);
void printStringArray(char **arr, size_t count);
char **getArgs(char *command, size_t len, size_t space_count);
bool isSpecialCommand(size_t space_count);
bool isNumeric(const char *s);
void makeNullTerminated(char **sonuc, size_t elm_count);
int callProgram(char *path, char *const argv[], char **envp);
bool parametersValid(char **argv, size_t elm_count, size_t commandCode);
void readAll();
void clearScreen();
void displayHelp();

int main(int argc, char *argv[], char **envp) {
  char *command;
  printf("Welcome to the Accountant, type %s to get help", "help");
  do {
    printf("\nAccountant >> ");
    command = metinAl();
    size_t len = strlen(command);
    size_t space_count = get_space_count(command, len);

    if (isSpecialCommand(space_count)) {
      if (strcmp(command, "exit") == 0) {
        break;
      }
      if (strcmp(command, "readAll") == 0) {
        readAll(envp);
        continue;
      }

      if (strcmp(command, "clear") == 0) {
        clearScreen();
        continue;
      }
      if (strcmp(command, "help") == 0) {
        displayHelp();
        continue;
      }

      printf("Hatalı giriş yaptınız");
      continue;
    }

    char **argv = getArgs(command, len, space_count);

    int size = sizeof(argv) / sizeof(argv[0]);

    size_t elm_count = space_count + 1;
    makeNullTerminated(argv, elm_count);

    if (strcmp(*argv, "insert") == 0) {
      if (!parametersValid(argv, elm_count, 0)) {
        printf("Tüm parametreler sayı olmalıdır");
        continue;
      }

      int result = callProgram("Inserter", argv, envp);
    } else if (strcmp(*argv, "calculate") == 0) {
      if (!parametersValid(argv, elm_count, 1)) {
        printf("1. parametre harf diğerleri pozitif tam sayı olmalıdır");
        continue;
      }

      int result = callProgram("Calc", argv, envp);
      if (result < 0) {
        printf("%s\n", "Hatalı giriş yaptınız");
        continue;
      }
      printf("sum: %d\n", result);
    }

  } while (1);

  return 0;
}

void clearScreen() { printf("\033[H\033[J"); }

void displayHelp() {
  printf("Available commands:\n%s\n%s\n%s\n%s\n%s\n%s", "insert", "calculate",
         "readAll", "clear", "help", "exit");
}

void readAll(char **envp) {
  char *argv[3];
  *argv = "cat";
  *(argv + 1) = "./files/database.txt";
  *(argv + 2) = NULL;
  callProgram("/bin/cat", argv, envp);
}

int callProgram(char *path, char *const argv[], char **envp) {
  int result;
  int pid = fork();
  if (pid == 0) {
    // Child
    execve(path, argv, envp);
    perror("child: execve failed\n");
  } else if (pid < 0) {
    return -1;
  } else {
    int waitstatus;
    wait(&waitstatus);
    result = WEXITSTATUS(waitstatus);
  }
  return (254 - result) < 0 ? -1 : result;  // Hatalı durumda result : 255
}

bool isAlphabetical(char ch) {
  return (ch == 's' || ch == 'S') || (ch == 'r' || ch == 'R');
}

int ctoi(char *c) { return *c - '0'; }

bool isNumber(char *c) {
  char elm;
  for (size_t i = 0; (elm = *(c + i)) != '\0'; i++) {
    printf("%c\n", elm);
    if (!(elm > 47 && elm < 58)) return false;
  }
  return true;
}

bool isNumeric(const char *s) {
  if (s == NULL || *s == '\0' || isspace(*s)) return 0;
  char *p;
  strtod(s, &p);
  return *p == '\0';
}

bool containsNonNumericOrNegative(char **str, size_t size, char caller) {
  size_t i = (caller == 'i' ? 1 : 2);
  // calculate's first argument is a char, so we discard it.
  for (; i < size; i++) {
    if (!isNumeric(*(str + i)) || ctoi(*(str + i)) < 0) return true;
  }
  return false;
}

bool IsCalculateValid(char **argv, size_t elm_count) {
  if (elm_count != 4) return false;
  char mustBeAlphabetical = *(*(argv + 1));
  if (!isAlphabetical(mustBeAlphabetical)) return false;
  if (containsNonNumericOrNegative(argv, elm_count, 'c')) return false;
  return true;
}

bool IsInsertValid(char **argv, size_t elm_count) {
  return containsNonNumericOrNegative(argv, elm_count, 'i') ? false : true;
}

bool parametersValid(char **argv, size_t elm_count, size_t commandCode) {
  if (commandCode == 0) {
    return IsInsertValid(argv, elm_count);
  } else if (commandCode == 1) {
    return IsCalculateValid(argv, elm_count);
  }
  return -1;
}

void makeNullTerminated(char **sonuc, size_t elm_count) {
  char *a = NULL;
  sonuc[elm_count] = a;
}

bool isSpecialCommand(size_t space_count) { return space_count == 0; }

char **getArgs(char *command, size_t len, size_t space_count) {
  char **sonuc = split(command, len, space_count);
  size_t elm_count = space_count + 1;
  return sonuc;
}

char *subString(char *str, size_t start_idx, size_t end_idx) {
  // start: inclusive, end: exclusive
  size_t size = end_idx - start_idx;
  char *result = malloc(size * sizeof(char));
  size_t count = 0;
  for (size_t i = start_idx; i < end_idx; i++) {
    *(result + count) = *(str + i);
    count++;
  }
  return result;
}

char *subStringEnd(char *str, size_t start_idx, size_t size) {
  size_t len = (size - start_idx) * sizeof(char);
  char *result = malloc(len);
  size_t count = 0;
  for (size_t i = start_idx; i < size; i++) {
    *(result + count) = *(str + i);
    count++;
  }
  return result;
}

char **biggerBuffer(char **arr, size_t buf_size) {
  return realloc(arr, (2 * buf_size) * sizeof(char *));
}

char **split(char *cmd, size_t len, size_t space_count) {
  size_t buf_size = 10;
  char **tmp = malloc(buf_size * sizeof(char *));
  size_t num_of_spaces = space_count;
  size_t count = 0;
  for (size_t i = 0; i < len; i++) {
    if (*(cmd + i) == ' ') {
      size_t bosluk_idx = i;
      char *bastanBoslugaKadar = subString(cmd, 0, bosluk_idx);

      if (i >= buf_size) {
        tmp = biggerBuffer(tmp, buf_size);
      }

      *(tmp + count) = bastanBoslugaKadar;

      size_t bosluktanSonrakiIlkChar = bosluk_idx + 1;
      cmd = subStringEnd(cmd, bosluktanSonrakiIlkChar, len);

      if (num_of_spaces == 1) {
        char **result = malloc((count + 1) * sizeof(char *));
        *(tmp + (count + 1)) = cmd;
        result = tmp;
        return result;
      }

      i = 0;  // kalan dizinin en başından başla
      num_of_spaces--;
      count++;
    }
  }
  return NULL;
}

size_t get_space_count(char *str, size_t len) {
  size_t space_count = 0;
  for (size_t i = 0; i < len; i++) {
    if (*(str + i) == ' ') {
      space_count++;
    }
  }
  return space_count;
}