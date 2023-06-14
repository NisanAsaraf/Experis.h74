#include "mu_test.h"

#include <string>
#include <climits>

#include "../../inc/minimum_stack.hpp"

BEGIN_TEST(_stack_creation)
	ds::MinimumStack s(100);
	ASSERT_THAT(s.empty());
END_TEST

BEGIN_TEST(add_operations)
	ds::MinimumStack s(12);
	s.push(13);
	ASSERT_THAT(s.pop() == 13);
END_TEST

BEGIN_TEST(remove_operations)
	ds::MinimumStack s(15);
	s.push(9292);
	ASSERT_THAT(s.pop() == 9292);
END_TEST

BEGIN_TEST(get_min)
	ds::MinimumStack q(15);
	q.push(5);
	q.push(1);
	q.push(-15);
	q.push(12);
	ASSERT_THAT(q.getMinimum() == -15);
	
END_TEST

TEST_SUITE(決して道から外れてはいけません)
	TEST(_stack_creation)
	TEST(add_operations)
	TEST(remove_operations)
	TEST(get_min)
END_SUITE