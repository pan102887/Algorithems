#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "sorting/shell_sort.h"
#include "util/test_data_util.h"
#include "test_config.h" // 包含测试配置文件


class ShellSortTest : public ::testing::Test, public TestDataUtil
{
protected:
    ShellSortTest() : TestDataUtil(TEST_DATA_SIZE) {} // 使用10000个元素的测试数据

    void SetUp() override
    {
        // 在每个测试之前执行的代码
    }

    void TearDown() override
    {
        // 在每个测试之后执行的代码
    }
};

TEST_F(ShellSortTest, NullPointerHandling)
{
    // 测试空指针处理
    ;
    EXPECT_EQ(generic_shell_sort(nullptr, 0, sizeof(int), compare_integers), SORT_SUCCESS);
}

TEST_F(ShellSortTest, EmptyArrayHandling)
{
    // 测试空数组处理
    std::vector<int> empty_vector;
    EXPECT_EQ(generic_shell_sort(empty_vector.data(), 0, sizeof(int), compare_integers), SORT_SUCCESS);
}


TEST_F(ShellSortTest, IntegerArrSortTest)
{
    // 测试整数数组排序
    auto shuffled = get_shuffled_int_vector();
    auto data = shuffled.data();
    generic_shell_sort(data, shuffled.size(), sizeof(int), compare_integers);
    EXPECT_TRUE(std::equal(shuffled.begin(), shuffled.end(), sorted_int_vector.begin()));
}