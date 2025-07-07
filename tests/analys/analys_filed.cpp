#include <gtest/gtest.h>

#include "sorting/merge_sort.h"
#include "util/test_data_util.h"

#define TEST_DATA_SIZE 1000000

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

TEST_F(AnalysFileTest, analysis) {
    auto vec = get_random_int_vecotor<TEST_DATA_SIZE, 0, 1000000>();
    generic_merge_sort(vec.data(), vec.size(), sizeof(int), compare_integers);
}