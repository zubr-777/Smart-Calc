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

int s21_reverse_polish_notation(stak **head, stak **result) {
  int status = 0;

  stak *out = NULL;
  token buffer_end;
  buffer_end.priority = -4;
  buffer_end.value = 0;
  push(&out, buffer_end);

  stak *operations = NULL;
  push(&operations, buffer_end);

  stak *buffer = NULL;
  stak *buffer_brackets = NULL;
  int priority = 0;

  do {
    buffer = pop(head);

    if (buffer->token.priority == 0 || buffer->token.priority == -1 ||
        buffer->token.priority == -2) {
      push(&out, buffer->token);
    } else {
      if (buffer->token.value == 1) {
        push(&operations, buffer->token);
        priority = 0;
      } else if (buffer->token.value == 2) {
        //  нашли закрывающую скобочку
        //  вынимаем все до открывающей скобочки
        while (operations->token.value != 1 && operations->token.priority != -4) {
          buffer_brackets = pop(&operations);
          push(&out, buffer_brackets->token);
          free(buffer_brackets);
        }
        if (operations->token.priority == -4) {
          return 1;
        }
        // вынимаем открывающую скобку
        buffer_brackets = pop(&operations);
        free(buffer_brackets);
        // обновляем приоритет
        priority = operations->token.priority;
      } else if (priority < buffer->token.priority) {
        // приоритет
        priority = buffer->token.priority;
        push(&operations, buffer->token);
      } else {
        //  вынимаем все операции имеющие приоритет выше этого
        while (operations->token.priority >= buffer->token.priority) {
          buffer_brackets = pop(&operations);
          push(&out, buffer_brackets->token);
          free(buffer_brackets);
        }
        // обновляем приоритет
        push(&operations, buffer->token);
        priority = operations->token.priority;
      }
    }

    free(buffer);

  } while ((*head)->token.priority != -4);

  free((*head));
  while (operations->token.priority != -4) {
    buffer_brackets = pop(&operations);
    push(&out, buffer_brackets->token);
    free(buffer_brackets);
  }
  free(operations);
  *result = out;
  return status;
}
