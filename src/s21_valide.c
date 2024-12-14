#include "s21_SmartCalc.h"

int is_valid_number(char *input_str, int i) {
  int is_valid = 1;
  if (input_str[i] == '0') {
    if (i == 0 && (strchr(NUMBERS, input_str[i + 1]) != NULL))
      is_valid = 0;
    else if ((i != 0 && strchr(NUMBERS, input_str[i - 1]) == NULL &&
              (strchr(NUMBERS, input_str[i + 1]) != NULL)))
      is_valid = 0;
  }
  if ((input_str[i + 1] != '\0' || input_str[i + 1] != '\n' ||
       input_str[i + 1] != '=') &&
      (input_str[i + 1] == '(' || input_str[i + 1] == 'x' ||
       strchr(FUNCS, input_str[i + 1]) != NULL)) {
    is_valid = 0;
  }
  return is_valid;
}

int is_valid_x(char *input_str, int i) {
  int is_valid = 1;
  if ((input_str[i + 1] != '\0' || input_str[i + 1] != '\n' ||
       input_str[i + 1] != '=') &&
      (input_str[i + 1] == '(' || input_str[i + 1] == 'x' ||
       strchr(FUNCS, input_str[i + 1]) != NULL ||
       strchr(NUMBERS, input_str[i + 1]) != NULL)) {
    is_valid = 0;
  }
  return is_valid;
}

int is_valid_dot(char *input_str, int i) {
  int is_valid = 1;
  int count_dot = 0;
  if (strchr(NUMBERS, input_str[i - 1]) == NULL ||
      strchr(NUMBERS, input_str[i + 1]) == NULL)
    is_valid = 0;
  else {
    int j = i + 1;
    while (strchr(NUMBERS, input_str[j]) != NULL && !count_dot) {
      if (input_str[j + 1] == '.') count_dot = 1;
      j++;
    }
    if (count_dot) is_valid = 0;
  }
  return is_valid;
}

int is_valid_operator(char *input_str, int *i) {
  int is_valid = 1;
  if (input_str[*i] == 'm') {
    char mod_str[5] = {0};
    char *ptr_ind = &input_str[*i];
    strncpy(mod_str, ptr_ind, 4);
    if (strstr(mod_str, "mod") == NULL)
      is_valid = 0;
    else {
      *i += 2;
      if (strchr(NOT_FIRST_ALL, input_str[*i + 1]) != NULL) is_valid = 0;
    }
  } else if (input_str[*i + 1] == '\0' || input_str[*i + 1] == '\n' ||
             input_str[*i + 1] == '=' ||
             strchr(NOT_FIRST_ALL, input_str[*i + 1]) != NULL) {
    is_valid = 0;
  }
  return is_valid;
}

int is_valid_brackets(char *input_str, int i, int *count_brackets) {
  int is_valid = 1;
  if (input_str[i] == '(') {
    if (input_str[i + 1] == '\0' || input_str[i + 1] == '\n' ||
        input_str[i + 1] == '=' ||
        strchr(NOT_FIRST, input_str[i + 1]) != NULL) {
      is_valid = 0;
    } else
      (*count_brackets)++;
  } else if (input_str[i] == ')') {
    if ((input_str[i + 1] != '\0' || input_str[i + 1] != '\n' ||
         input_str[i + 1] != '=') &&
        (strchr(NUMBERS, input_str[i + 1]) != NULL || input_str[i + 1] == '(' ||
         strchr(FUNCS, input_str[i + 1]) != NULL || input_str[i + 1] == '.' ||
         input_str[i + 1] == 'x')) {
      is_valid = 0;
    } else
      (*count_brackets)--;
  }
  return is_valid;
}

int is_valid_ln_log(char *func_str, int *i, int *count_brackets) {
  int is_valid = 1;
  if (strstr(func_str, "ln(") != NULL) {
    *i += 3;
    (*count_brackets)++;
  } else if (strstr(func_str, "log(") != NULL) {
    *i += 4;
    (*count_brackets)++;
  } else
    is_valid = 0;
  return is_valid;
}

int is_valid_sin_sqrt(char *func_str, int *i, int *count_brackets) {
  int is_valid = 1;
  if (strstr(func_str, "sin(") != NULL) {
    *i += 4;
    (*count_brackets)++;
  } else if (strstr(func_str, "sqrt(") != NULL) {
    *i += 5;
    (*count_brackets)++;
  } else
    is_valid = 0;
  return is_valid;
}

int is_valid_function(char *input_str, int *i, int *count_brackets) {
  int is_valid = 1;
  char func_str[6] = {0};
  char *ptr_ind = &input_str[*i];
  strncpy(func_str, ptr_ind, 5);
  if (input_str[*i] == 'c') {
    if (strstr(func_str, "cos(") == NULL)
      is_valid = 0;
    else {
      *i += 4;
      (*count_brackets)++;
    }
  } else if (input_str[*i] == 's') {
    is_valid = is_valid_sin_sqrt(func_str, i, count_brackets);
  } else if (input_str[*i] == 't') {
    if (strstr(func_str, "tan(") == NULL)
      is_valid = 0;
    else {
      *i += 4;
      (*count_brackets)++;
    }
  } else if (input_str[*i] == 'a') {
    if (strstr(func_str, "acos(") == NULL &&
        strstr(func_str, "asin(") == NULL && strstr(func_str, "atan(") == NULL)
      is_valid = 0;
    else {
      *i += 5;
      (*count_brackets)++;
    }
  } else if (input_str[*i] == 'l') {
    is_valid = is_valid_ln_log(func_str, i, count_brackets);
  }
  if (is_valid) {
    if (strchr(NOT_FIRST, input_str[*i]) == NULL)
      (*i)--;
    else
      is_valid = 0;
  }
  return is_valid;
}

int is_valid_symbol(char *input_str, int i) {
  int is_valid = 1;
  if (strchr(PERMITTED_SYMBOLS, input_str[i]) == NULL)
    is_valid = 0;
  else {
    if (strchr(NOT_FIRST, input_str[0]) != NULL) is_valid = 0;
  }
  return is_valid;
}

int s21_is_valide(char *input_str) {
  int is_valid = 1;
  int i = 0;
  int count_brackets = 0;
  while (input_str[i] != '=' && input_str[i] != '\n' && input_str[i] != '\0' &&
         is_valid) {
    is_valid = is_valid_symbol(input_str, i);
    if (is_valid) {
      if (strchr(NUMBERS, input_str[i]) != NULL)
        is_valid = is_valid_number(input_str, i);
      else if (input_str[i] == 'x') {
        is_valid = is_valid_x(input_str, i);
      } else if (input_str[i] == '.') {
        is_valid = is_valid_dot(input_str, i);
      }

      else if (strchr(OPERATORS, input_str[i]) != NULL) {
        is_valid = is_valid_operator(input_str, &i);
      } else if (strchr(BRACKETS, input_str[i]) != NULL) {
        is_valid = is_valid_brackets(input_str, i, &count_brackets);
      } else if (strchr(FUNCS_F, input_str[i]) != NULL) {
        is_valid = is_valid_function(input_str, &i, &count_brackets);
      }
    }
    if (is_valid) {
      i++;
    }
  }
  if (count_brackets != 0) is_valid = 0;
  return is_valid;
}
