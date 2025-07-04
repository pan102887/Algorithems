#include <gtest/gtest.h>
#include "sorting/sort_common.h"
#include "util/test_data_util.h"



TEST(SortCommonTest, CompareIntegers) {
    int a = 5, b = 10;
    EXPECT_LT(compare_integers(&a, &b), 0);
    EXPECT_GT(compare_integers(&b, &a), 0);
    EXPECT_EQ(compare_integers(&a, &a), 0);
}

TEST(SortCommonTest, GenericSwap) {
    int a = 5, b = 10;
    GENERIC_SAMP_SIZE_SWAP(sizeof(int), &a, &b);
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 5);

    // Test with larger data type
    double x = 1.5, y = 2.5;
    GENERIC_SAMP_SIZE_SWAP(sizeof(double), &x, &y);
    EXPECT_EQ(x, 2.5);
    EXPECT_EQ(y, 1.5);

    
    

}