#include "mu_test.h"
#include <string>
#include <climits>

#include "../../inc/rational.hpp"

    BEGIN_TEST(_value)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(ten.value() == (double)10);
    END_TEST

    BEGIN_TEST(_inverse)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(equal_to(ten.inverse(), algebra::Rational(1,10)));
    END_TEST
    
    BEGIN_TEST(_add)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(equal_to(ten.fraction_add(algebra::Rational(10, 2)), algebra::Rational(15,1)));
    END_TEST

    BEGIN_TEST(_sub)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(equal_to(ten.fraction_sub(algebra::Rational(10, 2)), algebra::Rational(5, 1)));
    END_TEST

    BEGIN_TEST(_mul)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(equal_to(ten.fraction_mul(algebra::Rational(1, 5)), algebra::Rational(2, 1)));
    END_TEST

    BEGIN_TEST(_div)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(equal_to(ten.fraction_div(algebra::Rational(5, 1)), algebra::Rational(2, 1)));
    END_TEST

    BEGIN_TEST(_less)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(ten.less(algebra::Rational(15,1)));
    END_TEST

    algebra::Rational const frac_list[] = {algebra::Rational(), algebra::Rational(1), algebra::Rational(1, 2), algebra::Rational(3, 2), algebra::Rational(20, 2)};

    BEGIN_TEST(_sumd)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(algebra::equal_to(algebra::sumd(frac_list, 5), algebra::Rational(13,1).value()));
    END_TEST

    BEGIN_TEST(_sumf)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(algebra::equal_to(algebra::sumf(frac_list, 5), algebra::Rational(13,1)));
    END_TEST
 
    BEGIN_TEST(OP_add)
        algebra::Rational ten(20, 2);
        ASSERT_THAT((ten + algebra::Rational(10, 2)) ==  algebra::Rational(15,1));
    END_TEST

    BEGIN_TEST(OP_sub)
        algebra::Rational ten(20, 2);
        ASSERT_THAT((ten - algebra::Rational(10, 2)) ==  algebra::Rational(5, 1));
    END_TEST

    BEGIN_TEST(OP_mul)
        algebra::Rational ten(20, 2);
        ASSERT_THAT((ten*algebra::Rational(1, 5)) ==  algebra::Rational(2, 1));
    END_TEST

    BEGIN_TEST(OP_div)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(ten/algebra::Rational(5, 1) ==  algebra::Rational(2, 1));
    END_TEST

    BEGIN_TEST(OP_less)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(ten < algebra::Rational(15,1));
    END_TEST

    BEGIN_TEST(OP_sumd)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(algebra::sumd(frac_list, 5) == algebra::Rational(13,1).value());
    END_TEST

    BEGIN_TEST(OP_sumf)
        algebra::Rational ten(20, 2);
        ASSERT_THAT(algebra::sumf(frac_list, 5) ==  algebra::Rational(13,1));
    END_TEST

TEST_SUITE(決して道から外れてはいけません)
    TEST(_value)
    TEST(_inverse)
    TEST(_add)
    TEST(_sub)
    TEST(_mul)
    TEST(_div)
    TEST(_less)
    TEST(_sumd)
    TEST(_sumf)
    TEST(OP_add)
    TEST(OP_sub)
    TEST(OP_mul)
    TEST(OP_div)
    TEST(OP_less)
    TEST(OP_sumd)
    TEST(OP_sumf)

END_SUITE