#include "s21_smart_calc.h"

// возможные токены
/*
    | Описание функции                  | Функция   | Токен | priority | value |
    | --------------------------------- | --------- | ----- | -------- | ----- |
    | Вычисляет косинус                 | cos(x)    | cos   | 5        | 501   |
    | Вычисляет синус                   | sin(x)    | sin   | 5        | 502   |
    | Вычисляет тангенс                 | tan(x)    | tan   | 5        | 503   |
    | Вычисляет арккосинус              | acos(x)   | acos  | 5        | 504   |
    | Вычисляет арксинус                | asin(x)   | asin  | 5        | 505   |
    | Вычисляет арктангенс              | atan(x)   | atan  | 5        | 506   |
    | Вычисляет квадратный корень       | sqrt(x)   | sqrt  | 5        | 507   |
    | Вычисляет натуральный логарифм    | ln(x)     | ln    | 5        | 508   |
    | Вычисляет десятичный логарифм     | log(x)    | log   | 5        | 509   |
    | --------------------------------- | --------- | ----- | -------- | ----- |
    | Другие операции                   | Символ    | Токен | priority | value |
    | --------------------------------- | --------- | ----- | -------- | ----- |
    | Открывающая скобка                | (         | (     |     -3   | 001   |
    | Закрывающая скобка                | )         | )     |     -3   | 002   |
    | --------------------------------- | --------- | ----- | -------- | ----- |
    | Унарный плюс                      | +x        | #     | 3        | 301   |
    | Унарный минус                     | -y        | ~     | 3        | 302   |
    | --------------------------------- | --------- | ----- | -------- | ----- |
    | Возведение в степень              | x ^ y     | ^     | 4        | 401   |
    | --------------------------------- | --------- | ----- | -------- | ----- |
    | Умножени                          | x * y     | *     | 2        | 201   |
    | Деление                           | x / y     | /     | 2        | 202   |
    | Остаток от деления                | x mod y   | mod   | 2        | 203   |
    | --------------------------------- | --------- | ----- | -------- | ----- |
    | Бинарный плюс                     | x + y     | +     | 1        | 101   |
    | Бинарный минус                    | x - y     | -     | 1        | 102   |
    | --------------------------------- | --------- | ----- | -------- | ----- |
    | Символ остановы                   | --------- | ----- | -4       | 000   |
    | --------------------------------- | --------- | ----- | -------- | ----- |
    | x                                 | --------- | ----- | -2       | 000   |
    | --------------------------------- | --------- | ----- | -------- | ----- |

    Для чисел priority: для double - -1
    Для чисел value равно union
*/

/*
typedef union {
  int value_i;
  float value_fl;
} value;

typedef struct token {
    value value;
    int priority;
} token;

priority:

typedef struct stak {
        struct token token;
        struct stak *next;
} stak;
*/

stak *pop(stak **head) {
  stak *out;
  if ((*head) == NULL) {
    return NULL;
  }
  out = *head;
  *head = (*head)->next;
  return out;
}

void push(stak **head, token token) {
  stak *tmp = malloc(sizeof(stak));
  if (tmp != NULL) {
    tmp->next = *head;
    tmp->token = token;
    *head = tmp;
  }
}

stak *invers_stak(stak **head, double src) {
  if ((*head) == NULL) {
    return NULL;
  }
  stak *out = NULL;

  token buffer;
  buffer.priority = -4;
  buffer.value = 0;
  push(&out, buffer);

  stak *free_stak = NULL;
  while ((*head)->next != NULL) {
    free_stak = pop(head);
    if (free_stak->token.priority == -2) {
      free_stak->token.priority = -1;
      free_stak->token.value = src;
    }
    push(&out, free_stak->token);
    free(free_stak);
  }
  push(&out, (*head)->token);
  free(*head);
  return out;
}

void free_stak(stak **head) {
  if ((*head) != NULL) {
    stak *buffer = NULL;
    while ((*head)->next != NULL) {
      buffer = pop(head);
      free(buffer);
    }
    free(*head);
  }
}

// разбивает строку на токены
// на вход получает массив чаров, возвращает массив стрингов
// !!! функция не обрабатывает некорректный ввод

