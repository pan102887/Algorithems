#include "sorting/merge_sort.h"
#include <gtest/gtest.h>
#include <random>
#include <vector>
#include <string>
#include <algorithm>

class MergeSortTest : public ::testing::Test {
protected:
    std::vector<int> test_int_data;
    std::vector<int> expected_int_data;

    std::vector<std::string> test_string_data;
    std::vector<std::string> expected_string_data;

    void SetUp() override {
        // 初始化测试数据
        test_int_data = {64, 34, 25, 12, 22, 11, 90};
        expected_int_data = {11, 12, 22, 25, 34, 64, 90};

        test_string_data = {"banana", "apple", "cherry", "date", "elderberry"};
        expected_string_data = {"apple", "banana", "cherry", "date", "elderberry"};
    }

    void TearDown() override {
    }
};
