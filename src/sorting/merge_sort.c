#include <stdlib.h>
#include "sorting/merge_sort.h"

sort_result_t generic_merge_sort(void *arr[], size_t len, generic_compare_func_t cmp, sort_stats_t *stats)
{
    if (NULL == arr || NULL == cmp) {
        return SORT_ERROR_NULL_POINTER;
    }
    if (len <= 1) {
        return SORT_SUCCESS;
    }
}

static void merge(void * arr[], size_t l, size_t q, size_t r, sort_stats_t *stats) {
    size_t n1 = q - l + 1;
    size_t n2 = r - q;

    void **L = malloc(n1 * sizeof(void *));
    void **R = malloc(n2 * sizeof(void *));

    if (L == NULL || R == NULL) {
        free(L);
        free(R);
        return SORT_ERROR_ALLOCATION_FAILED;
    }

    for (size_t i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (size_t j = 0; j < n2; j++) {
        R[j] = arr[q + 1 + j];
    }

    size_t i = 0, j = 0, k = l;
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