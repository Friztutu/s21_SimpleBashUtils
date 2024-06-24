#include "../../include/grep/s21_grep.h"

int main(int argc, char* argv[]) {
  if (argc <= 2) {
    fprintf(stderr, "To few options");
    return 0;
  }

  struct InputData* input_data = NULL;
  input_data = (struct InputData*)malloc(sizeof(struct InputData));
  // SetUpStruct(input_data);

  if (ParseCommandLineOptions(argc, argv, input_data) == 1) {
    return 0;
  }

  input_data->filename = GetFilename(argc, argv, true);
  bool no_files = input_data->filename[0] == '\0';
}