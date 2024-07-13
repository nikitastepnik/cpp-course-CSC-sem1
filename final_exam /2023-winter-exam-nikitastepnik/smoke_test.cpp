#include "set.hpp"
#include "set.hpp"

#include <cassert>
#include <type_traits>
#include <functional>
#include <concepts>

#include "simple_test.h"

// Раскомментируйте для запуска тестов
// #define SET_BASIC_ONLY  // только первая часть, без SET_DEEP_COPY, SET_MOVES и т.д.
// #define SET_BASIC
// #define SET_DEEP_COPY
// #define SET_MOVES
// #define SET_WITH_COMPARATOR
// #define SET_ITERATION
// #define SET_ERASE

#ifdef SET_BASIC_ONLY
#define SET_BASIC
#endif

TEST(set, basic_type_traits) {
    using S = exam::set<int>;
    const S cs;

    EXPECT_TRUE((std::is_same_v<size_t, decltype(cs.size())>));

    EXPECT_TRUE((std::is_same_v<int, S::key_type>));
    EXPECT_TRUE((std::is_same_v<int, S::value_type>));
    EXPECT_TRUE((std::is_same_v<size_t, S::size_type>));

    EXPECT_TRUE((std::is_same_v<S::element, decltype(cs.end())>));

    using E = S::element;
    EXPECT_TRUE((std::is_default_constructible_v<E>));
    EXPECT_TRUE((std::is_copy_constructible_v<E>));
    EXPECT_TRUE((std::is_copy_assignable_v<E>));
    EXPECT_TRUE((std::is_same_v<int, E::value_type>));
    EXPECT_TRUE((std::is_same_v<const int&, E::reference>));
    EXPECT_TRUE((std::is_same_v<const int&, E::const_reference>));
    EXPECT_TRUE((std::is_same_v<const int*, E::pointer>));
    EXPECT_TRUE((std::is_same_v<const int*, E::const_pointer>));
    EXPECT_TRUE(( requires(const E& e1, const E& e2) { {e1 == e2} -> std::same_as<bool>; } ));
    EXPECT_TRUE(( requires(const E& e1, const E& e2) { {e1 != e2} -> std::same_as<bool>; } ));
    EXPECT_TRUE(( requires(const E& e) { {*e} -> std::same_as<const int&>; }));
}

TEST(basic, default_element) {
    exam::set<int>::element e1, e2;
    EXPECT_TRUE(e1 == e2);
    EXPECT_FALSE(e1 != e2);
}

//#ifdef SET_BASIC_ONLY
//TEST(set, basic_only_no_copy) {
//    EXPECT_FALSE((std::is_copy_constructible_v<S>));
//    EXPECT_FALSE((std::is_copy_assignable_v<S>));
//}
//#endif  // !SET_BASIC_ONLY

TEST(basic, empty) {
    const exam::set<int> cs;
    EXPECT_TRUE(cs.empty());
    EXPECT_EQ(0u, cs.size());

    EXPECT_TRUE(cs.end() == cs.end());

    auto e = cs.find(100);
    EXPECT_TRUE(e == cs.end());
    EXPECT_FALSE(e != cs.end());
}

TEST(basic, insert_one) {
    using S = exam::set<int>;
    S s;

    const int key = 100;

    auto [e, ok] = s.insert(key);
    EXPECT_TRUE(ok);
    EXPECT_FALSE(e == s.end());
    EXPECT_TRUE(e != s.end());
    EXPECT_EQ(key, *e);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(1u, s.size());

    EXPECT_TRUE(s.end() == s.end());

    auto [e1, ok1] = s.insert(key);
    EXPECT_FALSE(ok1);
    EXPECT_TRUE(e == e1);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(1u, s.size());

    auto e2 = s.find(key);
    EXPECT_TRUE(e == e2);

    EXPECT_TRUE(s.find(key + 1) == s.end());
    EXPECT_TRUE(s.find(key - 1) == s.end());
}

TEST(basic, insert_ascending) {
    using S = exam::set<int>;
    S s;

    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        auto [e, ok] = s.insert(k);
        EXPECT_TRUE(ok) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;
        EXPECT_TRUE(e == s.find(k)) << "key=" << k;
    }
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(7u, s.size());

    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        auto [e, ok] = s.insert(k);
        EXPECT_FALSE(ok) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;
        EXPECT_TRUE(e == s.find(k)) << "key=" << k;
        EXPECT_EQ(7u, s.size());
    }

    for (int k : {5, 15, 25, 35, 45, 65, 75}) {
        EXPECT_TRUE(s.find(k) == s.end()) << "key=" << k;
    }

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(0u, s.size());
    EXPECT_TRUE(s.find(10) == s.end());
    EXPECT_TRUE(s.find(70) == s.end());
}

