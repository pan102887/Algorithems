#include "sorting/sort_common.h"

int compare_integers(const void *a, const void *b) {
  int int_a = *(const int *)a;
  int int_b = *(const int *)b;

  if (int_a < int_b)
    return -1;
  if (int_a > int_b)
    return 1;
  return 0;
}

int compare_strings(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}