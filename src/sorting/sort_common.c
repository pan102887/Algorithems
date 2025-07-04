#include "sorting/sort_common.h"
#include <string.h>

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

int generic_int_cmp(const int * const a, const int * const b) {
  if (a == NULL || b == NULL) {
    return 0; // or handle error
  }
  return *a - *b;
}


void integers_swap(void * const a, void * const b) {
  GENERIC_SAMP_SIZE_SWAP(sizeof(int), a, b);
}

void incre_comparisons(sort_stats_t *stats)
{
  if (NULL == stats)
  {
    return;
  }
  stats->comparisons++;
}

void incre_movements(sort_stats_t *stats)
{
  if (NULL == stats)
  {
    return;
  }
  stats->movements++;
}
