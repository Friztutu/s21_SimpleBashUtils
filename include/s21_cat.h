#ifndef INCLUDE_S21_CAT
#define INCLUDE_S21_CAT

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dinamic_string.h"

#define START_SIZE_BUFFER 100

struct Options {
  bool b_flag;
  bool v_flag;
  bool e_flag;
  bool n_flag;
  bool s_flag;
  bool t_flag;
  bool without_flags;
};

struct InputData {
  char* filename;
  char* buffer;
  bool input_from_file;
  struct Options options;
};

int ValidateCommandLineOptions(char opt, struct InputData input_data);

int ParseCommandLineOptions(int argc, char* argv[],
                            struct InputData input_data);

char* GetFilename(int argc, char* argv[], bool first_time);

void UnmarkUselessOptions(struct InputData input_data);
#endif