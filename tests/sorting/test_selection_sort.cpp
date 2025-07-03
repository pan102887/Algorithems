#include <vector>
#include <gtest/gtest.h>
#include "sorting/selection_sort.h"
#include "test_data_util.h"



class SelectionSortTest : public testing::Test {
protected:
    std::vector<int> int_data;
    std::vector<int> expected_data;

    void SetUp() override {
        for (int i =0; i < 20; i++) {
            expected_data.push_back(i);
        }
        int_data = Shuffle<int>::shuffle_vector(expected_data);
    }
};

TEST_F(SelectionSortTest, NullPointerHandling) {
    sort_stats_t stats;
    EXPECT_EQ(generic_selection_sort(nullptr, 10, compare_integers, &stats), SORT_ERROR_NULL_POINTER);
    
    void** arr = reinterpret_cast<void**>(int_data.data());
    EXPECT_EQ(generic_selection_sort(arr, 10, nullptr, &stats), SORT_ERROR_NULL_POINTER);
}


