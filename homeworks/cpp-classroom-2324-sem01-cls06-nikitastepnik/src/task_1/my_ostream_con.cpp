#pragma once

#include "my_ostream_con.hpp"

#include <iostream>
#include <string>

namespace cls_06 {
    class my_ostream_con : public my_ostream {
    public:
        my_ostream& operator<<(int value) override {
            std::cout << value;
            return *this;
        }

        my_ostream& operator<<(double value) override {
            std::cout << value;
            return *this;
        }

        my_ostream& operator<<(const std::string& value) override {
            std::cout << value;
            return *this;
        }
    };

}