int s21_string_parsing(char *src, stak **head) {
  int status = 0;

  stak *src_stak = NULL;
  token buffer;

  // находим длину исходной строки
  size_t size_src = strlen(src);
  int count;

  int count_open_bracket = 0;
  int count_closing_bracket = 0;

  int dot_count = 0;

  for (int i = 0; i < (int)size_src; i++) {
    if (s21_check_unary_minus(src, i)) {
      buffer.priority = 3;
      buffer.value = 302;
    } else if (s21_check_unary_plus(src, i)) {
      buffer.priority = 3;
      buffer.value = 301;
    } else if (s21_check_acos(src, i)) {
      buffer.priority = 5;
      buffer.value = 504;
      i = i + 3;
    } else if (s21_check_asin(src, i)) {
      buffer.priority = 5;
      buffer.value = 505;
      i = i + 3;
    } else if (s21_check_atan(src, i)) {
      buffer.priority = 5;
      buffer.value = 506;
      i = i + 3;
    } else if (s21_check_sin(src, i)) {
      buffer.priority = 5;
      buffer.value = 502;
      i = i + 2;
    } else if (s21_check_sqrt(src, i)) {
      buffer.priority = 5;
      buffer.value = 507;
      i = i + 3;
    } else if (s21_check_ln(src, i)) {
      buffer.priority = 5;
      buffer.value = 508;
      i = i + 1;
    } else if (s21_check_log(src, i)) {
      buffer.priority = 5;
      buffer.value = 509;
      i = i + 2;
    } else if (s21_check_mod(src, i)) {
      buffer.priority = 2;
      buffer.value = 203;
      i = i + 2;
    } else if (s21_check_tan(src, i)) {
      buffer.priority = 5;
      buffer.value = 503;
      i = i + 2;
    } else if (s21_check_cos(src, i)) {
      buffer.priority = 5;
      buffer.value = 501;
      i = i + 2;
    } else if (strchr(".0123456789", src[i])) {
      count = i;
      dot_count = 0;
      while (count < (int)size_src && strchr(".0123456789", src[count])) {
        if ('.' == src[count]) {
          dot_count++;
        }
        count++;
      }
      if (dot_count > 1) {
        status = 1;
      } else { 
        buffer.priority = -1;
        buffer.value = s21_token(src, i, count - 1);
      }
      i = count - 1;
    } else if (src[i] == '(') {
      buffer.priority = -3;
      buffer.value = 1;
      count_open_bracket++;
    } else if (src[i] == ')') {
      buffer.priority = -3;
      buffer.value = 2;
      count_closing_bracket++;
    } else if (src[i] == '+') {
      buffer.priority = 1;
      buffer.value = 101;
    } else if (src[i] == '-') {
      buffer.priority = 1;
      buffer.value = 102;
    } else if (src[i] == '*') {
      buffer.priority = 2;
      buffer.value = 201;
    } else if (src[i] == '/') {
      buffer.priority = 2;
      buffer.value = 202;
    } else if (src[i] == '^') {
      buffer.priority = 4;
      buffer.value = 401;
    } else if (src[i] == 'x') {
      buffer.priority = -2;
      buffer.value = 0;
    } else if (!(src[i] == ' ' || src[i] == '\t')) {
      status = 1;
    }
    if (status == 0 && !(src[i] == ' ' || src[i] == '\t')) {
      push(&src_stak, buffer);
    }
  }
  if (count_open_bracket != count_closing_bracket) {
    status = 2;
  }
  (*head) = src_stak;
  return status;
}

double s21_token(char *src, int start, int end) {
  double buffer = 0;
  int flag_dot = start;
  while (src[flag_dot] != '.' && flag_dot != end) {
    flag_dot++;
  }
  int count = flag_dot == end ? flag_dot : flag_dot - 1;
  while (count >= start) {
    buffer += flag_dot == end
                  ? (src[count] - 48) * pow(10, flag_dot - count)
                  : (src[count] - 48) * pow(10, flag_dot - count - 1);
    count--;
  }
  if (flag_dot != end) {
    count = flag_dot + 1;
    while (count <= end) {
      buffer += (double)(src[count] - 48) / pow(10, count - flag_dot);
      count++;
    }
  }
  return buffer;
}

