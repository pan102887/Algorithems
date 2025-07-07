
#include <stdlib.h>
#include "sorting/sort_common.h"
#include "sorting/insertion_sort.h"


sort_result_t generic_insertion_sort(void *ptr_arr[],
                                     size_t arr_len,
                                     size_t element_size,
                                     compare_func_t cmp)
{
    if (NULL == ptr_arr || NULL == cmp)
    {
        return SORT_ERROR_NULL_POINTER;
    }
    if (arr_len == 0 || arr_len == 1)
    {
        return SORT_SUCCESS;
    }

    void *key = malloc(element_size);
    if (NULL == key)
    {
        return SORT_ERROR_ALLOCATION_FAILED;
    }

    for (size_t i = 1; i < arr_len; i++)
    {
        memcpy(key, ptr_arr[i], element_size);
        size_t j = i - 1;
        while (j > 0 && cmp(ptr_arr[j], key) > 0)
        {
            memcpy(ptr_arr[j + 1], ptr_arr[j], element_size);
            j--;
        }
        memcpy(ptr_arr[j + 1], key, element_size);
    }
    free(key);
    return SORT_SUCCESS;
}

sort_result_t generic_insertion_sort_with_binary_search(void *ptr_arr[],
                                                        size_t arr_len,
                                                        size_t element_size,
                                                        compare_func_t cmp)
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

    for (size_t i = 1; i < arr_len; i++)
    {
        memcpy(key, ptr_arr[i], element_size);
        int left = 0;
        int right = (int)i - 1;

        int mid;
        while (left <= right)
        {

            mid = left + (right - left) / 2;
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
            memcpy(ptr_arr[j], ptr_arr[j - 1], element_size);
        }
        memcpy(ptr_arr[left], key, element_size);
    }


    free(key);
    return SORT_SUCCESS;
}
