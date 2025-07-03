// #include <stdlib.h>
// #include "sorting/merge_sort.h"


// static void merge(void *arr[], size_t left, size_t mid, size_t right, generic_compare_func_t cmp, sort_stats_t *stats);

// sort_result_t generic_merge_sort(void *arrp[], size_t len, generic_compare_func_t cmp, sort_stats_t *stats) {
//     return SORT_SUCCESS;
// }


// static void merge(void *arr[], size_t left, size_t mid, size_t right, generic_compare_func_t cmp, sort_stats_t *stats) {
//     #define LEFT_INDEX(i) (left + i)
//     #define RIGHT_INDEX(i) (mid + 1 + i)
    
//     size_t left_size = mid - left + 1;
//     size_t right_size = right - mid;

//     void **left_arr = malloc(left_size * sizeof(void *));
//     void **right_arr = malloc(right_size * sizeof(void *));

//     if (left_arr == NULL || right_arr == NULL) {
//         free(left_arr);
//         free(right_arr);
//         return SORT_ERROR_ALLOCATION_FAILED;
//     }
    
//     for (size_t i = 0; i < left_size; i++) {
//         left_arr[i] = arr[LEFT_INDEX(i)];
//     }
//     for (size_t i = 0; i < right_size; i++) {
//         right_arr[i] = arr[RIGHT_INDEX(i)];
//     }

//     size_t i =0, j = 0;
//     for (; i < left_size && j < right_size;) {
//         INCRE_COMPARITIONS(stats)
//         if (cmp(left_arr[i], right_arr[j]) <= 0) {
//             arr[LEFT_INDEX(i + j)] = left_arr[i];
//             INCRE_MOVEMENTS(stats);
//             i++;
//         } else {
//             arr[LEFT_INDEX(i + j)] = right_arr[j];
//             INCRE_MOVEMENTS(stats);
//             j++;
//         }
//     }

//     for (; i < left_size; i++) {
//         arr[LEFT_INDEX(i + j)] = left_arr[i];
//         INCRE_MOVEMENTS(stats);
//     }

//     for (; j < right_size; j++) {
//         arr[LEFT_INDEX(i + j)] = right_arr[j];
//         INCRE_MOVEMENTS(stats);
//     }


//     free(left_arr);
//     free(right_arr);

//     #undef LEFT_INDEX
//     #undef RIGHT_INDEX
// }