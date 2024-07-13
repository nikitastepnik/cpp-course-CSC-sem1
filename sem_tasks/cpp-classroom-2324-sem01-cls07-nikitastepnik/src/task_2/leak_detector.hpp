#include <cstddef>

void *operator new(size_t s);
void operator delete(void* addr) noexcept;

namespace cls07 {
    struct Meta {
        Meta *next;
        size_t size;
        bool isFree;
    };

    struct LeakDetector {
        void *GetNextLeakedAddress();

        // add code
    };
}