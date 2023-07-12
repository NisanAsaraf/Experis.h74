#include "mu_test.h"
#include <string>

#include "../../inc/vault_secrets.hpp"

BEGIN_TEST(vault_init)
vos::Vault &vault1 = vos::Vault::open("1234");
vault1.add("google" , "qwer");
vault1.add("youtube" , "asdf");
vault1.add("gmail" , "zxcv");

std::cout<<vault1;

ASSERT_THAT(true);

END_TEST

BEGIN_TEST(vault_re_init)
vos::Vault &vault1 = vos::Vault::open("1234");
std::cout<<vault1;
ASSERT_THAT(true);
END_TEST

BEGIN_TEST(vault_get)
vos::Vault &vault1 = vos::Vault::open("1234");
std::cout<<vault1.get("google");

ASSERT_THAT(true);
END_TEST

BEGIN_TEST(vault_get_except)
vos::Vault &vault1 = vos::Vault::open("1234");
try
{
    std::cout<<vault1.get("steam");
}
catch (const std::out_of_range& ex)
{

}
ASSERT_THAT(true);
END_TEST


TEST_SUITE(決して道から外れてはいけません)
TEST(vault_init)
TEST(vault_re_init)
TEST(vault_get)
TEST(vault_get_except)
END_SUITE
