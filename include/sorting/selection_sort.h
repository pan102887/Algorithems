#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H
#ifdef __cplusplus
extern "C" {
#endif
#include "sorting/sort_common.h"


    extern sort_result_t generic_selection_sort(
        void* arr,
        size_t arr_len,
        size_t element_size,
        compare_func_t cmp
    );

    extern sort_result_t selection_sort(
        void *arr,
        size_t arr_len,
        size_t element_size,
        compare_func_t cmp
    );

#ifdef __cplusplus
}
#endif

#endif // SELECTION_SORT_H