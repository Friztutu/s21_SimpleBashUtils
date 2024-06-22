#include "../../include/cat/parser.h"

/**
 * @brief Validates the parameters passed to the program,
 * if the parameter is correct, marks it in the structure,
 * if not, displays an error message and returns the code.
 * @param [in] opt Char, command line parameter character.
 * @param [out] input_data InputData*, structure for storing input data.
 * @return int, 0 - OK, 1 - non-existent parameter.
 */
int ValidateCommandLineOptions(char opt, struct InputData* input_data) {
  int return_flag = 0;

  switch (opt) {
    case 'b':
      input_data->options.b_flag = true;
      break;
    case 'v':
      input_data->options.v_flag = true;
      break;
    case 'e':
      input_data->options.e_flag = true;  // flag e includes flag v
      input_data->options.v_flag = true;
      break;
    case 'n':
      input_data->options.n_flag = true;
      break;
    case 's':
      input_data->options.s_flag = true;
      break;
    case 't':
      input_data->options.t_flag = true;  // flag t includes flag v
      input_data->options.v_flag = true;
      break;
    case 'E':
      input_data->options.e_flag = true;
      break;
    case 'T':
      input_data->options.t_flag = true;
      break;
    default:
      fprintf(stderr, "cat: illegal option\nusage: cat [option...] [file ...]");
      return_flag = 1;
  }

  return return_flag;
}

/**
 * @brief Parsing program parameters using getopt lib.
 * @param [in] argc Int, number of command line arguments.
 * @param [in] argv Char**, array of command line arguments.
 * @param [out] input_data InputData*, structure for storing input data.
 * @return Int, 0 - Ok, 1 - troubles.
 */
int ParseCommandLineOptions(int argc, char* argv[],
                            struct InputData* input_data) {
  int return_flag = 0;

  int opt;
  opterr = 0;  // turn off error messages from getopt funcs
  static struct option long_options[] = {
      // names long(gnu) options
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
  };

  int option_index = 0;  // dont touch

  while ((opt = getopt_long(argc, argv, "bvenstET", long_options,
                            &option_index)) != -1 &&
         return_flag == 0) {
    if (ValidateCommandLineOptions(opt, input_data)) {
      return_flag = 1;
    }
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