#include "sorting/sort_common.h"
#include <string.h>
#include <stdio.h>

int compare_integers(const void *const a, const void *const b)
{
  const int *ap = (const int *)a;
  const int *bp = (const int *)b;
  return *ap - *bp;
}
int compare_strings(const void *const a, const void *const b)
{
  return strcmp((const char *)a, (const char *)b);
}

void swap_integers(void *const a, void *const b)
{
  GENERIC_SAMP_SIZE_SWAP(sizeof(int), a, b);
}

void print_stats(const sort_stats_t *stats)
{
  if (NULL == stats)
  {
    return;
  }
  printf("element_size: %zu bytes\n"
         "array_length: %zu\n"
         "Comparisons: %zu\n"
         "Movements: %zu\n"
         "Time Spent: %.2f ms\n"
         "Additional Memory Used: %zu bytes\n"
         "Max Additional Memory Used: %zu bytes\n",
         stats->element_size,
         stats->array_length,
         stats->comparisons,
         stats->movements,
         stats->time_elapsed_ms,
         stats->memory_used,
         stats->max_mamory_used);
}