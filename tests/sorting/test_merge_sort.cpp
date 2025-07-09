#include <gtest/gtest.h>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
#include "sorting/merge_sort.h"
#include "util/test_data_util.h"
#include "test_config.h" // 包含测试配置文件

class MergeSortTest : public ::testing::Test, public TestDataUtil
{
protected:
    MergeSortTest() : TestDataUtil(TEST_DATA_SIZE) {}
    void SetUp() override
    {
    }

    void TearDown() override
    {
        // 清理资源
    }
};

TEST_F(MergeSortTest, NullPointerHandling)
{
    void **arr = nullptr;
    EXPECT_EQ(generic_merge_sort(arr, 1, sizeof(void *), compare_integers), SORT_ERROR_NULL_POINTER);
}

TEST_F(MergeSortTest, EmptyArrayHandling)
{
    void *arr[1];
    EXPECT_EQ(generic_merge_sort(arr, 1, sizeof(void *), compare_integers), SORT_SUCCESS);
}

TEST_F(MergeSortTest, IntegerArrSortTest)
{
    auto shuffled = get_shuffled_int_vector();
    auto data = shuffled.data();
    generic_merge_sort(data, shuffled.size(), sizeof(int), compare_integers);
    EXPECT_TRUE(std::equal(sorted_int_vector.begin(), sorted_int_vector.end(), shuffled.begin()));
}

TEST_F(MergeSortTest, IntegerBenchmakrTest)
{
    auto vec = get_random_int_vecotor<TEST_DATA_SIZE, 0, 1000000>();
    generic_merge_sort(vec.data(), vec.size(), sizeof(int), compare_integers);
}
