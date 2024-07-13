#include "int_vector.hpp"

void pushBack(IntVector& v, int value) {
    if (v.size == v.capacity_) {
        if (v.capacity_ == 0) {
            v.capacity_ = 1;
        } else {
            v.capacity_ *= 2;
        }
        int* oldData = v.data;
        v.data = new int[v.capacity_]();
        for (size_t i = 0; i < v.size; ++i) {
            v.data[i] = oldData[i];
        }
        delete[] oldData;
        oldData = nullptr;
    }
    v.data[v.size] = value;
    ++v.size;
}

void popBack(IntVector& v) {
    if (v.size == 0) {
        return;
    }
    v.size--;
    int* oldData = v.data;
    v.data = new int[v.size];
    for (size_t i = 0; i < v.size; ++i) {
        v.data[i] = oldData[i];
    }
    delete[] oldData;
    oldData = nullptr;
}

void deallocate(IntVector& v) {
    delete[] v.data;
    v.data = nullptr;
    v.size = 0;
    v.capacity_ = 0;
}