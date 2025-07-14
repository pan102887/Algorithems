#include <stdio.h>
#include "sorting/selection_sort.h"


sort_result_t selection_sort(
    void* arr,
    size_t arr_len,
    size_t element_size,
    compare_func_t cmp
) {
    if (NULL == arr || NULL == cmp) {
        return SORT_ERROR_NULL_POINTER;
    }

    if (arr_len == 0 || arr_len == 1) {
        return SORT_SUCCESS;
    }

    for (size_t i = 0; i < arr_len - 1; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < arr_len; j++) {
            if (cmp(INDEX_OF(arr, element_size, j), INDEX_OF(arr, element_size, min_index)) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            GENERIC_SAMP_SIZE_SWAP(element_size, INDEX_OF(arr, element_size, i), INDEX_OF(arr, element_size, min_index));
        }
    }
    return SORT_SUCCESS;
}


sort_result_t generic_selection_sort(
    void* arr,
    size_t arr_len,
    size_t element_size,
    compare_func_t cmp
) {
    if (NULL == arr || NULL == cmp) {
        return SORT_ERROR_NULL_POINTER;
    }
    if (arr_len == 0 || arr_len == 1) {
        return SORT_SUCCESS;
    }
    
    for (size_t i = 0; i < arr_len - 1; i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < arr_len; j++) {
            if (cmp(INDEX_OF(arr, element_size, j), INDEX_OF(arr, element_size, min_index)) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            GENERIC_SAMP_SIZE_SWAP(element_size,INDEX_OF(arr, element_size, i), INDEX_OF(arr, element_size, min_index));
        }
    }
    return SORT_SUCCESS;
}