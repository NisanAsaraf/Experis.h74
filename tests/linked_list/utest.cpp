#include "mu_test.h"

#include <string>
#include "../../inc/stack.hpp"

BEGIN_TEST(_stack_creation)
	ds::Stack s(100);

	ASSERT_THAT(s.empty());

END_TEST

BEGIN_TEST(_stack_creation_copy)
	ds::Stack s(100);
	ds::Stack q(s);
	ASSERT_THAT(q.empty());
END_TEST


BEGIN_TEST(_stack_creation_eq)
	ds::Stack s(100);
	ds::Stack q = s;
	ASSERT_THAT(q.empty());
END_TEST


BEGIN_TEST(add_operations)
	ds::Stack s(100);
	s.push(31);
	ASSERT_THAT(s.peek() == 31);
END_TEST

BEGIN_TEST(remove_operations)
	ds::Stack s(100);
	s.push(12);
	ASSERT_THAT(s.pop() == 12);
END_TEST

BEGIN_TEST(overload_test)
	ds::Stack s(100);
	ds::Stack q(100);
	size_t n = 100;
	while(n-- > 0)
	{
		s.push(4*n % 100);
		q.push(2*n % 100);
	}
	s += q;
	ASSERT_EQUAL(s.size(), 200);
	ASSERT_THAT(q.empty());
END_TEST


BEGIN_TEST(drain)
	ds::Stack s(100);
	ds::Stack p(100);
	s.push(5);
	s.push(2);
	s.push(1);
	ds::drain(s,p);
	ASSERT_THAT(s.empty());
END_TEST

BEGIN_TEST(test_full)
	size_t const n = 10;
	ds::Stack s(n);

	size_t many = n;
	while(many-- > 0){
		s.push(many);
	}
	ASSERT_EQUAL(s.size(), n);
	ASSERT_THAT(s.full());

END_TEST

BEGIN_TEST(double_free)
	ds::Stack s(10);
	s.~Stack();
	ASSERT_PASS();
END_TEST

TEST_SUITE(決して道から外れてはいけません)
	TEST(_stack_creation)
	TEST(_stack_creation_copy)
	TEST(_stack_creation_eq)
	TEST(add_operations)
	TEST(remove_operations)
	TEST(drain)
	TEST(test_full)
	IGNORE_TEST(double_free)
	TEST(overload_test)
END_SUITE
