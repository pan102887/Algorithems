
#include "sorting/merge_sort.h"
#include <stdlib.h>
#include <stdbool.h>

static bool print_debug = false;


static void merge(void *arr[], compare_func_t cmp, int p, int q, int r);

static void iner_merge_sort(void *arr[], size_t l, size_t r, compare_func_t cmp,
                            sort_stats_t *stats);

extern sort_result_t generic_merge_sort(void *arr[], size_t len,
                                        compare_func_t cmp,
                                        sort_stats_t *stats) {

  if (arr == NULL || cmp == NULL) {
    return SORT_ERROR_NULL_POINTER;
  }
  if (len == 0) {
    return SORT_ERROR_INVALID_LENGTH;
  }
  iner_merge_sort(arr, 0, (int)len - 1, cmp, stats);
  return SORT_SUCCESS;
}

extern void turn_on_merge_sort_debug(void) {
  print_debug = true;
}

static void merge(void *arr[], compare_func_t cmp, int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;

  void **L = malloc(n1 * sizeof(void *));
  void **R = malloc(n2 * sizeof(void *));

  for (int i = 0; i < n1; i++) {
    L[i] = arr[p + i];
  }
  for (int j = 0; j < n2; j++) {
    R[j] = arr[q + 1 + j];
  }

  int i = 0, j = 0, k = p;
  while (i < n1 && j < n2) {
    if (cmp(L[i], R[j]) <= 0) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }

  while (i < n1) {
    arr[k++] = L[i++];
  }
  while (j < n2) {
    arr[k++] = R[j++];
  }

  free(L);
  free(R);
}

static void iner_merge_sort(void *arr[], size_t l, size_t r, compare_func_t cmp,
                            sort_stats_t *stats) {
  size_t len = r - l + 1;
  if (len < 2) {
    return;
  }

  int mid = l + ((r - l) / 2);
  iner_merge_sort(arr, l, mid, cmp, stats);
  iner_merge_sort(arr, mid + 1, r, cmp, stats);
  merge(arr, cmp, l, mid, r);
}
