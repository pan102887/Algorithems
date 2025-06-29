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
    EXPECT_EQ(insertion_sort_generic(nullptr, 10, compare_integers, &stats), 
              SORT_ERROR_NULL_POINTER);
    
    void** arr = reinterpret_cast<void**>(test_int_data.data());
    EXPECT_EQ(insertion_sort_generic(arr, 10, nullptr, &stats), 
              SORT_ERROR_NULL_POINTER);
}

TEST_F(InsertionSortTest, EmptyArrayHandling) {
    sort_stats_t stats;
    void** arr = reinterpret_cast<void**>(test_int_data.data());
    
    // 测试空数组处理
    EXPECT_EQ(insertion_sort_generic(arr, 0, compare_integers, &stats), 
              SORT_ERROR_INVALID_LENGTH);
}

TEST_F(InsertionSortTest, SingleElementArray) {
    std::vector<int> single_element = {42};
    std::vector<void*> ptr_array = {&single_element[0]};
    sort_stats_t stats;
    
    sort_result_t result = insertion_sort_generic(ptr_array.data(), 1, 
                                               compare_integers, &stats);
    
    EXPECT_EQ(result, SORT_SUCCESS);
    EXPECT_EQ(stats.comparisons, 0);
    EXPECT_EQ(stats.movements, 0);
    EXPECT_EQ(single_element[0], 42);
}

/* ============================================================================
 * 整数排序测试
 * ============================================================================ */

TEST_F(InsertionSortTest, IntegerSortingGeneric) {
    // 使用副本避免修改原始测试数据
    std::vector<int> test_copy = test_int_data;
    
    // 创建指针数组
    std::vector<void*> ptr_array;
    for (auto& val : test_copy) {
        ptr_array.push_back(&val);
    }
    
    sort_stats_t stats;
    sort_result_t result = insertion_sort_generic(ptr_array.data(), 
                                               ptr_array.size(), 
                                               compare_integers, &stats);
    
    EXPECT_EQ(result, SORT_SUCCESS);
    
    // 检查通过指针排序后的结果是否正确
    std::vector<int> sorted_values;
    for (void* ptr : ptr_array) {
        sorted_values.push_back(*(int*)ptr);
    }
    EXPECT_EQ(sorted_values, expected_int_sorted);
    
    EXPECT_GT(stats.comparisons, 0);
    EXPECT_GT(stats.movements, 0);
    EXPECT_GE(stats.time_elapsed_ms, 0.0);
}

TEST_F(InsertionSortTest, IntegerSortingOptimized) {
    // 使用副本避免修改原始测试数据
    std::vector<int> test_copy = test_int_data;
    
    sort_stats_t stats;
    sort_result_t result = insertion_sort_int_optimized(test_copy.data(), 
                                                     test_copy.size(), 
                                                     &stats);
    
    EXPECT_EQ(result, SORT_SUCCESS);
    EXPECT_EQ(test_copy, expected_int_sorted);
    EXPECT_GT(stats.comparisons, 0);
    EXPECT_GT(stats.movements, 0);
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
    sort_result_t result = binary_insertion_sort(ptr_array.data(), 
                                              ptr_array.size(), 
                                              compare_integers, &stats);
    
    EXPECT_EQ(result, SORT_SUCCESS);
    
    // 检查通过指针排序后的结果是否正确
    std::vector<int> sorted_values;
    for (void* ptr : ptr_array) {
        sorted_values.push_back(*(int*)ptr);
    }
    EXPECT_EQ(sorted_values, expected_int_sorted);
    
    EXPECT_GT(stats.comparisons, 0);
    EXPECT_GT(stats.movements, 0);
}

/* ============================================================================
 * 字符串排序测试
 * ============================================================================ */

TEST_F(InsertionSortTest, StringSorting) {
    // 创建可修改的字符串数组
    std::vector<std::string> test_copy = test_strings;
    std::vector<const char*> c_strings;
    std::vector<void*> ptr_array;
    
    for (const auto& str : test_copy) {
        c_strings.push_back(str.c_str());
    }
    
    for (auto& c_str : c_strings) {
        ptr_array.push_back(const_cast<void*>(reinterpret_cast<const void*>(&c_str)));
    }
    
    sort_stats_t stats;
    sort_result_t result = insertion_sort_generic(ptr_array.data(), 
                                               ptr_array.size(), 
                                               compare_strings, &stats);
    
    EXPECT_EQ(result, SORT_SUCCESS);
    
    // 验证排序结果 - 检查通过指针排序后的字符串顺序
    std::vector<std::string> sorted_strings;
    for (void* ptr : ptr_array) {
        const char** str_ptr = static_cast<const char**>(ptr);
        sorted_strings.push_back(std::string(*str_ptr));
    }
    
    for (size_t i = 0; i < expected_strings_sorted.size(); i++) {
        EXPECT_EQ(sorted_strings[i], expected_strings_sorted[i]);
    }
}

/* ============================================================================
 * 性能和压力测试
 * ============================================================================ */

