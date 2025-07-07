#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "sorting/sort_common.h"

    extern sort_result_t generic_insertion_sort(void *ptr_arr[],
                                         size_t arr_len,
                                         size_t element_size,
                                         compare_func_t cmp);

    extern sort_result_t generic_insertion_sort_with_binary_search(
        void *ptr_arr[],
        size_t arr_len,
        size_t element_size,
        compare_func_t cmp);

#ifdef __cplusplus
}
#endif
#endif
