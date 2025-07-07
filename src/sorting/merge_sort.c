#include <stdlib.h>
#include <stdio.h>
#include "sorting/merge_sort.h"

#define INDEX_OF(start_ptr, element_size, index) \
    ((char *)(start_ptr) + ((index) * (element_size)))

static sort_result_t internal_merge_sort(
    void *arr,
    size_t left,
    size_t right,
    size_t element_size,
    compare_func_t cmp);

static sort_result_t merge(
    void *arr,
    size_t left,
    size_t mid,
    size_t right,
    size_t element_size,
    compare_func_t cmp);

sort_result_t generic_merge_sort(
    void *arr,
    size_t arr_len,
    size_t element_size,
    compare_func_t cmp)
{
    if (arr == NULL || NULL == cmp)
    {
        return SORT_ERROR_NULL_POINTER;
    }
    if (arr_len <= 1)
    {
        return SORT_SUCCESS;
    }
    if (element_size == 0)
    {
        return SORT_ERROR_INVALID_ELEMENT_SIZE;
    }
    return internal_merge_sort(arr, 0, arr_len - 1, element_size, cmp);
}

static sort_result_t internal_merge_sort(
    void *arr,
    size_t left,
    size_t right,
    size_t element_size,
    compare_func_t cmp)
{
    if (left < right)
    {
        size_t mid = left + (right - left) / 2;

        sort_result_t res = internal_merge_sort(arr, left, mid, element_size, cmp);
        if (res != SORT_SUCCESS)
            return res;

        res = internal_merge_sort(arr, mid + 1, right, element_size, cmp);
        if (res != SORT_SUCCESS)
            return res;

        return merge(arr, left, mid, right, element_size, cmp);
    }
    return SORT_SUCCESS;
}

static sort_result_t merge(
    void *arr,
    size_t left,
    size_t mid,
    size_t right,
    size_t element_size,
    compare_func_t cmp)
{
    size_t size_l = mid - left + 1;
    size_t size_r = right - mid;

    void *left_arr = malloc(size_l * element_size);
    void *right_arr = malloc(size_r * element_size);
    if (left_arr == NULL || right_arr == NULL)
    {
        if (left_arr)
            free(left_arr);
        if (right_arr)
            free(right_arr);
        return SORT_ERROR_ALLOCATION_FAILED;
    }
    memcpy(left_arr, INDEX_OF(arr, element_size, left), size_l * element_size);
    memcpy(right_arr, INDEX_OF(arr, element_size, mid + 1), size_r * element_size);

    size_t i = 0, j = 0, k = left;
    while (i < size_l && j < size_r)
    {
        if (cmp(INDEX_OF(left_arr, element_size, i), INDEX_OF(right_arr, element_size, j)) <= 0)
        {
            memcpy(INDEX_OF(arr, element_size, k), INDEX_OF(left_arr, element_size, i), element_size);
            i++;
            k++;
        }
        else
        {
            memcpy(INDEX_OF(arr, element_size, k), INDEX_OF(right_arr, element_size, j), element_size);
            j++;
            k++;
        }
    }

    while (i < size_l)
    {
        memcpy(INDEX_OF(arr, element_size, k), INDEX_OF(left_arr, element_size, i), element_size);
        i++;
        k++;
    }
    while (j < size_r)
    {
        memcpy(INDEX_OF(arr, element_size, k), INDEX_OF(right_arr, element_size, j), element_size);
        j++;
        k++;
    }
    free(left_arr);
    free(right_arr);
    return SORT_SUCCESS;
}

#undef INDEX_OF