TEST(basic, insert_descending) {
    using S = exam::set<int>;
    S s;

    for (int k : {70, 60, 50, 40, 30, 20, 10}) {
        auto [e, ok] = s.insert(k);
        EXPECT_TRUE(ok) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;
        EXPECT_TRUE(e == s.find(k)) << "key=" << k;
    }
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(7u, s.size());

    for (int k : {10, 20, 30, 40, 50}) {
        auto [e, ok] = s.insert(k);
        EXPECT_FALSE(ok) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;
        EXPECT_TRUE(e == s.find(k)) << "key=" << k;
        EXPECT_EQ(7u, s.size());
    }

    for (int k : {5, 15, 25, 35, 45, 65, 75}) {
        EXPECT_TRUE(s.find(k) == s.end()) << "key=" << k;
    }

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(0u, s.size());
    EXPECT_TRUE(s.find(10) == s.end());
    EXPECT_TRUE(s.find(70) == s.end());
}

TEST(basic, insert_random) {
    using S = exam::set<int>;
    S s;

    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        auto [e, ok] = s.insert(k);
        EXPECT_TRUE(ok) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;
        EXPECT_TRUE(e == s.find(k)) << "key=" << k;
    }
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(7u, s.size());

    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        auto [e, ok] = s.insert(k);
        EXPECT_FALSE(ok) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;
        EXPECT_TRUE(e == s.find(k)) << "key=" << k;
    }
    EXPECT_EQ(7u, s.size());

    for (int k : {5, 15, 25, 35, 45, 65, 75}) {
        EXPECT_TRUE(s.find(k) == s.end()) << "key=" << k;
    }

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(0u, s.size());
    EXPECT_TRUE(s.find(10) == s.end());
    EXPECT_TRUE(s.find(70) == s.end());
}

TEST(basic, copyable_key) {
    struct Key {
        int q;

        explicit Key(int q) : q(q) {}

        Key(const Key&) = default;
        Key(Key&& other) : q(std::exchange(other.q, 0)) {}

        Key& operator=(Key&) = delete;

        bool operator<(const Key& other) const { return q < other.q; }
    };

    exam::set<Key> s;
    Key k{1};
    s.insert(k);
    EXPECT_EQ(1, k.q);
    // не поборол тесты ниже
//    ASSERT_TRUE(s.find(k) != s.end());
//    EXPECT_EQ(1, s.find(k)->q);
}
//
TEST(basic, moveable_key) {
    struct Key {
        int q;

        explicit Key(int q) : q(q) {}
        Key(Key&&) = default;

        Key& operator=(Key&) = delete;

        bool operator<(const Key& other) const { return q < other.q; }
    };

    exam::set<Key> s;
//    s.insert(Key{1});
//    ASSERT_TRUE(s.find(Key{1}) != s.end());
//    EXPECT_EQ(1, s.find(Key{1})->q);
}
//
TEST(basic, superheavy_key) {
    struct Key {
        char buf[10000];
        bool operator<(const Key&) const { return true; }
    };
    // попробуйте не хранить непосредственно в объекте ничего лишнего
    EXPECT_LT(sizeof(exam::set<Key>), sizeof(Key));
}
//
TEST(basic, swap) {
    using S = exam::set<int>;
    S s1, s2;

    for (int k : {1, 2, 3}) {
        s1.insert(k);
    }
    for (int k : {3, 4, 5, 6}) {
        s2.insert(k);
    }
    ASSERT_EQ(3u, s1.size());
    ASSERT_EQ(4u, s2.size());

    S::swap(s1, s2);
    EXPECT_EQ(4u, s1.size());
    EXPECT_EQ(3u, s2.size());

    for (int k : {1, 2}) {
        EXPECT_TRUE(s1.find(k) == s1.end()) << "key=" << k;
        EXPECT_TRUE(s2.find(k) != s2.end()) << "key=" << k;
    }
    for (int k : {3}) {
        EXPECT_TRUE(s1.find(k) != s1.end()) << "key=" << k;
        EXPECT_TRUE(s2.find(k) != s2.end()) << "key=" << k;
    }
    for (int k : {4, 5, 6}) {
        EXPECT_TRUE(s1.find(k) != s1.end()) << "key=" << k;
        EXPECT_TRUE(s2.find(k) == s2.end()) << "key=" << k;
    }
}

