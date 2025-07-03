#ifndef TEST_DATA_UTIL_H
#define TEST_DATA_UTIL_H
#include <vector>
#include <array>
#include <random>

template<typename T>
class Shuffle {
public:
    static std::vector<T> shuffle_vector(const std::vector<T>& vec) {
        std::vector<T> shuffled = vec;
        static std::random_device rd;
        static std::mt19937 g(rd());
        std::shuffle(shuffled.begin(), shuffled.end(), g);
        return shuffled;
    }

    template<size_t N>    
    static std::array<T, N> shuffle_array(const T (&arr)[N]) {
        std::array<T, N> shuffled;
        std::copy(std::begin(arr), std::end(arr), shuffled.begin());
        
        static std::random_device rd;
        static std::mt19937 g(rd());
        std::shuffle(shuffled.begin(), shuffled.end(), g);
        
        return shuffled;
    }
};


#endif