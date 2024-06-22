#include "../include/s21_cat.h"

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    fprintf(stderr, "No options");
    return 0;
  }

  struct InputData input_data;
  input_data.options.b_flag = false;
  input_data.options.t_flag = false;
  input_data.options.n_flag = false;
  input_data.options.s_flag = false;
  input_data.options.e_flag = false;
  input_data.options.v_flag = false;

  if (ParseCommandLineOptions(argc, argv, input_data) == 1) {
    return 0;
  }

  UnmarkUselessOptions(input_data);

  char* filename = GetFilename(argc, argv, true);
  bool no_files = filename[0] == '\0';

  if (no_files) {
    fprintf(stderr, "cat: illegal option\nusage: cat [option...] [file ...]");
  }

  while (!no_files) {
    if (ProcessText(filename, input_data) == 1) {
      fprintf(stderr, "cat: %s: No such file or directory", filename);
    }
    char* filename = GetFilename(argc, argv, false);
    no_files = filename[0] == '\0';
  }

  free(filename);

  return 0;
}

int ValidateCommandLineOptions(char opt, struct InputData input_data) {
  int return_flag = 0;

  switch (opt) {
    case 'b':
      input_data.options.b_flag = true;
      break;
    case 'v':
      input_data.options.v_flag = true;
      break;
    case 'e':
      input_data.options.e_flag = true;
      input_data.options.v_flag = true;
      break;
    case 'n':
      input_data.options.n_flag = true;
      break;
    case 's':
      input_data.options.s_flag = true;
      break;
    case 't':
      input_data.options.t_flag = true;
      input_data.options.v_flag = true;
      break;
    case 'E':
      input_data.options.e_flag = true;
      break;
    case 'T':
      input_data.options.t_flag = true;
      break;
    default:
      fprintf(stderr, "cat: illegal option\nusage: cat [option...] [file ...]");
      return_flag = 1;
  }

  return return_flag;
}

int ParseCommandLineOptions(int argc, char* argv[],
                            struct InputData input_data) {
  int return_flag = 0;

  int opt;
  opterr = 0;
  static struct option long_options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
  };

  int option_index = 0;

  while ((opt = getopt_long(argc, argv, "bvenstET", long_options,
                            &option_index)) != -1 &&
         return_flag == 0) {
    if (ValidateCommandLineOptions(opt, input_data)) {
      return_flag = 1;
    }
  }

  return return_flag;
}

char* GetFilename(int argc, char* argv[], bool first_time) {
  char* filename = malloc(sizeof(char) * 30);
  filename[0] = '\0';

  static int index;

  if (first_time) {
    index = 1;
  }

  for (; index < argc; index++) {
    if (argv[index][0] == '-') continue;

    int j;
    for (j = 0; j < strlen(argv[index]); j++) {
      // TODO: обработка длинных названий файлов
      filename[j] = argv[index][j];
    }
    filename[++j] = '\0';
    index++;
    break;
  }

  return filename;
}

void UnmarkUselessOptions(struct InputData input_data) {
  if (input_data.options.b_flag) {
    input_data.options.n_flag = false;
  }
}

int ProcessText(char* filename, struct InputData input_data) {
  FILE* file = fopen(filename, "r");

  if (file == NULL) {
    return 1;
  }

  bool* end_file = false;
  bool previous_empty = false, is_empty = false;
  int line_number = 1;
  char* buffer = ReadStringFromFile(file, end_file);

  while (!end_file) {
    is_empty = buffer[0] == '\n';

    if (input_data.options.s_flag && previous_empty && is_empty) continue;

    if (input_data.options.b_flag && !is_empty) {
      printf("\t%d  ", line_number);
    }

    if (input_data.options.n_flag) {
      printf("\t%d  ", line_number);
    }

    printf("%s", buffer);

    if (input_data.options.e_flag) {
      printf("$");
    }

    printf("\n");

    line_number++;
    free(buffer);
    buffer = ReadStringFromFile(file, end_file);
  }

  fclose(file);
  free(buffer);
  free(filename);

  return 0;
}

char* ReadStringFromFile(FILE* file, bool* end_file) {
  char c;
  int index = 0, size = 31;
  char* buffer = malloc(sizeof(char) * 31);

  while ((c = fgetc(file)) != EOF && c != '\n') {
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