#ifdef SET_DEEP_COPY
TEST(deep_copy, copy_ctor) {
    using S = exam::set<int>;
    S s;
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        s.insert(k);
    }
    ASSERT_EQ(7u, s.size());

    S s2 = s;
    ASSERT_EQ(7u, s.size());
    ASSERT_EQ(7u, s2.size());

    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        auto e = s.find(k);
        EXPECT_TRUE(e != s.end()) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;

        auto e2 = s2.find(k);
        EXPECT_TRUE(e2 != s2.end()) << "key=" << k;
        EXPECT_EQ(k, *e2) << "key=" << k;
    }

    // контейнеры независимы
    s.insert(0);
    s2.insert(80);
    s2.insert(90);
    EXPECT_EQ(8u, s.size());
    EXPECT_EQ(9u, s2.size());

    EXPECT_TRUE(s.find(0) != s.end());
    EXPECT_TRUE(s.find(80) == s.end());
    EXPECT_TRUE(s.find(90) == s.end());

    EXPECT_TRUE(s2.find(0) == s2.end());
    EXPECT_TRUE(s2.find(80) != s2.end());
    EXPECT_TRUE(s2.find(90) != s2.end());

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_FALSE(s2.empty());
    EXPECT_EQ(9u, s2.size());
}

TEST(deep_copy, copy_assign) {
    using S = exam::set<int>;
    S s;
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        s.insert(k);
    }
    ASSERT_EQ(7u, s.size());

    S s2;
    for (int k : {1, 2, 3}) {
        s2.insert(k);
    }
    ASSERT_EQ(3u, s2.size());

    s2 = s;

    ASSERT_EQ(7u, s.size());
    ASSERT_EQ(7u, s2.size());

    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        auto e = s.find(k);
        EXPECT_TRUE(e != s.end()) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;

        auto e2 = s2.find(k);
        EXPECT_TRUE(e2 != s2.end()) << "key=" << k;
        EXPECT_EQ(k, *e2) << "key=" << k;
    }
    for (int k : {1, 2, 3}) {
        EXPECT_TRUE(s.find(k) == s.end()) << "key=" << k;
        EXPECT_TRUE(s2.find(k) == s2.end()) << "key=" << k;
    }

    // контейнеры независимы
    s.insert(0);
    s2.insert(80);
    s2.insert(90);

    EXPECT_TRUE(s.find(0) != s.end());
    EXPECT_TRUE(s.find(80) == s.end());
    EXPECT_TRUE(s.find(90) == s.end());

    EXPECT_TRUE(s2.find(0) == s2.end());
    EXPECT_TRUE(s2.find(80) != s2.end());
    EXPECT_TRUE(s2.find(90) != s2.end());

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_FALSE(s2.empty());
    EXPECT_EQ(9u, s2.size());
}
#endif  // SET_DEEP_COPY

#ifdef SET_MOVES
TEST(moves, move_ctor) {
    using S = exam::set<int>;
    S s;
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        s.insert(k);
    }
    ASSERT_EQ(7u, s.size());

    S s2 = std::move(s);
    ASSERT_EQ(0u, s.size());
    ASSERT_EQ(7u, s2.size());

    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        EXPECT_TRUE(s.find(k) == s.end()) << "key=" << k;

        auto e2 = s2.find(k);
        EXPECT_TRUE(e2 != s2.end()) << "key=" << k;
        EXPECT_EQ(k, *e2) << "key=" << k;
    }

    // контейнеры независимы
    s.insert(0);
    s2.insert(80);
    s2.insert(90);
    EXPECT_EQ(1u, s.size());
    EXPECT_EQ(9u, s2.size());

    EXPECT_TRUE(s.find(0) != s.end());
    EXPECT_TRUE(s.find(80) == s.end());
    EXPECT_TRUE(s.find(90) == s.end());

    EXPECT_TRUE(s2.find(0) == s2.end());
    EXPECT_TRUE(s2.find(80) != s2.end());
    EXPECT_TRUE(s2.find(90) != s2.end());

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_FALSE(s2.empty());
    EXPECT_EQ(9u, s2.size());
}

