#include "s21_SmartCalc.h"

int Smart_calc(char *input_str, double *res, double X) {
  int error = 0;
  if (s21_is_valide(input_str)) {
    Node *input = NULL;
    Node *convert = NULL;
    Node *ready = NULL;
    Node *result = NULL;
    s21_parser(input_str, &input);
    convert_stack(input, &convert);
    pol_notation(convert, &ready);
    convert_stack(ready, &result);
    if (strchr(input_str, 'x') != NULL) {
      *res = calculate_x(&result, X, &error);
    } else {
      *res = calculation(&result, &error);
    }
  } else
    error = 1;

  return error;
}

double calc_operation(double val1, double val2, char operator, int * error) {
  double res = 0;
  if (operator== '+')
    res = val1 + val2;
  else if (operator== '-')
    res = val1 - val2;
  else if (operator== '*')
    res = val1 * val2;
  else if (operator== '/') {
    if (val2 == 0)
      *error = 1;
    else
      res = val1 / val2;
  } else if (operator== '^')
    res = pow(val1, val2);
  else if (operator== 'm') {
    if (val2 == 0)
      *error = 1;
    else
      res = fmod(val1, val2);
  }
  return res;
}

double calc_function(double val, char func, int *error) {
  double res = 0;
  if (func == 's')
    res = sin(val);
  else if (func == 'c')
    res = cos(val);
  else if (func == 't')
    res = tan(val);
  else if (func == '1') {
    if (val < -1 || val > 1)
      *error = 1;
    else
      res = acos(val);
  } else if (func == '2') {
    if (val < -1 || val > 1)
      *error = 1;
    else
      res = asin(val);
  } else if (func == '3')
    res = atan(val);
  else if (func == 'q') {
    if (val < 0)
      *error = 1;
    else
      res = sqrt(val);
  } else if (func == 'n') {
    if (val < 0)
      *error = 1;
    else
      res = log(val);
  } else if (func == 'l') {
    if (val < 0)
      *error = 1;
    else
      res = log10(val);
  }
  return res;
}

double calculation(Node **list, int *error) {
  double numbers[130] = {0};
  int i = 0;
  for (Node *p = *list; !(*error) && p != NULL; p = p->next) {
    if (!(*error) && p->priority == 0) {
      numbers[i] = p->value;
      i++;
    } else if (!(*error) && p->priority == 4) {
      numbers[i - 1] = calc_function(numbers[i - 1], p->type, error);
    } else if (!(*error) && strchr(OPERATORS, p->type) != NULL) {
      numbers[i - 2] =
          calc_operation(numbers[i - 2], numbers[i - 1], p->type, error);
      i--;
    }
  }
  if (*list != NULL) clear_stack(list);
  return numbers[0];
}

double calculate_x(Node **list, double X, int *error) {
  double res = 0;
  for (Node *p = *list; !(*error) && p != NULL; p = p->next) {
    if (p->type == 'x') p->value = X;
  }
  if (!(*error)) res = calculation(list, error);
  return res;
}