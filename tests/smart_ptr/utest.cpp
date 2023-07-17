#include "mu_test.h"
#include <string>
#include "smart_ptr.hpp"

using namespace ptr_utils;

BEGIN_TEST(ptr_init)
    SmartPtr<int> SP;
    ASSERT_THAT(!SP);
END_TEST

BEGIN_TEST(ptr_init_str)
    SmartPtr SP(new std::string("Hello123"));
    ASSERT_THAT(SP);
END_TEST

BEGIN_TEST(ptr_init_str_move)
    SmartPtr SP(new std::string("Hello123"));
    SmartPtr<std::string> MP;
    MP = std::move(SP);
    ASSERT_THAT(!SP && !!MP);
END_TEST

BEGIN_TEST(ptr_init_str_deref)
    SmartPtr SP(new std::string("Hello123"));
    ASSERT_THAT(*SP == "Hello123");
END_TEST

BEGIN_TEST(ptr_init_str_deref_const)
    const SmartPtr SP(new std::string("Hello123"));
    ASSERT_THAT(*SP == "Hello123");
END_TEST

BEGIN_TEST(ptr_init_arrow)
    SmartPtr SP(new std::string("Hello123"));
    ASSERT_THAT(SP->length() == 8);
END_TEST

BEGIN_TEST(ptr_init_arrow_const)
    const SmartPtr SP(new std::string("Hello123"));
    ASSERT_THAT(SP->length() == 8);
END_TEST

BEGIN_TEST(ptr_init_str_assignment_move)
    SmartPtr SP(new std::string("Hello123"));
    SmartPtr MP(new std::string("Godbye321"));
    SP = std::move(MP);
    ASSERT_THAT(*SP == "Godbye321" && !MP);
END_TEST


TEST_SUITE(決して道から外れてはいけません)
TEST(ptr_init)
TEST(ptr_init_str)
TEST(ptr_init_str_move)
TEST(ptr_init_str_deref)
TEST(ptr_init_str_deref_const)
TEST(ptr_init_arrow)
TEST(ptr_init_arrow_const)
TEST(ptr_init_str_assignment_move)

END_SUITE
