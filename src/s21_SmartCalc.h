#ifndef S21_SMARTCALC_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PERMITTED_SYMBOLS "1234567890()+-*/^=.cosintaqrlgmdx"
#define NUMBERS "1234567890"
#define NUMBERS_DOT "1234567890."
#define OPERATORS "+-*/^m"
#define BRACKETS "()"
#define FUNCS "cosintaqrlgd"
#define FUNCS_F "cstal"
#define NOT_FIRST_ALL "+-*/^).oingrq"
#define NOT_FIRST "*/^).oingrq"

typedef struct Node {
  double value;
  int priority;
  char type;
  struct Node *next;
} Node;

int Smart_calc(char *input_str, double *res, double X);
void clear_stack(Node **list);
int s21_is_valide(char *input_str);
void s21_parser(char *input_str, Node **list);
void clear_stack(Node **list);
void push(Node **plist, double value, int priority, char type);
void pop(Node **plist, double *value, int *priority, char *type);
int peek(Node *plist, double *value, int *priority, char *type);
int is_empty_stack(Node *list);
void convert_stack(Node *input, Node **convert);
void pol_notation(Node *convert, Node **ready);
double calculation(Node **list, int *error);
double calculate_x(Node **list, double X, int *error);

#endif
