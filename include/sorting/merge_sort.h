#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "sort_common.h"

    extern sort_result_t generic_merge_sort(
        void* arr,
        size_t arr_len,
        size_t element_size,
        compare_func_t cmp,
        sort_stats_t* stats
    );



#ifdef __cplusplus
}
#endif
#endif
