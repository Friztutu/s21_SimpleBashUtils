#include "../../include/grep/grep_parser.h"

int ParseCommandLineOptions(int argc, char* argv[],
                            struct InputData* input_data) {
  int return_flag = 0;
  char opt;
  opterr = 0;

  while ((opt = getopt(argc, argv, "eivclnhsfo")) != -1 && !return_flag) {
    if (ValidateCommandLineOptions(opt, input_data)) {
      return_flag = 1;
    }
  }

  return return_flag;
}

int ValidateCommandLineOptions(char opt, struct InputData* input_data) {
  int return_flag = 0;

  switch (opt) {
    case 'e':
      input_data->options.e_flag = true;
      break;
    case 'i':
      input_data->options.i_flag = true;
      break;
    case 'v':
      input_data->options.v_flag = true;
      break;
    case 'c':
      input_data->options.c_flag = true;
      break;
    case 'l':
      input_data->options.l_flag = true;
      break;
    case 'n':
      input_data->options.n_flag = true;
      break;
    case 'h':
      input_data->options.h_flag = true;
      break;
    case 's':
      input_data->options.s_flag = true;
      break;
    case 'f':
      input_data->options.f_flag = true;
      input_data->options.num_of_f_flag += 1;
      break;
    case 'o':
      input_data->options.o_flag = true;
      break;
    default:
      fprintf(stderr,
              "grep: illegal option\nusage: grep [option...] [file ...]");
      return_flag = 1;
  }

  return return_flag;
}

/**
 * @brief Looks for file names in command line arguments,
 * each new function call will return the next file name (if any), i
 * f there are no more names, it will return an empty string.
 * @param [in] argc Int, number of command line arguments.
 * @param [in] argv Char**, array with command line arguments.
 * @param [in] first_time bool, If the function is called first for these
 * arguments
 * - true, else - false.
 * @return Char*, if there - filename, else - empty string.
 */
char* GetFilename(int argc, char* argv[], bool first_time) {
  char* filename = malloc(sizeof(char) * 30);
  filename[0] = '\0';

  static int index;

  if (first_time) {
    index = 1;  // to bypass by argv
  }

  for (; index < argc; index++) {
    if (argv[index][0] == '-')
      continue;  // if its start by '-', its not filename

    int j;
    for (j = 0; j < strlen(argv[index]); j++) {
      // TODO: обработка длинных названий файлов
      filename[j] = argv[index][j];
    }
    filename[++j] = '\0';
    index++;
    break;  // we already have one filename, one required to return it.
  }

  return filename;
}

char* GetRegexFilename(int argc, char* argv[], bool first_time) {
  char* regex_filename = malloc(sizeof(char) * 30);
  regex_filename[0] = '\0';

  static int index;

  if (first_time) {
    index = 1;
  }

  bool next_if_filename = false;
  for (; index < argc; index++) {
    if (argv[index][0] == '-' && argv[index][1] == 'f') {
      next_if_filename = true;
      continue;
    }

    if (next_if_filename) {
      int j;
      for (j = 0; j < strlen(argv[index]); j++) {
        // TODO: обработка длинных названий файлов
        regex_filename[j] = argv[index][j];
      }
      regex_filename[++j] = '\0';
      index++;
      break;  // we already have one filename, one required to return it.
    }
  }

  return regex_filename;
}