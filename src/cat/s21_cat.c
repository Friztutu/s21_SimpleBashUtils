#include "../../include/cat/s21_cat.h"

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    fprintf(stderr, "No options");
    return 0;
  }

  struct InputData* input_data = NULL;
  input_data = (struct InputData*)malloc(sizeof(struct InputData));
  SetUpStruct(input_data);

  if (ParseCommandLineOptions(argc, argv, input_data) == 1) {
    return 0;
  }

  UnmarkUselessOptions(input_data);

  input_data->filename = GetFilename(argc, argv, true);
  bool no_files = input_data->filename[0] == '\0';

  if (no_files) {
    fprintf(stderr, "cat: illegal option\nusage: cat [option...] [file ...]");
  }

  while (!no_files) {
    if (ProcessText(input_data) == 1) {
      fprintf(stderr, "cat: %s: No such file or directory",
              input_data->filename);
    }
    input_data->filename = GetFilename(argc, argv, false);
    no_files = input_data->filename[0] == '\0';
  }

  free(input_data->filename);

  return 0;
}

void SetUpStruct(struct InputData* input_data) {
  input_data->options.b_flag = false;
  input_data->options.t_flag = false;
  input_data->options.n_flag = false;
  input_data->options.s_flag = false;
  input_data->options.e_flag = false;
  input_data->options.v_flag = false;
}

void UnmarkUselessOptions(struct InputData* input_data) {
  if (input_data->options.b_flag) {
    input_data->options.n_flag = false;
  }
}

int ProcessText(struct InputData* input_data) {
  FILE* file = fopen(input_data->filename, "r");

  if (file == NULL) {
    return 1;
  }

  bool end_file = false;
  bool previous_empty = false;
  int line_number = 1;
  input_data->buffer = ReadStringFromFile(file, &end_file);

  while (!end_file) {
    bool is_empty = input_data->buffer[0] == '\0';

    if (input_data->options.s_flag && previous_empty && is_empty) continue;

    if (input_data->options.b_flag && !is_empty || input_data->options.n_flag) {
      printf("   %d  ", line_number++);
    }

    for (int i = 0; i < strlen(input_data->buffer); i++) {
      if (input_data->options.t_flag && input_data->buffer[i] == '\t') {
        printf("^I");
      } else {
        printf("%c", input_data->buffer[i]);
      }
    }

    if (input_data->options.e_flag) {
      printf("$");
    }

    printf("\n");

    free(input_data->buffer);
    input_data->buffer = ReadStringFromFile(file, &end_file);
  }

  fclose(file);
  free(input_data->buffer);
  free(input_data->filename);
  free(input_data);

  return 0;
}

char* ReadStringFromFile(FILE* file, bool* end_file) {
  int c;
  int index = 0, size = 31;
  char* buffer = malloc(sizeof(char) * 31);

  while (feof(file) == 0 && (c = fgetc(file)) != EOF && c != '\n') {
    if (index == size - 2) {
      buffer = append(buffer, size, 30);
      size += 30;
    }

    buffer[index++] = c;
  }

  if (c == EOF) {
    *end_file = true;
  }

  buffer[index] = '\0';

  return buffer;
}
