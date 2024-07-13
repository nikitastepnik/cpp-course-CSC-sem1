#include "worker.hpp"
#include "worker.hpp"

#include "../simple_test.h"


int foo() {
    return 42;
}

int throwing_foo() {
    throw std::exception();
}

TEST(worker, ok) {
    cls01::worker<int> w(foo);
    w.run();
    EXPECT_TRUE(w.called());
    EXPECT_FALSE(w.exception_caught());
    EXPECT_EQ(42, w.get());
}

TEST(worker, catching_inside) {
    cls01::worker<int> w(throwing_foo);
    w.run();
    EXPECT_TRUE(w.called());
    EXPECT_TRUE(w.exception_caught());
    EXPECT_NE(nullptr, w.get_exception());
}

TEST(worker, getting_result_before_run) {
    cls01::worker<int> w(foo);
    EXPECT_FALSE(w.called());

    EXPECT_THROW(w.get(), cls01::not_called_exception);
}

TESTING_MAIN()
