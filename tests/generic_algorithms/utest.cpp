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
/*     list<Cat> lst;
    lst.push_back(Cat("pixel");
    lst.push_back(Cat("quark");
    cout << lst; // prin exactly: [ pixel, quark ] */
END_TEST

TEST_SUITE(決して道から外れてはいけません)
TEST(_print_any_container)
END_SUITE
