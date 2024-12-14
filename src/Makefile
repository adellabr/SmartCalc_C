CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -Wall -Werror -Wextra --coverage
SRC = s21_calculation.c s21_parser.c s21_stack.c s21_valide.c
OBJS = $(SRC:.c=.o)

OS := $(shell uname -s)

ifeq ($(OS),Linux)
  LIBS =  -pthread -lcheck -lm -lrt -lsubunit
else
  LIBS = -lcheck -lm
endif


all: clean install

gcov_report: clean s21_SmartCalc_test.c $(SRC)
	$(CC) $(GCOVFLAGS) -c $(SRC) 
	ar rcs s21_SmartCalc.a $(OBJS)
	$(CC) $(GCOVFLAGS) -c s21_SmartCalc_test.c -o s21_SmartCalc_test.o
	$(CC) $(GCOVFLAGS) s21_SmartCalc_test.o s21_SmartCalc.a -o gcov_unit_test $(LIBS)
	./gcov_unit_test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	open ./report/index.html
	make clean_without_report

test: s21_SmartCalc.a 
	$(CC) $(CFLAGS) s21_SmartCalc_test.c $< -o unit_test $(LIBS)
	./unit_test

install: clean uninstall
	cd frontend && qmake Calculator.pro && make && make clean && rm Makefile && mkdir ../build && mv Calculator.app/$(UI_BIN) ../build/

dvi:
	open ./documentation.md

dist: install
	mkdir -p dist
	cp  -R ./build/Calculator.app ./dist/Calculator.app
	cp ./documentation.md ./dist/documentation.md
	cd ./dist && tar cvzf Calculator.tgz *
	cd ./dist && rm -R Calculator.app documentation.md
	make clean	

uninstall:
	rm -rf build

SmartCalc_tests.o: s21_SmartCalc_test.c
	$(CC) $(CFLAGS) -c s21_SmartCalc_test.c -o $@

s21_SmartCalc.a: $(OBJS)
	ar rcs s21_SmartCalc.a $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clang:
	clang-format -i *.c *.h 

clean_without_report: 
	rm -f  *.o *.gcno *.gcov *.gcda *.info *.a main_test unit_test gcov_unit_test

clean: clean_without_report
	rm -rf report test_log/*.log check
