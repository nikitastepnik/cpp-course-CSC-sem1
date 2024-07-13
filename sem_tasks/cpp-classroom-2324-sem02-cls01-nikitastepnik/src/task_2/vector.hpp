#pragma once

#include <cstddef>
#include <new>
#include <type_traits>
#include <utility>
#include <memory>
#include <exception>

namespace cls01 {

    template<class T>
    class Vector {
        using size_type = std::size_t;
    private:
        T *begin_ = nullptr;
        T *end_ = nullptr;
        size_t capacity_ = 0;

        static T *create_storage(size_type count) {
            return static_cast<T*>(operator new(count * sizeof(T)));
        }

    public:
        Vector(size_type count, const T &value)
                : begin_(create_storage(count)), end_(begin_ + count), capacity_(count) {
            for (size_type i = 0; i < count; ++i) {
                new (&begin_[i]) T(value);
            }
        }

        ~Vector() {
            for (size_type i = 0; i < capacity_; ++i) {
                begin_[i].~T();
            }
            operator delete(begin_);
        }

        void push_back(const T &value) noexcept(std::is_nothrow_copy_constructible<T>::value) {
            T *newEnd = static_cast<T*>(operator new((capacity_ + 1) * sizeof(T)));
            try {
                for (size_type i = 0; i < capacity_; ++i) {
                    new (&newEnd[i]) T(std::move_if_noexcept(begin_[i]));
                    begin_[i].~T();
                }
                new (&newEnd[capacity_]) T(value);
            } catch (...) {
                for (size_type i = 0; i < capacity_; ++i) {
                    newEnd[i].~T();
                }
                operator delete(newEnd);
                throw;
            }
            operator delete(begin_);
            begin_ = newEnd;
            end_ = begin_ + capacity_;
            capacity_ += 1;
        }

        size_type size() const noexcept {
            return capacity_;
        }

        void pop_back() {
            if (capacity_ > 0) {
                end_[-1].~T();
                capacity_ -= 1;
                end_ -= 1;
            }
        }

        Vector(const Vector &) = delete;
        Vector(Vector &&) noexcept = delete;
        Vector &operator=(const Vector &) = delete;
        Vector &operator=(Vector &&) noexcept = delete;
    };

} // namespace cls01
