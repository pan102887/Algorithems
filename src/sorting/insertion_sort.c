
#include <stdlib.h>
#include "sorting/sort_common.h"
#include "sorting/insertion_sort.h"


sort_result_t generic_insertion_sort(void *ptr_arr[],
                                     size_t arr_len,
                                     size_t element_size,
                                     compare_func_t cmp,
                                     sort_stats_t *stats)
{
    INCRE_COMPARISONS(stats);
    if (NULL == ptr_arr || NULL == cmp)
    {
        return SORT_ERROR_NULL_POINTER;
    }
    INCRE_COMPARISONS(stats);
    if (arr_len == 0 || arr_len == 1)
    {
        return SORT_SUCCESS;
    }

    void *key = malloc(element_size);
    if (NULL == key)
    {
        return SORT_ERROR_ALLOCATION_FAILED;
    }
    INCRE_MEMORY_USED(stats, element_size);

    for (size_t i = 1; i < arr_len; i++)
    {
        memcpy(key, ptr_arr[i], element_size);
        size_t j = i - 1;
        INCRE_COMPARISONS(stats);
        while (j > 0 && cmp(ptr_arr[j], key) > 0)
        {
            INCRE_COMPARISONS(stats);
            memcpy(ptr_arr[j + 1], ptr_arr[j], element_size);
            j--;
        }
        INCRE_MOVEMENTS(stats);
        memcpy(ptr_arr[j + 1], key, element_size);
    }
    free(key);
    DECRE_MEMORY_USED(stats, element_size);
    return SORT_SUCCESS;
}

sort_result_t generic_insertion_sort_with_binary_search(void *ptr_arr[],
                                                        size_t arr_len,
                                                        size_t element_size,
                                                        compare_func_t cmp,
                                                        sort_stats_t *stats)
{

    if (NULL == ptr_arr || NULL == cmp)
    {
        return SORT_ERROR_NULL_POINTER;
    }

    if (arr_len <= 1)
    {
        return SORT_SUCCESS;
    }

    void *key = malloc(element_size);
    if (NULL == key)
    {
        return SORT_ERROR_ALLOCATION_FAILED;
    }
    INCRE_MEMORY_USED(stats, element_size);

    for (size_t i = 1; i < arr_len; i++)
    {
        memcpy(key, ptr_arr[i], element_size);
        int left = 0;
        int right = (int)i - 1;

        int mid;
        INCRE_COMPARISONS(stats);
        while (left <= right)
        {

            mid = left + (right - left) / 2;
            INCRE_COMPARISONS(stats);
            if (cmp(ptr_arr[mid], key) < 0)
            {
                // 如果中点的值比key小，则key应该在中点的右侧，所以将左界设置为mid + 1
                left = mid + 1;
            }
            else
            {
                // 如果重点的值大于等于key, 则key的插入位置应该在中点的左侧或者中点这，因此将右边界设置为mid
                right = mid - 1;
            }
        }

        for (int j = i; j > left; j--)
        {
            INCRE_MOVEMENTS(stats);
            memcpy(ptr_arr[j], ptr_arr[j - 1], element_size);
        }
        INCRE_MOVEMENTS(stats);
        memcpy(ptr_arr[left], key, element_size);
    }


    free(key);
    DECRE_MEMORY_USED(stats, element_size);
    return SORT_SUCCESS;
}
