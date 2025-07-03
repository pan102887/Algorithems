#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "sort_common.h"
#include "common/common.h"

sort_result_t generic_selection_sort(void *arr[], size_t len, generic_compare_func_t cmp, sort_stats_t *stats);




#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SELECTION_SORT_H