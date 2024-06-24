#include "../../include/grep/s21_grep.h"

int main(int argc, char* argv[]) {
  if (argc <= 2) {
    fprintf(stderr, "To few options");
    return 0;
  }

  struct InputData* input_data = NULL;
  input_data = (struct InputData*)malloc(sizeof(struct InputData));
  SetUpStruct(input_data);

  if (ParseCommandLineOptions(argc, argv, input_data) == 1) {
    return 0;
  }

  input_data->filename = GetFilename(argc, argv, true);
  bool no_files = input_data->filename[0] == '\0';
}

void SetUpStruct(InputData* input_data) {
  input_data->options.e_flag = false;
  input_data->options.i_flag = false;
  input_data->options.v_flag = false;
  input_data->options.c_flag = false;
  input_data->options.l_flag = false;
  input_data->options.n_flag = false;
  input_data->options.h_flag = false;
  input_data->options.s_flag = false;
  input_data->options.f_flag = false;
  input_data->options.o_flag = false;

  input_data->options.num_of_f_flag = 0;
}