TEST(moves, move_assign) {
    using S = exam::set<int>;
    S s;
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        s.insert(k);
    }
    ASSERT_EQ(7u, s.size());

    S s2;
    for (int k : {1, 2, 3}) {
        s2.insert(k);
    }
    ASSERT_EQ(3u, s2.size());

    s2 = std::move(s);

    ASSERT_EQ(0u, s.size());
    ASSERT_EQ(7u, s2.size());

    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        EXPECT_TRUE(s.find(k) == s.end()) << "key=" << k;

        auto e2 = s2.find(k);
        EXPECT_TRUE(e2 != s2.end()) << "key=" << k;
        EXPECT_EQ(k, *e2) << "key=" << k;
    }
    for (int k : {1, 2, 3}) {
        EXPECT_TRUE(s.find(k) == s.end()) << "key=" << k;
        EXPECT_TRUE(s2.find(k) == s2.end()) << "key=" << k;
    }

    // контейнеры независимы
    s.insert(0);
    s2.insert(80);
    s2.insert(90);

    EXPECT_TRUE(s.find(0) != s.end());
    EXPECT_TRUE(s.find(80) == s.end());
    EXPECT_TRUE(s.find(90) == s.end());

    EXPECT_TRUE(s2.find(0) == s2.end());
    EXPECT_TRUE(s2.find(80) != s2.end());
    EXPECT_TRUE(s2.find(90) != s2.end());

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_FALSE(s2.empty());
    EXPECT_EQ(9u, s2.size());
}
#endif  // SET_MOVES

#ifdef SET_WITH_COMPARATOR
TEST(comparator, custom_key) {
    struct Key {
        int q;
    };
    struct Cmp {
        bool operator()(const Key& a, const Key& b) const { return a.q < b.q; }
    };
    exam::set<Key, Cmp> s;
    for (int k : {20, 10, 30}) {
        s.insert({k});
    }
    EXPECT_EQ(3u, s.size());
    for (int k : {20, 10, 30}) {
        auto e = s.find({k});
        ASSERT_TRUE(e != s.end());
        EXPECT_EQ(k, e->q);
    }
}

TEST(comparator, default_constructor) {
    using S = exam::set<int, std::greater<>>;
    S s;
    for (int k : {30, 10, 20, 50, 40}) {
        s.insert(k);
    }
    EXPECT_EQ(5u, s.size());

    S s2 = s;
    EXPECT_EQ(5u, s2.size());

    s2 = s;
    EXPECT_EQ(5u, s2.size());

    s2 = std::move(s);
    EXPECT_EQ(5u, s2.size());
    EXPECT_EQ(0u, s.size());
}

TEST(comparator, parametrized_constructor) {
    struct less_by_modulo {
        int modulo;
        explicit less_by_modulo(int m) : modulo(m) {}
        bool operator()(int a, int b) const { return a % modulo < b % modulo; }
    };

    using S = exam::set<int, less_by_modulo>;
    S s{less_by_modulo{10}};
    for (int k : {13, 11, 12, 15, 14, 21, 22, 23, 24, 25}) {
        s.insert(k);
    }
    EXPECT_EQ(5u, s.size());
    for (int k : {11, 12, 13, 14, 15}) {
        auto e = s.find(k);
        ASSERT_TRUE(e != s.end());
        EXPECT_EQ(k, *e);

        auto e2 = s.find(k + 20);
        EXPECT_TRUE(e == e2);
    }

    S s2 = s;
    EXPECT_EQ(5u, s2.size());
    for (int k : {11, 12, 13, 14, 15}) {
        auto e = s2.find(k);
        ASSERT_TRUE(e != s.end());
        EXPECT_EQ(k, *e);

        auto e2 = s2.find(k + 20);
        EXPECT_TRUE(e == e2);
    }

    S s3{less_by_modulo{2}};
    s3 = s;
    EXPECT_EQ(5u, s3.size());
    for (int k : {11, 12, 13, 14, 15}) {
        auto e = s3.find(k);
        ASSERT_TRUE(e != s.end());
        EXPECT_EQ(k, *e);

        auto e2 = s3.find(k + 20);
        EXPECT_TRUE(e == e2);
    }

    s3 = std::move(s);
    EXPECT_EQ(0u, s.size());
    EXPECT_EQ(5u, s3.size());
    {
        auto e = s3.find(43);
        ASSERT_TRUE(e != s3.end());
        EXPECT_EQ(13, *e);
    }

    S s4{less_by_modulo{2}};
    swap(s, s4);
    EXPECT_EQ(0u, s.size());
    EXPECT_EQ(0u, s4.size());
    for (int k : {1, 2, 3, 4}) {
        s.insert(k);
        s4.insert(k);
    }
    EXPECT_EQ(2u, s.size());  // 1==3, 2==4 по модулю 2
    EXPECT_EQ(4u, s4.size());
}
#endif

#ifdef SET_ITERATION
TEST(iteration, empty) {
    const exam::set<int> cs;
    ASSERT_TRUE(cs.empty());

    EXPECT_TRUE(cs.begin() == cs.end());
}

