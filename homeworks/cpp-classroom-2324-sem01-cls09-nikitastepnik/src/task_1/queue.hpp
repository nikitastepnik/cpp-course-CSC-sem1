#pragma once

#include <cctype>
#include <typeinfo>
#include <queue>
#include <iterator>
#include <iostream>


namespace cls09 {
    template<typename T>
    class Node {
    public:
        T data;
        Node<T> *next;

        Node(const T &value) : data(value), next(nullptr) {
        }

        explicit Node(T &&movedNode) : data(std::move(movedNode)), next(nullptr) {
        }

    };

    template<typename T>
    class queue {
    private:
        Node<T> *head;
        Node<T> *tail;
        size_t queueSize;

    public:
        queue() : head(nullptr), tail(nullptr), queueSize(0) {}

        queue(const queue &other) : head(nullptr), tail(nullptr), queueSize(0) {
            Node<T> *current = other.head;
            try {
                while (current != nullptr) {
                    push(current->data);
                    current = current->next;
                }
            } catch (std::runtime_error &exc) {
                clear();
                throw exc;
            }

            queueSize = other.queueSize;
        }


        queue(queue &&movedQ) {
            head = movedQ.head;
            tail = movedQ.tail;
            queueSize = movedQ.queueSize;
            movedQ.head = nullptr;
            movedQ.tail = nullptr;
            movedQ.queueSize = 0;
        }


        queue &operator=(const queue &other) {
            if (this != &other) {
                std::queue<T> auxQ;
                try {
                    Node<T> *current = other.head;
                    while (current != nullptr) {
                        auxQ.push(current->data);
                        current = current->next;
                    }
                } catch (std::runtime_error &exc) {
                    throw exc;
                }
                clear();
                while (!auxQ.empty()) {
                    push(std::move(auxQ.front()));
                    auxQ.pop();
                }
            }
            return *this;
        }


        queue &operator=(queue &&movedQ) noexcept {
            clear();
            head = movedQ.head;
            tail = movedQ.tail;
            queueSize = movedQ.queueSize;
            movedQ.head = nullptr;
            movedQ.tail = nullptr;
            movedQ.queueSize = 0;
            return *this;
        }

        ~queue() {
            clear();
        }

        void push(const T &elem) {
            Node<T> *newNode = new Node<T>(elem);
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            queueSize++;
        }

        void push(T &&elem) {
            Node<T> *newNode = new Node<T>(std::move(elem));
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            queueSize++;
        }

        void pop() {
            if (head != nullptr) {
                Node<T> *temp = head;
                head = head->next;
                delete temp;
                queueSize--;
            }
        }

        T &front() {
            return head->data;
        }

        const T &front() const {
            return head->data;
        }

        size_t size() const {
            return queueSize;
        }

        void clear() {
            while (head != nullptr) {
                Node<T> *temp = head;
                head = head->next;
                delete temp;
            }
            tail = nullptr;
            queueSize = 0;
        }

        struct iterator {
            using iterator_category = std::random_access_iterator_tag;
            using value_type = int;
            using pointer = int*;
            using reference = int&;
        };

        class const_iterator {

        };

    };
}

namespace std {
    template <class T>
    struct iterator_traits {
        typedef typename T::value_type            value_type;
        typedef typename T::difference_type       difference_type;
        typedef typename T::iterator_category     iterator_category;
        typedef typename T::pointer               pointer;
        typedef typename T::reference             reference;
    };

