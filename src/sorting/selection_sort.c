#include "sorting/selection_sort.h"

sort_result_t generic_selection_sort(void *arr[], size_t len, generic_compare_func_t cmp, sort_stats_t *stats) {
    if (NULL == arr || NULL == cmp) {
        return SORT_ERROR_NULL_POINTER;
    }
    if (len <= 1) {
        return SORT_SUCCESS;
    }

    for (size_t i = 0; i < len - 1; i++) {

        void **min_elem = arr + i;
        for (size_t j = i; j < len; j++) {
            INCRE_COMPARITIONS(stats);
            if (cmp(*min_elem, arr[j]) > 0) {
                min_elem = arr + j;
            }
        }

        INCRE_COMPARITIONS(stats);
        if (min_elem != arr + i) {
            void *temp = arr[i];
            arr[i] = *min_elem;
            *min_elem = temp;
            INCRE_MOVEMENTS(stats);
        }
    }

    return SORT_SUCCESS;
}