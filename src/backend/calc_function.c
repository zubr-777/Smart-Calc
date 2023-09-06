#include "s21_smart_calc.h"

int calc_function(char *string_function, double src, double *resalt) {
  int status = 0;

  stak *stak_parsing_string_function;
  status = s21_string_parsing(string_function, &stak_parsing_string_function);
  stak *stak_function = NULL;
  //  0 - все хорошо
  //  1 - некорректный символ
  //  2 - количество открывающих и закрывающих скобок не совпадает
  if (status == 0) {
    stak_function = invers_stak(&stak_parsing_string_function, src);
    status = s21_reverse_polish_notation(&stak_function,
                                         &stak_parsing_string_function);
    if (status == 0) {
      stak_function = invers_stak(&stak_parsing_string_function, src);
      stak *buffer_pop = NULL;
      buffer_pop = pop(&stak_function);
      free(buffer_pop);
      double dest;
      status = reverse_polish_notation_calculation(&stak_function, &dest);
      *resalt = dest;
    }
  }
  return status;
}

