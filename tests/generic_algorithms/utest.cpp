#include "mu_test.h"
#include <string>

#include "../../inc/generic_algorithms.hpp"

using namespace std;

BEGIN_TEST(_print_any_container)
    vector<int> e;
    vector<int> o(1, 6);
    vector<int> v(3, 4);
    cout << e;  // print exactly: [ ]
    cout << o;  // print exactly: [ 6]
    cout << v;  // print exactly: [ 4, 4, 4 ]
    ASSERT_THAT(true);
    list<pets::Cat> lst;
    lst.push_back(pets::Cat("pixel"));
    lst.push_back(pets::Cat("quark"));
    cout << lst; // print exactly: [ pixel, quark ]
END_TEST

BEGIN_TEST(print_subrange)
    vector<int> v(3, 14);
    print(v.begin(), v.end());
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(print_mul)
    vector<int> v(3, 10);
    cout << mul(v.begin(), v.end()); // 1000
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(print_binary)
    vector<int> v;
    v.push_back(3);
    v.push_back(7);
    v.push_back(10);
    v.push_back(20);
    cout << foldit(v.begin(), v.end(), add) << '\n';  // 40
    // as if executed  add(add(v[0], v[1]), v[2])
    cout << foldit(v.begin(), v.end(), mul) << '\n';  // 4200
    ASSERT_THAT(true);  
END_TEST

BEGIN_TEST(print_merge)
    std::vector<int> v = {1, 4, 7, 9, 12, 13, 15};
    std::vector<int> w = {2, 3, 5, 10, 13, 18, 19};
    vector<int> r(14);
    merge(v, w, r);
    cout << r;
    // [1,2,3,4,5,7,9,10,12,13,13,15,18,19 ]
    ASSERT_THAT(true);  
END_TEST


BEGIN_TEST(print_replace)
    vector<int> v = {1, 5, 2, 1, 4, 3, 7, 2};
    replace_with_left_bigger(v);
    print(v);
    // prints  [ 5, 7, 4, 4, 4, 5, 7, 7, 2 ]
    ASSERT_THAT(true);  
END_TEST

TEST_SUITE(決して道から外れてはいけません)
TEST(_print_any_container)
TEST(print_subrange)
TEST(print_mul)
TEST(print_binary)
TEST(print_merge)
TEST(print_replace)

END_SUITE
