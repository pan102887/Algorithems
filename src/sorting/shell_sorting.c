
#include "sorting/shell_sort.h"


sort_result_t generic_shell_sort(
    void *arr,
    size_t arr_len,
    size_t element_size,
    compare_func_t cmp
) {
    if (arr_len <= 1) {
        return SORT_SUCCESS;
    }
    if (NULL == arr || NULL == cmp) {
        return SORT_ERROR_NULL_POINTER;
    }

    if (element_size == 0) {
        return SORT_ERROR_INVALID_ELEMENT_SIZE;
    }
    size_t N = arr_len;
    size_t h = 1;
    while (h < N / 3) {
        h = 3 * h + 1; // 1, 4, 13, 40, 121, 364, ...
    }

    while (h >= 1) {
        for (size_t i = h; i < N; i++) {
            // j = 4 , 1
            for (size_t j = i; j >= h && cmp(INDEX_OF(arr, element_size, j), INDEX_OF(arr, element_size, j - h)) < 0; j -= h) {
                GENERIC_SAMP_SIZE_SWAP(element_size, INDEX_OF(arr, element_size, j), INDEX_OF(arr, element_size, j - h));
            }
        }
        h /= 3;
    }
    return SORT_SUCCESS;
}