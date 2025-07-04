
#include "sorting/sort_common.h"
#include "sorting/insertion_sort.h"


sort_result_t generic_insertion_sort(void *arr[], size_t len, compare_func_t cmp, sort_stats_t* stats) {
    if (NULL == arr || NULL == cmp) {
        return SORT_ERROR_NULL_POINTER;
    }
    if (len == 0 || len == 1) {
        return SORT_SUCCESS;
    }
    for (size_t i = 1; i < len; i++) {
        void *key = arr[i];
        
        
        size_t j = i - 1;
        incre_comparisons(stats);
        while (j > 0 && cmp(arr[j], key) > 0) {
            incre_comparisons(stats);
            arr[j + 1] = arr[j];
            j--;
        }
        incre_movements(stats);
        arr[j + 1] = key;
    }
    return SORT_SUCCESS;
}


sort_result_t generic_insertion_sort_with_binary_search(void *arr[], size_t len, compare_func_t cmp, sort_stats_t *stats) {

    if (NULL == arr || NULL == cmp) {
        return SORT_ERROR_NULL_POINTER;
    }

    if (len <= 1) {
        return SORT_SUCCESS;
    }

    for (int i = 1; i < (int)len; i++) {
        void *key = arr[i];

        int left = 0;
        int right = i - 1;


        int mid;
        incre_comparisons(stats);
        while (left <= right) {

            mid = left + (right - left) / 2;
            incre_comparisons(stats);
            if (cmp(arr[mid], key) < 0) {
                // 如果中点的值比key小，则key应该在中点的右侧，所以将左界设置为mid + 1
                left = mid + 1;
            } else {
                // 如果重点的值大于等于key, 则key的插入位置应该在中点的左侧或者中点这，因此将右边界设置为mid
                right = mid - 1;
            }
        }

        
        for (int j = i; j > left; j--) {
            incre_movements(stats);
            arr[j] = arr[j - 1];
        }
        arr[left] = key;
    }
    return SORT_SUCCESS;
}
