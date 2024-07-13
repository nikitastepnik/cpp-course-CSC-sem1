#pragma once
#include "my_ostream.hpp"

namespace cls_06 {
    class my_ostream_con : public my_ostream {
    public:
        my_ostream& operator<<(int value) override;
        my_ostream& operator<<(double value) override;
        my_ostream& operator<<(const std::string& value) override;
    };

}
