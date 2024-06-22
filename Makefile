CC=gcc
CCFLAG=-Wall -Werror -Wextra

all: s21_cat.out

s21_cat.out : src/s21_cat.c include/s21_cat.h
	$(CC) $(CCFLAGS) src/dinamic_string.c src/s21_cat.c -o bin/s21_cat.out

s21_grep.out : src/s21_grep.c include/s21_grep.h
	$(CC) $(CCFLAGS) src/s21_grep.c -o bin/s21_grep.out

code_style:
	mv linter/.clang-format .
	clang-format -i src/*.c include/*.h
	mv .clang-format linter/.

check_code_style:
	mv linter/.clang-format .
	clang-format -n src/*.c include/*.h
	mv .clang-format linter/.

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem src/*.c include/*.h
clean:
	rm -rf src/*.o bin/*.out

rebuild: clean all