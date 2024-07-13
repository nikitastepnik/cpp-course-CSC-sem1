// maybe.hpp - header-only solution goes into this file.
#pragma once


#include <type_traits>


namespace control_03 {
    template <typename T>
    class maybe {
    private:
        alignas(T) char buffer[sizeof(T)];
        bool isValueSetted;
    public:
        maybe() : isValueSetted(false) {}

        maybe(const maybe<T>& other) : isValueSetted(other.isValueSetted) {
            if (isValueSetted) {
                new(buffer) T(other.value());
            }
        }

        maybe(maybe<T>&& other) : isValueSetted(other.isValueSetted) {
            if (isValueSetted) {
                new(buffer) T(std::move(other.value()));
            }
        }

        maybe(const T& value) : isValueSetted(true) {
            new(buffer) T(value);
        }

        maybe(T&& value) : isValueSetted(true) {
            new(buffer) T(std::move(value));
        }

        ~maybe() {
            reset();
        }

        void reset() {
            if (isValueSetted) {
                value().~T();
                isValueSetted = false;
            }
        }

        void reset(const T& value) {
            reset();
            new(buffer) T(std::move(value));
            isValueSetted = true;
        }

        T& value() {
            return *reinterpret_cast<T*>(buffer);
        }

        const T& value() const {
            return *reinterpret_cast<const T*>(buffer);
        }

        bool has_value() const {
            return isValueSetted;
        }

        maybe<T>& operator=(const maybe<T>& other) {
            if (this != &other) {
                reset(other.value());
            }
            return *this;
        }

        maybe<T>& operator=(maybe<T>&& other) {
            if (this != &other) {
                reset(std::move(other.value()));
            }
            return *this;
        }

        explicit operator bool() const {
            return isValueSetted;
        }
    };

}