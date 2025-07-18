/**
 * @file test_insertion_sort.cpp
 * @brief Google Test测试用例 - 插入排序算法
 * @author C Programming Expert
 * @date 2025-06-26
 * @version 1.0
 */

#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <algorithm>
#include <string>

#include "sorting/insertion_sort.h"
#include "sorting/sort_common.h"
#include "util/test_data_util.h"
#include "test_config.h" // 包含测试配置文件


class InsertionSortTest : public ::testing::Test, public TestDataUtil
{
protected:
    InsertionSortTest() : TestDataUtil(TEST_DATA_SIZE) {}
    void SetUp() override
    {
    }

    void TearDown() override
    {
        // 清理资源
    }
};

/* ============================================================================
 * 基础功能测试
 * ============================================================================ */

TEST_F(InsertionSortTest, NullPointerHandling)
{

    // 测试空指针处理
    EXPECT_EQ(generic_insertion_sort(nullptr, 0, 0, compare_integers),
              SORT_ERROR_NULL_POINTER);

    auto shuffled_vector = get_shuffled_int_vector();
    auto arr = get_vector_data_ptr_arr(shuffled_vector);
    EXPECT_EQ(generic_insertion_sort((void **)arr, 10, sizeof(int), nullptr),
              SORT_ERROR_NULL_POINTER);
    delete[] arr;
}

TEST_F(InsertionSortTest, EmptyArrayHandling)
{
    auto shuffled_vector = get_shuffled_int_vector();
    auto arr = get_vector_data_ptr_arr(shuffled_vector);

    // 测试空数组处理
    sort_result_t result = generic_insertion_sort((void **)(arr), 0, sizeof(int), compare_integers);
    EXPECT_EQ(result, SORT_SUCCESS);
    delete[] arr;
}

TEST_F(InsertionSortTest, SingleElementArray)
{
    std::vector<int> single_element = {42};
    std::vector<void *> ptr_array = {&single_element[0]};

    sort_result_t result = generic_insertion_sort(ptr_array.data(),
                                                  ptr_array.size(),
                                                  sizeof(int),
                                                  compare_integers);
    EXPECT_EQ(result, SORT_SUCCESS);
}

// TEST_F(InsertionSortTest, BinaryInsertionSort)
// {
//     auto shuffled_vector = get_shuffled_int_vector();
//     std::vector<void *> ptr_vector;
//     for (auto &elem : shuffled_vector) ptr_vector.push_back(static_cast<void *>(&elem));
//     sort_result_t result = generic_insertion_sort_with_binary_search(ptr_vector.data(),
//                                                                      ptr_vector.size(),
//                                                                      sizeof(int),
//                                                                      compare_integers);
//     EXPECT_EQ(result, SORT_SUCCESS);

//     // 检查通过指针排序后的结果是否正确
//     EXPECT_TRUE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled_vector.begin()));
// }
