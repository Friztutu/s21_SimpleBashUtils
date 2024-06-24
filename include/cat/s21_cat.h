#ifndef INCLUDE_S21_CAT
#define INCLUDE_S21_CAT

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../dinamic_string.h"
#include "cat_parser.h"

void UnmarkUselessOptions(struct InputData* input_data);

int ProcessText(struct InputData* input_data);

char* ReadStringFromFile(FILE* file, bool* end_file);

void SetUpStruct(struct InputData* input_data);
#endif