#ifndef INCLUDES_STRUCTURES_H
#define INCLUDES_STRUCTURES_H

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Options {
  bool b_flag;
  bool v_flag;
  bool e_flag;
  bool n_flag;
  bool s_flag;
  bool t_flag;
};

struct InputData {
  char* filename;
  char* buffer;
  struct Options options;
};

int ValidateCommandLineOptions(char opt, struct InputData* input_data);

int ParseCommandLineOptions(int argc, char* argv[],
                            struct InputData* input_data);

char* GetFilename(int argc, char* argv[], bool first_time);

#endif