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

TEST_F(SelectionSortTest, EmptyArrayHandling) {
    sort_stats_t stats;
    void** arr = reinterpret_cast<void**>(int_data.data());

    EXPECT_EQ(generic_selection_sort(arr, 0, compare_integers, &stats), SORT_SUCCESS);
}

TEST_F(SelectionSortTest, SingleElementArray) {
    sort_stats_t stats;
    std::vector<int> single_element = {42};
    auto data = single_element.data();
    void **arr = new void*[single_element.size()];
    for(size_t i = 0; i < single_element.size(); i++) {
        arr[i] = &data[i];
    }

    EXPECT_EQ(generic_selection_sort(arr, 1, compare_integers, &stats), SORT_SUCCESS);
    EXPECT_EQ(single_element[0], 42);
    delete[] arr;
}

TEST_F(SelectionSortTest, SortFunctionality) {
    sort_stats_t stats;
    auto data = int_data.data();
    
    
    
    
    
    EXPECT_EQ(generic_selection_sort((void **)(data), int_data.size(), compare_integers, &stats), SORT_SUCCESS);
    
    for (size_t i = 0; i < int_data.size(); i++) {
        EXPECT_EQ(data[i], expected_data[i]);
    }
    
}


