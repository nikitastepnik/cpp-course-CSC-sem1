#include "custom_new_delete.hpp"
#include "expression.hpp"


MethodsCounter* globalCounts;

#define DEFINE_NEW_DEL(TYPE)                          \
    void* TYPE::operator new(size_t size) {         \
        if (globalCounts) { globalCounts->getNewCalls<TYPE>()++; }    \
        return ::operator new(size);                \
    }                                               \
                                                    \
    void TYPE::operator delete(void *p) {           \
        if (globalCounts) { globalCounts->getDeleteCalls<TYPE>()++; } \
        ::operator delete(p);                       \
    }


DEFINE_NEW_DEL(Val)
DEFINE_NEW_DEL(Add)
DEFINE_NEW_DEL(Mul)
//DEFINE_NEW_DEL(Var)
