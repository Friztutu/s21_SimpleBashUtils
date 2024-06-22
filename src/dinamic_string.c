#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: поправить всякое
char* append(char* old_string, int size, int step) {
  char* new_string = malloc(sizeof(char) * (size + step));

  for (int i = 0; i < size - 2; i++) {
    new_string[i] = old_string[i];
  }

  free(old_string);

  return new_string;
}