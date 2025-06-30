#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "sorting/sort_common.h"

sort_result_t generic_insertion_sort(void *arr[], size_t len, generic_compare_func_t cmp, sort_stats_t *stats);
sort_result_t generic_insertion_sort_with_binary_search(void *arr[], size_t len, generic_compare_func_t cmp, sort_stats_t *stats);

#endif