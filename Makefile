CC=gcc
CCFLAG=-Wall -Werror -Wextra

CAT_SOURCE=src/cat/s21_cat.c src/cat/cat_parser.c src/dinamic_string.c
CAT_INCLUDES=include/cat/cat_parser.h include/cat/s21_cat.h include/dinamic_string.h

GREP_SOURCE=src/grep/s21_grep.c src/grep/grep_parser.c src/dinamic_string.c
GREP_INCLUDES=include/grep/grep_parser.h include/grep/s21_grep.h include/dinamic_string.h

all: s21_cat.out

s21_cat.out : src/cat/s21_cat.c include/cat/s21_cat.h
	$(CC) $(CCFLAGS) $(CAT_SOURCE) -o bin/s21_cat.out

s21_grep.out : src/grep/s21_grep.c include/grep/s21_grep.h
	$(CC) $(CCFLAGS) $(GREP_SOURCE) -o bin/s21_grep.out

code_style:
	mv linter/.clang-format .
	clang-format -i $(CAT_SOURCE) $(CAT_INCLUDES) $(GREP_SOURCE) $(GREP_INCLUDES)
	mv .clang-format linter/.

check_code_style:
	mv linter/.clang-format .
	clang-format -n $(CAT_SOURCE) $(CAT_INCLUDES) $(GREP_SOURCE) $(GREP_INCLUDES)
	mv .clang-format linter/.

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(CAT_SOURCE) $(CAT_INCLUDES)
clean:
	rm -rf src/*.o bin/*.out

rebuild: clean all