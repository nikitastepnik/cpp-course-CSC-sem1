#include "vector.hpp"
#include "vector.hpp"

#include "../simple_test.h"
#include <utility>

struct IntHolder {
    static inline int do_throw_after = 100500;
    static inline int do_throw_on_value = 999;
    void check_n_throw() {
        if (do_throw_after-- <= 0 || v == do_throw_on_value) {
            throw std::exception();
        }
    }

    int v;

    explicit IntHolder(int i): v{i} {}

    IntHolder(const IntHolder& i): v{i.v} {
        check_n_throw();
    }
    IntHolder(IntHolder&& i): v{i.v} {
        check_n_throw();
    }
    IntHolder& operator=(const IntHolder& i) {
        v = i.v;
        check_n_throw();
        return *this;
    }
    IntHolder& operator=(IntHolder&& i) {
        v = i.v;
        check_n_throw();
        return *this;
    }
};


template <typename T>
using V = cls01::Vector<T>;

static_assert(noexcept(std::declval<V<int>>().push_back(std::declval<int>())));
static_assert(!noexcept(std::declval<V<IntHolder>>().push_back(std::declval<IntHolder>())));


TEST(vector, ints) {
    cls01::Vector<int> v(100, 42);
    EXPECT_EQ(100, v.size());

    v.push_back(24);
    v.push_back(24);

    EXPECT_EQ(102, v.size());
}

TEST(vector, int_holders_throwing_upon_pushing) {
    IntHolder::do_throw_after = 100500;
    IntHolder::do_throw_on_value = 999;

    cls01::Vector<IntHolder> v(100, IntHolder{42});
    EXPECT_EQ(100, v.size());

    EXPECT_THROW(v.push_back(IntHolder{999}), std::exception);
    EXPECT_EQ(100, v.size());
}

TEST(vector, int_holders_throwing_while_pushing) {
    IntHolder::do_throw_after = 100500;
    IntHolder::do_throw_on_value = 998;
    cls01::Vector<IntHolder> v(100, IntHolder{42});
    EXPECT_EQ(100, v.size());

    IntHolder::do_throw_after = 100 / 2;

    EXPECT_THROW(v.push_back(IntHolder{999 - 1}), std::exception);
    EXPECT_EQ(100, v.size());
}

TEST(vector, pop_back_sp) {
    using spi_t = std::shared_ptr<int>;
    spi_t sp{new int{24}};
    EXPECT_EQ(1, sp.use_count());

    {
        cls01::Vector<spi_t> v(100, sp);
        EXPECT_EQ(101, sp.use_count());

        v.pop_back();
        EXPECT_EQ(100, sp.use_count());
    }
    EXPECT_EQ(1, sp.use_count());
}

TESTING_MAIN()
