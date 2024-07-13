#include <cassert>
#include <string>
#include <sstream>

// Include guard should prevent double inclusion.
#include "bignum.hpp"
#include "bignum.hpp"

void check_constructors()
{
    mp::bignum n1;
    assert(n1.to_string() == "0");

    mp::bignum n2(42);
    assert(n2.to_string() == "42");

    mp::bignum n3(0xffffffff);
    assert(n3.to_string() == "4294967295");

    mp::bignum n4(n2);
    assert(n2.to_string() == "42");
    assert(n4.to_string() == "42");

    mp::bignum n5("42");
    assert(n5.to_string() == "42");

    mp::bignum n6("18446744073709551615");
    assert(n6.to_string() == "18446744073709551615");
}

void check_assignment()
{
    mp::bignum n1;
    assert(n1.to_string() == "0");

    n1 = 1;
    assert(n1.to_string() == "1");

    n1 = 0xffffffff;
    assert(n1.to_string() == "4294967295");

    mp::bignum n2;
    assert(n2.to_string() == "0");

    n2 = n1;
    assert(n1.to_string() == "4294967295");
    assert(n2.to_string() == "4294967295");

    mp::bignum n3("18446744073709551615"), n4, n5;
    assert(n3.to_string() == "18446744073709551615");
    assert(n4.to_string() == "0");
    n4 = n3;
    assert(n3.to_string() == "18446744073709551615");
    assert(n4.to_string() == "18446744073709551615");

    n3 = n5;
    assert(n3.to_string() == "0");
    assert(n5.to_string() == "0");

// In case compiler will complain about (intended here) self-assignment.
// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wself-assign-overloaded"
    n4 = n4;
// #pragma clang diagnostic pop
    assert(n4.to_string() == "18446744073709551615");
}

void check_to_int()
{
    mp::bignum n1(42);
    assert(std::uint32_t(n1) == 42);

    mp::bignum n2("1311768467284833366");  // 0x1234567890123456
    assert(std::uint32_t(n2) == 0x90123456);
}

void check_bool()
{
    assert(!mp::bignum(0));
    assert(mp::bignum(123));
}

void check_io()
{
    mp::bignum const n1(1234);

    std::ostringstream ostr;
    ostr << n1;
    assert(ostr.str() == "1234");

    std::istringstream istr1("5678");
    mp::bignum n2(42);
    istr1 >> n2;
    assert(n2.to_string() == "5678");

    // Optional
    std::istringstream istr2("0001234");
    mp::bignum n3;
    istr2 >> n3;
    assert(n3.to_string() == "1234");

    std::istringstream istr3("+1234");
    mp::bignum n4;
    istr3 >> n4;
    assert(n4.to_string() == "1234");

    std::istringstream istr4("+01234");
    mp::bignum n5;
    istr4 >> n5;
    assert(n5.to_string() == "1234");
}


void check_operators() {
    mp::bignum n1(1234);
    mp::bignum n2(5678);
    assert((n1 + n2).to_string() == std::to_string(1234 + 5678));

    mp::bignum n7(9999);
    mp::bignum n8(1);
    assert((n7 + n8).to_string() == std::to_string(9999 + 1));
    assert((n1 * n2).to_string() == std::to_string(1234 * 5678));

    mp::bignum n3(0xffffffff);
    mp::bignum n4(0xaaaaaaaa);
    assert((n3 + n4).to_string() == "7158278825");
    assert((n3 * n4).to_string() == "12297829376746411350");

    n3 *= 2;
    assert(n3.to_string() == "8589934590");

    n3 += n4;
    assert(n3.to_string() == "11453246120");
}

void check_const()
{
    mp::bignum const n1(42);
    mp::bignum n2;
    n2 = n1;
    assert(n1.to_string() == "42");
    assert(n2.to_string() == "42");

    mp::bignum const n3(10);
    assert(std::uint32_t(n3) == 10);

    assert(n3);

    assert((n1 + n3).to_string() == "52");
    assert((n1 * n3).to_string() == "420");

    n2 *= n3;
    assert(n2.to_string() == "420");
    assert(n3.to_string() == "10");

    n2 += n3;
    assert(n2.to_string() == "430");
    assert(n3.to_string() == "10");
}


void check_polynomial()
{
    mp::polynomial const p("2*x^2+10*x^1+1*x^0");

    assert(p(0) == 1);
    assert(p(-1) == -7);
    assert(std::abs(p(1.0) - 13.) < std::numeric_limits<double>::epsilon());
    assert(std::abs(p(0.1) - 2.02) < std::numeric_limits<double>::epsilon());
    assert(p(mp::bignum(2)).to_string() == "29");
}

void check_long_coefficient()
{
    mp::polynomial p("100*x^0");
    assert(p.at(0) == 100);
}

void check_long_double()
{
    mp::polynomial p("1*x^1");
    assert(p(1e100) == 1e100);
    assert(std::abs(p(1e100)-1e100) < 1e90);
}

void check_at()
{
    mp::polynomial p("1*x^0");

    assert(p.at(0) == 1);
    assert(p.at(1) == 0);
    assert(p(1) == 1);


    assert(p.at(2) == 0);
    assert(p.at(3) == 0);
    assert(p.at(10) == 0);
}

void check_const_at()
{
    mp::polynomial const p("7x^4+3x^2+2x^1+5x^0");

    assert(p.at(2) == 3);
    assert(p.at(4) == 7);
    assert(p(0) == 5);
    assert(p(1) == 17);
    assert(p(2) == 133);
}

int main()
{
    check_constructors();
    check_assignment();
    check_to_int();
    check_bool();
    check_io();
    check_operators();
    check_const();

    check_polynomial();
    check_long_coefficient();
    check_long_double();
    check_at();
    check_const_at();
}
