#ifndef INCLUDES_GREP_PARSER
#define INCLUDES_GREP_PARSER

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Options {
  bool e_flag;
  bool i_flag;
  bool v_flag;
  bool c_flag;
  bool l_flag;
  bool n_flag;
  bool h_flag;
  bool s_flag;
  bool f_flag;
  bool o_flag;

  int num_of_f_flag;
};

struct InputData {
  char* filename;
  char* regex_filename;
  struct Options options;
};

int ValidateCommandLineOptions(char opt, struct InputData* input_data);

int ParseCommandLineOptions(int argc, char* argv[],
                            struct InputData* input_data);

char* GetFilename(int argc, char* argv[], bool first_time);

char* GetRegexFilename(int argc, char* argv[], bool first_time);
#endif