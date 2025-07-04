#include "sorting/selection_sort.h"


sort_result_t selection_sort(
    void* arr[],
    size_t len,
    compare_func_t cmp,
    swap_func_t swap_fun,
    sort_stats_t* stats
) {
    if (NULL == arr || NULL == cmp) {
        return SORT_ERROR_NULL_POINTER;
    }

    if (len == 0 || len == 1) {
        return SORT_SUCCESS;
    }

    for (size_t i = 0; i < len - 1; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < len; j++) {
            INCRE_COMPARITIONS(stats);
            if (cmp(arr[j], arr[min_index]) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap_fun(arr[i], arr[min_index]);
            INCRE_MOVEMENTS(stats);
        }
    }
    return SORT_SUCCESS;
}


sort_result_t generic_selection_sort(
    void* arr,
    size_t element_size,
    size_t len,
    compare_func_t cmp,
    swap_func_t swap_fun,
    sort_stats_t* stats
) {
    if (NULL == arr || NULL == cmp) {
        return SORT_ERROR_NULL_POINTER;
    }
    if (len == 0 || len == 1) {
        return SORT_SUCCESS;
    }
    
    for (size_t i = 0; i < len - 1; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < len; j++) {
            INCRE_COMPARITIONS(stats);
            if (cmp((char*)arr + j * element_size, (char*)arr + min_index * element_size) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap_fun((char*)arr + i * element_size, (char*)arr + min_index * element_size);
            INCRE_MOVEMENTS(stats);
        }
    }
    return SORT_SUCCESS;
}