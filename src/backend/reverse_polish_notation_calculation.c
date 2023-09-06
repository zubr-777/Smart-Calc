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

    Для чисел priority: для int - 0; для float - -1
    Для чисел value равно union
*/

int reverse_polish_notation_calculation(stak **head, double *result) {
  int status = 0;

  stak *out = NULL;
  token buffer_end;
  buffer_end.priority = -4;
  buffer_end.value = 0;
  push(&out, buffer_end);
  out->next = NULL;

  stak *buffer = NULL;
  stak *num_1 = NULL;
  stak *num_2 = NULL;

  do {
    buffer = pop(head);

    if (buffer->token.priority == -1) {
      push(&out, buffer->token);
    } else {
      if (!(out->token.priority == -1)) {
        // попытка применить оперцию к пустоте или другой операции
        if (buffer != NULL) {
          free(buffer);
        }
        if (num_1 != NULL) {
          free(num_1);
        }
        if (num_2 != NULL) {
          free(num_2);
        }
        free_stak(&out);
        free_stak(head);

        return 1;
      } else {
        num_1 = pop(&out);
        // проверяем унарная или бинарная операция
        if (buffer->token.priority == 5 || buffer->token.priority == 3) {
          // унарные операторы
          // смотрим какой оператор

          if (unary_operations(buffer->token, num_1->token, &buffer_end) == 1) {
            push(&out, buffer_end);
            if (num_1 != NULL) {
              free(num_1);
              num_1 = NULL;
            }
          } else {
            //  некорректная операция
            if (buffer != NULL) {
              free(buffer);
            }
            if (num_1 != NULL) {
              free(num_1);
              num_1 = NULL;
            }
            if (num_2 != NULL) {
              free(num_2);
              num_2 = NULL;
            }
            free_stak(&out);
            free_stak(head);
            return 2;
          }

        } else {
          // бинарные операторы
          // проверяем, что второе число для бинарной операции есть
          if (!(out->token.priority == -1)) {
            // ОЧИСТИТЬ OUT
            if (buffer != NULL) {
              free(buffer);
            }
            if (num_1 != NULL) {
              free(num_1);
              num_1 = NULL;
            }
            if (num_2 != NULL) {
              free(num_2);
              num_2 = NULL;
            }
            free_stak(&out);
            free_stak(head);
            return 1;
          } else {
            num_2 = pop(&out);
            // смотрим какой оператор
            if (binary_operations(buffer->token, num_1->token, num_2->token,
                                  &buffer_end) == 1) {
              push(&out, buffer_end);
              if (num_1 != NULL) {
                free(num_1);
                num_1 = NULL;
              }
              if (num_2 != NULL) {
                free(num_2);
                num_2 = NULL;
              }
            } else {
              if (buffer != NULL) {
                free(buffer);
              }
              if (num_1 != NULL) {
                free(num_1);
                num_1 = NULL;
              }
              if (num_2 != NULL) {
                free(num_2);
                num_2 = NULL;
              }
              free_stak(&out);
              free_stak(head);
              // некорректная операция
              return 2;
            }
          }
        }
      }
    }

    free(buffer);
  } while ((*head)->token.priority != -4);
  buffer = pop(&out);
  (*result) = (buffer->token.value);
  free(buffer);
  buffer = pop(head);
  free(buffer);
  buffer = pop(&out);
  free(buffer);
  free(out);
  return status;
}

int unary_operations(token input, token number, token *out) {
  if (input.value == 501) {
    // cos
    out->priority = -1;
    out->value = cos(number.value);
  } else if (input.value == 502) {
    // sin
    out->priority = -1;
    out->value = sin(number.value);
  } else if (input.value == 503) {
    // tan
    out->priority = -1;
    out->value = tan(number.value);
  } else if (input.value == 504) {
    // acos
    // -1 <= x <= 1
    out->priority = -1;
    if (number.value < -1 || number.value > 1) {
      return 0;
    }
    out->value = acos(number.value);
  } else if (input.value == 505) {
    // asin
    // -1 <= x <= 1
    out->priority = -1;
    if (number.value < -1 || number.value > 1) {
      return 0;
    }
    out->value = asin(number.value);
  } else if (input.value == 506) {
    // atan
    out->priority = -1;
    out->value = atan(number.value);
  } else if (input.value == 507) {
    // sqrt
    // x >= 0
    out->priority = -1;
    if (number.value < 0) {
      return 0;
    }
    out->value = sqrt(number.value);
  } else if (input.value == 508) {
    // ln
    // x > 0
    out->priority = -1;
    if (number.value <= 0) {
      return 0;
    }
    out->value = log(number.value);
  } else if (input.value == 509) {
    // log
    // x > 0
    out->priority = -1;
    if (number.value <= 0) {
      return 0;
    }
    out->value = log10(number.value);
  } else if (input.value == 301) {
    // унарный +
    out->priority = -1;
    out->value = number.value;
  } else if (input.value == 302) {
    // унарный -
    out->priority = -1;
    out->value = -number.value;
  } else {
    return 2;
  }
  return 1;
}

int binary_operations(token input, token number_2, token number_1, token *out) {
  if (input.value == 401) {
    // ^
    // если основание отрицательное, то нужно проверить,
    // что показатель не имеет дробной части (
    // 5.0 == 5, проверять, что у float нет дробной части)
    out->priority = -1;
    if (number_1.value < 0 && (number_2.value - (int)(number_2.value)) != 0) {
      return 0;
    }
    out->value = pow(number_1.value, number_2.value);
  } else if (input.value == 201) {
    // *
    out->priority = -1;
    out->value = number_1.value * number_2.value;
  } else if (input.value == 202) {
    // /
    // делитель НЕ 0
    out->priority = -1;
    if (number_2.value == 0) {
      return 0;
    }
    out->value = number_1.value / number_2.value;
  } else if (input.value == 203) {
    // mod
    // делитель НЕ 0
    out->priority = -1;
    if (number_2.value == 0) {
      return 0;
    }
    out->value = fmod(number_1.value, number_2.value);
  } else if (input.value == 101) {
    // +
    out->priority = -1;
    out->value = number_1.value + number_2.value;
  } else if (input.value == 102) {
    // -
    out->priority = -1;
    out->value = number_1.value - number_2.value;
  } else {
    return 2;
  }
  return 1;
}