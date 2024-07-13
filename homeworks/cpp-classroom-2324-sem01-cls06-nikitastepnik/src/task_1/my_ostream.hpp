#pragma once

namespace cls_06 {
    class my_ostream {
    public:
        virtual ~my_ostream() = default;
        virtual my_ostream& operator<<(int value) = 0;
        virtual my_ostream& operator<<(double value) = 0;
        virtual my_ostream& operator<<(const std::string& value) = 0;
    };
}