int s21_check_unary_minus(char *src, int n) {
  int status = 0;
  if (src[n] == '-') {
    int i = n - 1;
    for (; i >= 0 && status == 0; i--) {
      if (src[i] != ' ' && src[i] != '\t') {
        if (src[i] == '(') {
          status = 1;
        } else {
          i = -1;
        }
      }
    }
    if (i == 0 || i == -1) {
      status = 1;
    }
  }
  return status;
}

int s21_check_unary_plus(char *src, int n) {
  int status = 0;
  if (src[n] == '+') {
    int i = n - 1;
    for (; i >= 0 && status == 0; i--) {
      if (src[i] != ' ' && src[i] != '\t') {
        if (src[i] == '(') {
          status = 1;
        } else {
          i = -1;
        }
      }
    }
    if (i == 0 || i == -1) {
      status = 1;
    }
  }
  return status;
}

int s21_check_acos(char *src, int n) {
  int status = 0;
  size_t size_src = strlen(src);
  if (n + 3 < (int)size_src) {
    if (src[n] == 'a' && src[n + 1] == 'c' && src[n + 2] == 'o' &&
        src[n + 3] == 's') {
      status = 1;
    }
  }
  return status;
}

int s21_check_asin(char *src, int n) {
  int status = 0;
  size_t size_src = strlen(src);
  if (n + 3 < (int)size_src) {
    if (src[n] == 'a' && src[n + 1] == 's' && src[n + 2] == 'i' &&
        src[n + 3] == 'n') {
      status = 1;
    }
  }
  return status;
}

int s21_check_atan(char *src, int n) {
  int status = 0;
  size_t size_src = strlen(src);
  if (n + 3 < (int)size_src) {
    if (src[n] == 'a' && src[n + 1] == 't' && src[n + 2] == 'a' &&
        src[n + 3] == 'n') {
      status = 1;
    }
  }
  return status;
}

int s21_check_sin(char *src, int n) {
  int status = 0;
  size_t size_src = strlen(src);
  if (n + 2 < (int)size_src) {
    if (src[n] == 's' && src[n + 1] == 'i' && src[n + 2] == 'n') {
      status = 1;
    }
  }
  return status;
}

int s21_check_cos(char *src, int n) {
  int status = 0;
  size_t size_src = strlen(src);
  if (n + 2 < (int)size_src) {
    if (src[n] == 'c' && src[n + 1] == 'o' && src[n + 2] == 's') {
      status = 1;
    }
  }
  return status;
}

int s21_check_tan(char *src, int n) {
  int status = 0;
  size_t size_src = strlen(src);
  if (n + 2 < (int)size_src) {
    if (src[n] == 't' && src[n + 1] == 'a' && src[n + 2] == 'n') {
      status = 1;
    }
  }
  return status;
}

int s21_check_sqrt(char *src, int n) {
  int status = 0;
  size_t size_src = strlen(src);
  if (n + 3 < (int)size_src) {
    if (src[n] == 's' && src[n + 1] == 'q' && src[n + 2] == 'r' &&
        src[n + 3] == 't') {
      status = 1;
    }
  }
  return status;
}

int s21_check_log(char *src, int n) {
  int status = 0;
  size_t size_src = strlen(src);
  if (n + 2 < (int)size_src) {
    if (src[n] == 'l' && src[n + 1] == 'o' && src[n + 2] == 'g') {
      status = 1;
    }
  }
  return status;
}

int s21_check_mod(char *src, int n) {
  int status = 0;
  size_t size_src = strlen(src);
  if (n + 2 < (int)size_src) {
    if (src[n] == 'm' && src[n + 1] == 'o' && src[n + 2] == 'd') {
      status = 1;
    }
  }
  return status;
}

int s21_check_ln(char *src, int n) {
  int status = 0;
  size_t size_src = strlen(src);
  if (n + 1 < (int)size_src) {
    if (src[n] == 'l' && src[n + 1] == 'n') {
      status = 1;
    }
  }
  return status;
}
