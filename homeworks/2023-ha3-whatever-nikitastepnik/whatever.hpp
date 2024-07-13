// whatever.hpp - header-only solution goes into this file.
#pragma once

#include <string>

namespace utils {
    struct Interface {
    public:
        virtual ~Interface() {}
    };

    template<typename T>
    struct Impl : public Interface {
    public:
        T data;

        explicit Impl() : data(nullptr) {

        }

        explicit Impl(T data) : data(data) {

        }

        ~Impl() {

        }

    };

    class whatever {
    private:
    public:
        Interface *dataInterface;

        explicit whatever() : dataInterface(nullptr) {
        }

        template<typename T>
        explicit whatever(T data): dataInterface(new Impl(data)) {
        }


        explicit whatever(whatever &otherWhatever) {
            if (otherWhatever.dataInterface != nullptr) {
                auto implPtrInt = dynamic_cast<Impl<int> *>(otherWhatever.dataInterface);
                auto implPtrDouble = dynamic_cast<Impl<double> *>(otherWhatever.dataInterface);
                auto implPtrString = dynamic_cast<Impl<std::string> *>(otherWhatever.dataInterface);

                if (implPtrInt != nullptr) {
                    auto data = implPtrInt->data;
                    dataInterface = new Impl<int>(data);
                } else if (implPtrDouble != nullptr) {
                    auto data = implPtrDouble->data;
                    dataInterface = new Impl<double>(data);
                } else if (implPtrString != nullptr) {
                    auto data = implPtrString->data;
                    dataInterface = new Impl<std::string>(data);
                }
            } else {
                dataInterface = nullptr;
            }
        }

        whatever &operator=(const whatever &leftSideWhatever) {
            if (this != &leftSideWhatever) {
                delete dataInterface;
                if (leftSideWhatever.dataInterface != nullptr) {
                    auto implPtrInt = dynamic_cast<Impl<int> *>(leftSideWhatever.dataInterface);
                    auto implPtrDouble = dynamic_cast<Impl<double> *>(leftSideWhatever.dataInterface);
                    auto implPtrString = dynamic_cast<Impl<std::string> *>(leftSideWhatever.dataInterface);

                    if (implPtrInt != nullptr) {
                        auto data = implPtrInt->data;
                        dataInterface = new Impl<int>(data);
                    } else if (implPtrDouble != nullptr) {
                        auto data = implPtrDouble->data;
                        dataInterface = new Impl<double>(data);
                    } else if (implPtrString != nullptr) {
                        auto data = implPtrString->data;
                        dataInterface = new Impl<std::string>(data);
                    }
                }
            }
            return *this;
        }

        template<typename T>
        whatever &operator=(T leftSideVal) {
            if (dataInterface != nullptr) {
                *dataInterface = Impl<std::decay_t<T>>(leftSideVal);
            } else {
                dataInterface = new Impl<std::decay_t<T>>(leftSideVal);
            }
            return *this;
        }

        bool empty() {
            if (dataInterface != nullptr) {
                return false;
            }
            return true;
        }

        template<typename T>
        friend const T *whatever_cast(const whatever *obj);

        template<typename T>
        friend T *whatever_cast(whatever *obj);

        template<typename T>
        friend T whatever_cast(whatever &obj);

        template<typename T>
        friend T whatever_cast(const whatever &obj);

        ~whatever() {
            if (dataInterface != nullptr) {
                delete dataInterface;
                dataInterface = nullptr;
            }
        }
    };

    class bad_whatever_cast : public std::runtime_error {
    public:
        explicit bad_whatever_cast(const std::string &message) : std::runtime_error(message) {}
    };

    template<typename T>
    const T *whatever_cast(const whatever *obj) {
        if (obj->dataInterface == nullptr or dynamic_cast<Impl<std::decay_t<T>> *>(obj->dataInterface) == nullptr) {
            return nullptr;
        }
        if (dynamic_cast<Impl<std::decay_t<T>> *>(obj->dataInterface) != nullptr) {
            auto &data = dynamic_cast<Impl<std::decay_t<T>> *>(obj->dataInterface)->data;
            if (data) {
                return &data;
            }
        }
        throw bad_whatever_cast("bad cast");
    }


    template<typename T>
    T *whatever_cast(whatever *obj) {
        if (obj->dataInterface == nullptr or dynamic_cast<Impl<std::decay_t<T>> *>(obj->dataInterface) == nullptr) {
            return nullptr;
        }
        if (dynamic_cast<Impl<std::decay_t<T>> *>(obj->dataInterface) != nullptr) {
            auto &data = dynamic_cast<Impl<std::decay_t<T>> *>(obj->dataInterface)->data;
            if (data) {
                return &data;
            }
        }
        throw bad_whatever_cast("bad cast");
    }


    template<typename T>
    T whatever_cast(const whatever &obj) {
        if (dynamic_cast<Impl<std::decay_t<T>> *>(obj.dataInterface) != nullptr) {
            auto &data = dynamic_cast<Impl<std::decay_t<T>> *>(obj.dataInterface)->data;
            if (data) {
                return dynamic_cast<Impl<std::decay_t<T>> *>(obj.dataInterface)->data;
            }
        }
        throw bad_whatever_cast("bad cast");
    }


    template<typename T>
    T whatever_cast(whatever &obj) {
        if (dynamic_cast<Impl<std::decay_t<T>> *>(obj.dataInterface) != nullptr) {
            auto &data = dynamic_cast<Impl<std::decay_t<T>> *>(obj.dataInterface)->data;
            if (data) {
                return dynamic_cast<Impl<std::decay_t<T>> *>(obj.dataInterface)->data;
            }
        }
        throw bad_whatever_cast("bad cast");
    }

    void swap(whatever& leftWhatever, whatever& rightWhatever) {
        whatever tmp(leftWhatever);
        leftWhatever = rightWhatever;
        rightWhatever = tmp;
    }
}
