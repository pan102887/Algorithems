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


class InsertionSortTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 初始化测试数据
        test_int_data = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 42};
        expected_int_sorted = {11, 12, 22, 25, 34, 42, 50, 64, 76, 88, 90};
        
        test_strings = {"banana", "apple", "cherry", "date", "elderberry", "fig", "grape"};
        expected_strings_sorted = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
    }

    void TearDown() override {
        // 清理资源
    }

    // 测试数据
    std::vector<int> test_int_data;
    std::vector<int> expected_int_sorted;
    std::vector<std::string> test_strings;
    std::vector<std::string> expected_strings_sorted;
};

/* ============================================================================
 * 基础功能测试
 * ============================================================================ */

TEST_F(InsertionSortTest, NullPointerHandling) {
    sort_stats_t stats;
    
    // 测试空指针处理
    EXPECT_EQ(generic_insertion_sort(nullptr, 10, compare_integers, &stats), 
              SORT_ERROR_NULL_POINTER);
    
    void** arr = reinterpret_cast<void**>(test_int_data.data());
    EXPECT_EQ(generic_insertion_sort(arr, 10, nullptr, &stats), 
              SORT_ERROR_NULL_POINTER);
}

TEST_F(InsertionSortTest, EmptyArrayHandling) {
    sort_stats_t stats;
    void** arr = reinterpret_cast<void**>(test_int_data.data());
    
    // 测试空数组处理
    EXPECT_EQ(generic_insertion_sort(arr, 0, compare_integers, &stats), 
              SORT_SUCCESS);
}

TEST_F(InsertionSortTest, SingleElementArray) {
    std::vector<int> single_element = {42};
    std::vector<void*> ptr_array = {&single_element[0]};
    sort_stats_t stats;
    
    sort_result_t result = generic_insertion_sort(ptr_array.data(), 1, 
                                               compare_integers, &stats);
    
    EXPECT_EQ(result, SORT_SUCCESS);
}

TEST_F(InsertionSortTest, BinaryInsertionSort) {
    // 使用副本避免修改原始测试数据
    std::vector<int> test_copy = test_int_data;
    
    // 创建指针数组
    std::vector<void*> ptr_array;
    for (auto& val : test_copy) {
        ptr_array.push_back(&val);
    }
    
    sort_stats_t stats;
    sort_result_t result = generic_insertion_sort_with_binary_search(ptr_array.data(), 
                                              ptr_array.size(), 
                                              compare_integers, &stats);
    
    EXPECT_EQ(result, SORT_SUCCESS);
    
    // 检查通过指针排序后的结果是否正确
    std::vector<int> sorted_values;
    for (void* ptr : ptr_array) {
        sorted_values.push_back(*(int*)ptr);
    }
    EXPECT_EQ(sorted_values, expected_int_sorted);
}
