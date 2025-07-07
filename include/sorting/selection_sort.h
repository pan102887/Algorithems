#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H
#ifdef __cplusplus
extern "C" {
#endif
#include "sorting/sort_common.h"

    extern sort_result_t selection_sort(
        void* arr[],
        size_t len,
        compare_func_t cmp,
        swap_func_t swap_fun
    );

    extern sort_result_t generic_selection_sort(
        void* arr,
        size_t element_size,
        size_t len,
        compare_func_t cmp,
        swap_func_t swap_fun
    );

#ifdef __cplusplus
}
#endif

#endif // SELECTION_SORT_H