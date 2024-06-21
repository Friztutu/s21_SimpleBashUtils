#include <stdlib.h>
#include <string.h>

char* append(char* old_string, int step) {
  char* new_string = malloc(sizeof(char) * (strlen(old_string) + 1 + step));

  for (int i = 0; i < strlen(old_string); i++) {
    new_string[i] = old_string[i];
  }

  free(old_string);
}

void clear(char* string) {
  free(string);
  string = NULL;
}