TEST_F(InsertionSortTest, LargeArrayPerformance) {
    const size_t array_size = 1000;
    std::vector<int> large_array(array_size);
    
    // 生成随机数据
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 10000);
    
    for (auto& val : large_array) {
        val = dis(gen);
    }
    
    // 保存原始数据用于验证
    std::vector<int> expected = large_array;
    std::sort(expected.begin(), expected.end());
    
    sort_stats_t stats;
    sort_result_t result = insertion_sort_int_optimized(large_array.data(), 
                                                     large_array.size(), 
                                                     &stats);
    
    EXPECT_EQ(result, SORT_SUCCESS);
    EXPECT_EQ(large_array, expected);
    EXPECT_LT(stats.time_elapsed_ms, 1000.0); // 应该在1秒内完成
}

TEST_F(InsertionSortTest, AlreadySortedArray) {
    std::vector<int> sorted_array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> expected = sorted_array;
    
    sort_stats_t stats;
    sort_result_t result = insertion_sort_int_optimized(sorted_array.data(), 
                                                     sorted_array.size(), 
                                                     &stats);
    
    EXPECT_EQ(result, SORT_SUCCESS);
    EXPECT_EQ(sorted_array, expected);
    
    // 已排序数组应该有最少的比较次数（最好情况 O(n)）
    EXPECT_EQ(stats.comparisons, sorted_array.size() - 1);
    EXPECT_EQ(stats.movements, 0);
}

TEST_F(InsertionSortTest, ReverseSortedArray) {
    std::vector<int> reverse_array = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    sort_stats_t stats;
    sort_result_t result = insertion_sort_int_optimized(reverse_array.data(), 
                                                     reverse_array.size(), 
                                                     &stats);
    
    EXPECT_EQ(result, SORT_SUCCESS);
    EXPECT_EQ(reverse_array, expected);
    
    // 逆序数组应该有最多的比较和移动次数（最坏情况 O(n²)）
    size_t n = reverse_array.size();
    EXPECT_EQ(stats.comparisons, n * (n - 1) / 2);
    // 移动次数实际上是比较次数+插入次数，因为每次比较都伴随移动，最后还要插入
    EXPECT_GT(stats.movements, n * (n - 1) / 2);
}

/* ============================================================================
 * 算法比较测试
 * ============================================================================ */

TEST_F(InsertionSortTest, AlgorithmComparison) {
    const size_t array_size = 500;
    std::vector<int> test_array(array_size);
    
    // 生成随机数据
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 1000);
    
    for (auto& val : test_array) {
        val = dis(gen);
    }
    
    // 为不同算法准备副本
    std::vector<int> array1 = test_array;
    std::vector<int> array2 = test_array;
    std::vector<int> array3 = test_array;
    
    // 创建指针数组
    std::vector<void*> ptr_array1, ptr_array2;
    for (auto& val : array1) ptr_array1.push_back(&val);
    for (auto& val : array2) ptr_array2.push_back(&val);
    
    sort_stats_t stats1, stats2, stats3;
    
    // 测试通用插入排序
    sort_result_t result1 = insertion_sort_generic(ptr_array1.data(), 
                                                 ptr_array1.size(), 
                                                 compare_integers, &stats1);
    
    // 测试优化整数排序
    sort_result_t result2 = insertion_sort_int_optimized(array3.data(), 
                                                       array3.size(), &stats3);
    
    // 测试二分插入排序
    sort_result_t result3 = binary_insertion_sort(ptr_array2.data(), 
                                                ptr_array2.size(), 
                                                compare_integers, &stats2);
    
    // 验证所有算法都成功
    EXPECT_EQ(result1, SORT_SUCCESS);
    EXPECT_EQ(result2, SORT_SUCCESS);
    EXPECT_EQ(result3, SORT_SUCCESS);
    
    // 验证排序结果一致
    // 对于指针数组排序，我们需要检查排序后的指针指向的值
    std::vector<int> sorted_values1, sorted_values2;
    for (void* ptr : ptr_array1) {
        sorted_values1.push_back(*(int*)ptr);
    }
    for (void* ptr : ptr_array2) {
        sorted_values2.push_back(*(int*)ptr);
    }
    
    EXPECT_EQ(sorted_values1, array3);  // 通用排序与优化排序比较
    EXPECT_EQ(sorted_values2, array3);  // 二分排序与优化排序比较
    
    // 分析性能特性
    std::cout << "Performance Comparison (Array Size: " << array_size << "):\n";
    std::cout << "Generic Sort: " << stats1.comparisons << " comparisons, " 
              << stats1.movements << " movements, " 
              << stats1.time_elapsed_ms << " ms\n";
    std::cout << "Optimized Int Sort: " << stats3.comparisons << " comparisons, " 
              << stats3.movements << " movements, " 
              << stats3.time_elapsed_ms << " ms\n";
    std::cout << "Binary Insertion Sort: " << stats2.comparisons << " comparisons, " 
              << stats2.movements << " movements, " 
              << stats2.time_elapsed_ms << " ms\n";
    
    // 二分插入排序应该有更少的比较次数
    EXPECT_LT(stats2.comparisons, stats1.comparisons);
    // 但移动次数应该相同
    EXPECT_EQ(stats2.movements, stats1.movements);
}