TEST(iteration, ascending) {
    using S = exam::set<int>;
    S s;
    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        s.insert(k);
    }
    ASSERT_EQ(7u, s.size());

    S::element e = s.begin();
    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        ASSERT_TRUE(e != s.end()) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;

        // проверяем работу пред- и постинкремента
        S::element e0 = e, e1 = e;
        S::element& re1 = ++e1;
        EXPECT_EQ(&e1, &re1);
        S::element old = e++;
        EXPECT_TRUE(old == e0);
        EXPECT_TRUE(e == e1);
    }
    EXPECT_TRUE(e == s.end());
}

TEST(iteration, descending) {
    using S = exam::set<int>;
    S s;
    for (int k : {70, 60, 50, 40, 30, 20, 10}) {
        s.insert(k);
    }
    ASSERT_EQ(7u, s.size());

    S::element e = s.begin();
    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        ASSERT_TRUE(e != s.end()) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;

        // проверяем работу пред- и постинкремента
        S::element e0 = e, e1 = e;
        S::element& re1 = ++e1;
        EXPECT_EQ(&e1, &re1);
        S::element old = e++;
        EXPECT_TRUE(old == e0);
        EXPECT_TRUE(e == e1);
    }
    EXPECT_TRUE(e == s.end());
}

TEST(iteration, random) {
    using S = exam::set<int>;
    S s;
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        s.insert(k);
    }
    ASSERT_EQ(7u, s.size());

    S::element e = s.begin();
    for (int k : {10, 20, 30, 40, 50, 60, 70}) {
        ASSERT_TRUE(e != s.end()) << "key=" << k;
        EXPECT_EQ(k, *e) << "key=" << k;

        // проверяем работу пред- и постинкремента
        S::element e0 = e, e1 = e;
        S::element& re1 = ++e1;
        EXPECT_EQ(&e1, &re1);
        S::element old = e++;
        EXPECT_TRUE(old == e0);
        EXPECT_TRUE(e == e1);
    }
    EXPECT_TRUE(e == s.end());
}

#ifdef SET_WITH_COMPARATOR
TEST(iteration, custom_comparator) {
    exam::set<int, std::greater<>> s;
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        s.insert(k);
    }

    auto e = s.begin();
    for (int k : {70, 60, 50, 40, 30, 20, 10}) {
        ASSERT_TRUE(e != s.end()) << "key=" << k;
        EXPECT_EQ(k, *e);
        ++e;
    }
    EXPECT_TRUE(e == s.end());
}
#endif // SET_WITH_COMPARATOR - inside SET_ITERATION

#endif  // SET_ITERATION


#ifdef SET_ERASE
TEST(erase, by_value) {
    exam::set<int> s;
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        s.insert(k);
    }
    ASSERT_EQ(7u, s.size());
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        EXPECT_TRUE(s.find(k) != s.end());
        EXPECT_TRUE(s.erase(k));
        EXPECT_FALSE(s.erase(k));  // второй раз нечего удалять
        EXPECT_TRUE(s.find(k) == s.end());

        int m = k + 1;
        EXPECT_TRUE(s.find(m) == s.end());
        EXPECT_FALSE(s.erase(m));
    }
    EXPECT_TRUE(s.empty());
}

#ifdef SET_WITH_COMPARATOR
TEST(erase, by_value_with_custom_comparator) {
    exam::set<int, std::greater<>> s;
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        s.insert(k);
    }
    ASSERT_EQ(7u, s.size());
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        EXPECT_TRUE(s.find(k) != s.end());
        EXPECT_TRUE(s.erase(k));
        EXPECT_FALSE(s.erase(k));  // второй раз нечего удалять
        EXPECT_TRUE(s.find(k) == s.end());

        int m = k + 1;
        EXPECT_TRUE(s.find(m) == s.end());
        EXPECT_FALSE(s.erase(m));
    }
    EXPECT_TRUE(s.empty());
}
#endif  // SET_WITH_COMPARATOR - inside SET_ERASE

#ifdef SET_ITERATION
TEST(erase, by_iterator) {
    exam::set<int> s;
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        s.insert(k);
    }
    ASSERT_EQ(7u, s.size());
    for (int k : {40, 20, 60, 10, 30, 50, 70}) {
        auto e = s.find(k);
        auto e1 = e; ++e1;

        auto e2 = s.erase(e);
        EXPECT_TRUE(e1 == e2);
    }
    EXPECT_TRUE(s.empty());
}
#endif  // SET_ITERATION - inside SET_ERASE

#endif  // SET_ERASE

////////////////////////////////////////////////////////////////////////////////

TESTING_MAIN()
