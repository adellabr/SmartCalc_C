#include "s21_SmartCalc.h"

void push(Node **plist, double value, int priority, char type) {
  Node *p = (Node *)calloc(1, sizeof(Node));
  p->value = value;
  p->priority = priority;
  p->type = type;
  p->next = *plist;
  *plist = p;
}

void pop(Node **plist, double *value, int *priority, char *type) {
  Node *p = *plist;
  *value = p->value;
  *priority = p->priority;
  *type = p->type;
  *plist = p->next;
  free(p);
}

int peek(Node *plist, double *value, int *priority, char *type) {
  Node *p = plist;
  *value = p->value;
  *priority = p->priority;
  *type = p->type;
  return p->priority;
}

int is_empty_stack(Node *list) { return list == NULL; }

void convert_stack(Node *input, Node **convert) {
  double value = 0;
  int priority = 0;
  char type = 0;
  while (!is_empty_stack(input)) {
    pop(&input, &value, &priority, &type);
    push(convert, value, priority, type);
  }
  if (input != NULL) clear_stack(&input);
}

void clear_stack(Node **list) {
  if (*list != NULL) {
    for (Node *p = *list; p != NULL; p = p->next) {
      *list = p->next;
      free(p);
    }
    *list = NULL;
  }
}

void rpn_end_bracket(Node **convert, Node **ready, Node **support,
                     double *value, int *priority, char *type, double *value_s,
                     int *priority_s, char *type_s) {
  pop(convert, value, priority, type);
  peek(*support, value_s, priority_s, type_s);
  while (*type_s != '(') {
    pop(support, value_s, priority_s, type_s);
    push(ready, *value_s, *priority_s, *type_s);
    peek(*support, value_s, priority_s, type_s);
  }
  if (*type_s == '(') pop(support, value_s, priority_s, type_s);
  if (*support != NULL && peek(*support, value_s, priority_s, type_s) == 4) {
    pop(support, value_s, priority_s, type_s);
    push(ready, *value_s, *priority_s, *type_s);
  }
}

void pol_notation(Node *convert, Node **ready) {
  Node *support = NULL;
  double value = 0;
  int priority = 0;
  char type = 0;
  double value_s = 0;
  int priority_s = 0;
  char type_s = 0;
  while (!is_empty_stack(convert)) {
    peek(convert, &value, &priority, &type);
    if (type == '0' || type == 'x') {
      pop(&convert, &value, &priority, &type);
      push(ready, value, priority, type);
    } else if (priority == 4 || type == '(') {
      pop(&convert, &value, &priority, &type);
      push(&support, value, priority, type);
    } else if (strchr(OPERATORS, type)) {
      if (!is_empty_stack(support)) {
        while (!is_empty_stack(support) &&
               peek(support, &value_s, &priority_s, &type_s) >= priority) {
          pop(&support, &value_s, &priority_s, &type_s);
          push(ready, value_s, priority_s, type_s);
        }
      }
      pop(&convert, &value, &priority, &type);
      push(&support, value, priority, type);
    } else if (type == ')') {
      rpn_end_bracket(&convert, ready, &support, &value, &priority, &type,
                      &value_s, &priority_s, &type_s);
    }
  }
  while (!is_empty_stack(support)) {
    pop(&support, &value, &priority, &type);
    push(ready, value, priority, type);
  }
  if (support != NULL) clear_stack(&support);
  if (convert != NULL) clear_stack(&convert);
}
