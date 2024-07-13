#include "concat.hpp"


char const *concat(
        char const a[],
        size_t a_size,
        char const b[],
        size_t b_size,
        size_t &concat_size
) {

    concat_size = a_size + b_size;
    char* concatRes = new char[concat_size];

    std::memcpy( concatRes, a, a_size);
    std::memcpy(concatRes+a_size, b, b_size);

    return concatRes;
}

