#include <gtest/gtest.h>

#include "sorting/selection_sort.h"
#include "util/test_data_util.h"

#define TEST_DATA_SIZE 10000

class AnalysFileTest : public ::testing::Test, public TestDataUtil {
protected:
    
    AnalysFileTest() : TestDataUtil(TEST_DATA_SIZE) {}
    void SetUp() override {
        // 初始化测试数据
    }
    
    void TearDown() override {
        // 清理资源
    }
};

TEST(generic_selection_sort_test, NativeIntArrayTest) {
    int *sorted_int_arr = new int[TEST_DATA_SIZE];
    for (int i = 0; i < TEST_DATA_SIZE; i++) {
        sorted_int_arr[i] = i;
    }
    auto shuffled = Shuffle<int>::shuffle_array(sorted_int_arr, TEST_DATA_SIZE);
    int shuffled_int_arr[TEST_DATA_SIZE];
    for (size_t i = 0; i < shuffled.size(); i++) {
        shuffled_int_arr[i] = shuffled[i];
    }
    generic_selection_sort(shuffled_int_arr, TEST_DATA_SIZE, sizeof(int), compare_integers);
    EXPECT_TRUE(std::equal(sorted_int_arr, sorted_int_arr + TEST_DATA_SIZE, shuffled_int_arr));
    EXPECT_FALSE(std::equal(sorted_int_arr, sorted_int_arr + TEST_DATA_SIZE, shuffled.begin()));
    delete[] sorted_int_arr;
}