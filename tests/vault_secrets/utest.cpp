#include "mu_test.h"
#include <string>
#include "../../inc/vault_secrets.hpp"
#include "../../inc/inl/vault_secrets.hxx"

static std::string PW = "psi";
using namespace vos;

BEGIN_TEST(vault_init)
    Vault<std::string> &vault1 = Vault<std::string>::open(PW);
    vault1.add("google" , "qwer");
    vault1.add("youtube" , "asdf");
    vault1.add("gmail" , "zxcv");

    std::cout<<vault1;

    ASSERT_THAT(true);

END_TEST

BEGIN_TEST(vault_re_init)
    Vault<std::string> &vault1 = Vault<std::string>::open(PW);
    std::cout<<vault1;
    Vault<std::string> &vault2 = Vault<std::string>::open(PW);
    std::cout<<vault2;
    ASSERT_EQUAL(&vault1, &vault2);
    
END_TEST

BEGIN_TEST(vault_wrong_password)
    try
    {
        Vault<std::string> &vault1 = Vault<std::string>::open("terry");
        std::cout<<vault1;
    }
    catch(const vos::InvalidPasswordException & e)
    {
        
    }

    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(vault_get)
    Vault<std::string> &vault1 = Vault<std::string>::open(PW);
    std::cout<<vault1.get("google");

    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(vault_get_except)
    Vault<std::string> &vault1 = Vault<std::string>::open(PW);
    try
    {
        std::cout<<vault1.get("steam");
    }
    catch (const std::out_of_range& ex)
    {

    }
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(vault_get_save)
    Vault<std::string> &vault1 = Vault<std::string>::open(PW);
    vault1.save();
    ASSERT_THAT(true);

END_TEST

BEGIN_TEST(vault_get_load)
    Vault<std::string> &vault1 = Vault<std::string>::open(PW);
    vault1.get("gmail");
    ASSERT_THAT(true);

END_TEST

TEST_SUITE(決して道から外れてはいけません)
TEST(vault_init)
TEST(vault_re_init)
TEST(vault_wrong_password)
TEST(vault_get)
TEST(vault_get_except)
TEST(vault_get_save)
TEST(vault_get_load)

END_SUITE
