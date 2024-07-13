#pragma once
#include <cctype>

namespace cls08 {
    template <size_t N>
    struct FibonacciNumber {
    public:
        static constexpr size_t getFibNumber(size_t index) {
            if (index == 0 or index == 1) {
                return index;
            }
            return getFibNumber(index-1) + getFibNumber(index-2);
        }
        static const size_t value = getFibNumber(N);
    };
}