#include "s21_SmartCalc.h"

double num_str_to_double(char *input_str, int *i) {
  double num_doub = 0;
  char number_str[256] = {'0'};
  int num_ind = 0;
  while (strchr(NUMBERS_DOT, input_str[*i]) != NULL) {
    number_str[num_ind] = input_str[*i];
    (*i)++;
    num_ind++;
  }
  number_str[num_ind] = '\0';
  num_doub = atof(number_str);
  return num_doub;
}

void pars_operators(char *input_str, int i, Node **list) {
  if ((input_str[i] == '-' || input_str[i] == '+') &&
      (i == 0 || input_str[i - 1] == '('))
    push(list, 0, 0, '0');
  if (input_str[i] == '+' || input_str[i] == '-')
    push(list, 0, 1, input_str[i]);
  else if (input_str[i] == '*' || input_str[i] == '/' || input_str[i] == 'm')
    push(list, 0, 2, input_str[i]);
  else if (input_str[i] == '^')
    push(list, 0, 3, input_str[i]);
}

void pars_brackets(char *input_str, int i, Node **list) {
  if (input_str[i] == '(') {
    push(list, 0, -1, input_str[i]);
  } else if (input_str[i] == ')') {
    push(list, 0, -1, input_str[i]);
  }
}

void pars_functions(char *input_str, int *i, Node **list) {
  if (input_str[*i] == 's' && input_str[*i + 1] == 'i') {
    push(list, 0, 4, input_str[*i]);
    *i += 2;
  } else if (input_str[*i] == 'c' || input_str[*i] == 't') {
    push(list, 0, 4, input_str[*i]);
    *i += 2;
  } else if (input_str[*i] == 's' && input_str[*i + 1] == 'q') {
    push(list, 0, 4, input_str[*i + 1]);
    *i += 3;
  } else if (input_str[*i] == 'a' && input_str[*i + 1] == 'c') {
    push(list, 0, 4, '1');
    *i += 3;
  } else if (input_str[*i] == 'a' && input_str[*i + 1] == 's') {
    push(list, 0, 4, '2');
    *i += 3;
  } else if (input_str[*i] == 'a' && input_str[*i + 1] == 't') {
    push(list, 0, 4, '3');
    *i += 3;
  } else if (input_str[*i] == 'l' && input_str[*i + 1] == 'n') {
    push(list, 0, 4, 'n');
    *i += 1;
  } else if (input_str[*i] == 'l' && input_str[*i + 1] == 'o') {
    push(list, 0, 4, 'l');
    *i += 2;
  }
}

void s21_parser(char *input_str, Node **list) {
  int i = 0;
  while (input_str[i] != '\n' && input_str[i] != '\0') {
    if (strchr(NUMBERS, input_str[i]) != NULL) {
      double num_doub = num_str_to_double(input_str, &i);
      i--;
      push(list, num_doub, 0, '0');
    } else if (input_str[i] == 'x') {
      push(list, 0, 0, 'x');
    } else if (strchr(OPERATORS, input_str[i]) != NULL) {
      pars_operators(input_str, i, list);
    } else if (strchr(BRACKETS, input_str[i]) != NULL) {
      pars_brackets(input_str, i, list);
    } else if (strchr(FUNCS_F, input_str[i]) != NULL) {
      pars_functions(input_str, &i, list);
    }
    i++;
  }
}
