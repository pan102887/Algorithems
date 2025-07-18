#include <gtest/gtest.h>

#include <random>
#include <algorithm>
#include <iterator>
#include "test_data_util.h"


class ShuffleTest : public testing::Test {
protected:
    std::vector<int> int_vector;
    std::vector<int> copied_int_vector;
    int int_array[20];
    int copied_int_array[20];

    void SetUp() override {
        for (int i = 0; i < 20; i++) {
            int_vector.push_back(i);
            int_array[i] = i;
            copied_int_array[i] = i;
        }
        std::copy(int_vector.begin(), int_vector.end(), std::back_inserter(copied_int_vector));
    }
    void TearDown() override {

    }
};


TEST_F(ShuffleTest, NotShuffleOriginalVector) {
    std::vector<int> original_vector = int_vector;
    auto shuffled = Shuffle<int>::shuffle_vector(int_vector);
    EXPECT_EQ(original_vector.size(), int_vector.size());
    EXPECT_FALSE(std::equal(original_vector.begin(), original_vector.end(), shuffled.begin()));
}


TEST_F(ShuffleTest, NotShuffleOriginalArray) {
    int original_array[20] {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19
    };
    int copied_int_array[20];
    std::copy(std::begin(original_array), std::end(original_array), std::begin(copied_int_array));
    auto shuffled = Shuffle<int>::shuffle_array(original_array);
    EXPECT_EQ(std::size(original_array), std::size(shuffled));
    EXPECT_FALSE(std::equal(std::begin(original_array), std::end(original_array), shuffled.begin()));
    EXPECT_TRUE(std::equal(std::begin(original_array), std::end(original_array), std::begin(copied_int_array), std::end(copied_int_array)));
}


TEST_F(ShuffleTest, ShuffleVector) {
    std::vector<int> shuffled = Shuffle<int>::shuffle_vector(int_vector);
    EXPECT_EQ(int_vector.size(), copied_int_vector.size());
    EXPECT_TRUE(std::equal(int_vector.begin(), int_vector.end(), copied_int_vector.begin()));

    EXPECT_EQ(shuffled.size(), int_vector.size());
    EXPECT_FALSE(std::equal(int_vector.begin(), int_vector.end(), shuffled.begin()));
    // shuffle method return a new vector instead modify on passed vector
    EXPECT_TRUE(std::equal(int_vector.begin(), int_vector.end(), copied_int_vector.begin()));
}

TEST_F(ShuffleTest, ShuffleArray) {
    auto shuffled = Shuffle<int>::shuffle_array(int_array);
    EXPECT_EQ(std::size(int_array), std::size(copied_int_array));
    EXPECT_TRUE(std::equal(std::begin(int_array), std::end(int_array), std::begin(copied_int_array), std::end(copied_int_array)));
    EXPECT_FALSE(std::equal(std::begin(int_array), std::end(int_array), shuffled.begin()));
}
