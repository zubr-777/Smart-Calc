#ifndef S21_SMART_CALC
#define S21_SMART_CALC

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct token {
  double value;
  int priority;
} token;

typedef struct stak {
  struct token token;
  struct stak *next;
} stak;

stak *pop(stak **head);
void push(stak **head, token token);
stak *invers_stak(stak **head, double src);
void free_stak(stak **head);

/**/

double s21_token(char *src, int start, int end);

int s21_check_unary_minus(char *src, int n);
int s21_check_unary_plus(char *src, int n);
int s21_check_acos(char *src, int n);
int s21_check_asin(char *src, int n);
int s21_check_atan(char *src, int n);
int s21_check_sin(char *src, int n);
int s21_check_cos(char *src, int n);
int s21_check_tan(char *src, int n);
int s21_check_sqrt(char *src, int n);
int s21_check_log(char *src, int n);
int s21_check_mod(char *src, int n);
int s21_check_ln(char *src, int n);

int s21_string_parsing(char *src, stak **head);
int s21_reverse_polish_notation(stak **head, stak **result);

int reverse_polish_notation_calculation(stak **head, double *result);
int unary_operations(token input, token number, token *out);
int binary_operations(token input, token number_1, token number_2, token *out);

int calc_function(char *string_function, double src, double *resalt);

#endif //  S21_SMART_CALC