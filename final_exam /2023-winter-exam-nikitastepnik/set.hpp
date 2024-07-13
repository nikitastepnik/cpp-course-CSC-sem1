#pragma once

#include <optional>
#include <cstddef>
#include <utility>
#include <tuple>
#include <functional>

namespace exam {
    int END_ELEM_FLAG = 0;
    int NOT_END_ELEM_FLAG = 1;

    template<typename T>
    class element {
    public:
        typedef T value_type;
        typedef const T& reference;
        typedef const T& const_reference;
        typedef const T* pointer;
        typedef const T* const_pointer;

        value_type _value;
        element<T> *right;
        element<T> *left;
        bool isEnd = false;

        element() : _value(NOT_END_ELEM_FLAG), right(nullptr), left(nullptr) {}

        explicit element(const T& val) : _value(val), right(nullptr), left(nullptr)  {}
        element(const T& val, element<T>* right, element<T>* left) : _value(val), right(right), left(left) {}
        explicit element(bool isEnd) : _value(END_ELEM_FLAG), right(nullptr), left(nullptr), isEnd(isEnd) {}

        element(const element &other) {
            if (this == &other) {
                return;
            }
            this->_value = other._value;
            this->right = other.right;
            this->left = other.left;
        }


        element &operator=(const element &other) {
            if (this != &other) {
                this->_value = other._value;
                this->right = other.right;
                this->left = other.left;
            }
            return *this;
        }
        bool operator==(const element& other) const {
            return (this->_value == other._value && this->right == other.right && this->left == other.left);
        }
        bool operator!=(const element& other) const {
            return !(this->_value == other._value && this->right == other.right && this->left == other.left);
        }
        const T& operator*() const {
            return _value;
        }
        ~element()=default;
    };

    template<typename T>
    class set {
    private:
        element<T> *head_;
        size_t countNodes = 0;
    public:
        set() : head_(nullptr) {}

        set(const set& otherSet) {
            if (this == &otherSet) {
                return;
            }
            head_ = otherSet.head_;
            countNodes = otherSet.countNodes;
        }

        set(set&& moveSet) noexcept : head_(moveSet.head_), countNodes(moveSet.countNodes) {
        }

        ~set() {
            clear();
        }

        void destroyTree(element<T>*& node) {
            if (node != nullptr) {
                destroyTree(node->left);
                destroyTree(node->right);
                delete node;
                node = nullptr;
            }
            countNodes = 0;
        }

        typedef T key_type;
        typedef T value_type;
        typedef element<T> element;
        typedef size_t size_type;

        [[nodiscard]] bool empty() const {
            return head_ == nullptr;
        }


        [[nodiscard]] size_type size() const {
            return countNodes;
        }

        element find(const T& key) const {
            element* current = head_;
            while (current != nullptr) {
                if (key < current->_value) {
                    current = current->left;
                } else if (current->_value < key) {
                    current = current->right;
                } else {
                    return element(current->_value, current->right, current->left);
                }
            }
            return end();
        }

        element end() const {
            return element(true);
        }

        std::pair<element&, bool>  insert(const T& key) {
            if (head_ == nullptr) {
                head_ = new element(key);
                countNodes += 1;
                return std::make_pair(std::ref(*head_), true);
            }
            element* current = head_;
            while (true) {
                if (key < current->_value) {
                    if (current->left == nullptr) {
                        current->left = new element(key);
                        countNodes += 1;
                        return std::make_pair(std::ref(*current->left), true);
                    }
                    current = current->left;
                } else if (current->_value < key) {
                    if (current->right == nullptr) {
                        current->right = new element(key);
                        countNodes += 1;
                        return std::make_pair(std::ref(*current->right), true);
                    }
                    current = current->right;
                } else {
                    return std::make_pair(std::ref(*current), false);

                }
            }
        }

        std::pair<element&, bool> insert(T&& key) {
            if (head_ == nullptr) {
                head_ = new element(std::move(key));
                countNodes += 1;
                return std::make_pair(std::ref(*head_), true);
            }
            element* current = head_;
            while (true) {
                if (key < current->_value) {
                    if (current->left == nullptr) {
                        current->left = new element(std::move(key));
                        countNodes += 1;
                        return std::make_pair(std::ref(*current->left), true);
                    }
                    current = current->left;
                } else if (current->_value < key) {
                    if (current->right == nullptr) {
                        current->right = new element(std::move(key));
                        countNodes += 1;
                        return std::make_pair(std::ref(*current->right), true);
                    }
                    current = current->right;
                } else {
                    return std::make_pair(std::ref(*current), false);
                }
            }
        }
    void clear() {
            destroyTree(head_);
        }

    static void swap(set &s1, set &s2) {
        std::swap(s1.head_, s2.head_);
        std::swap(s1.countNodes, s2.countNodes);
    }
    };
}