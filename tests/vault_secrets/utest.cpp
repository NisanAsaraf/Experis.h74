#include "mu_test.h"
#include <string>
#include "../../inc/vault_secrets.hpp"

static std::string PW = "LIGMA";

BEGIN_TEST(vault_init)
    vos::Vault &vault1 = vos::Vault::open(PW);
    vault1.add("google" , "qwer");
    vault1.add("youtube" , "asdf");
    vault1.add("gmail" , "zxcv");

    std::cout<<vault1;

    ASSERT_THAT(true);

END_TEST

BEGIN_TEST(vault_re_init)
    vos::Vault &vault1 = vos::Vault::open(PW);
    std::cout<<vault1;
    vos::Vault &vault2 = vos::Vault::open(PW);
    std::cout<<vault2;
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(vault_wrong_password)
    try
    {
        vos::Vault &vault1 = vos::Vault::open("terry");
        std::cout<<vault1;
    }
    catch(const vos::InvalidPasswordException & e)
    {
        
    }

    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(vault_get)
    vos::Vault &vault1 = vos::Vault::open(PW);
    std::cout<<vault1.get("google");

    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(vault_get_except)
    vos::Vault &vault1 = vos::Vault::open(PW);
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
    vos::Vault &vault1 = vos::Vault::open(PW);
    vault1.save();
    ASSERT_THAT(true);

END_TEST

BEGIN_TEST(vault_get_load)
    vos::Vault &vault1 = vos::Vault::open(PW);
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
