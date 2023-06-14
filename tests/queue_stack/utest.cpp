#include "mu_test.h"

#include <string>
#include <climits>

#include "../../inc/queue_stack.hpp"

BEGIN_TEST(Qcreate)
	ds::QueueStack q(100);

	ASSERT_THAT(true); //just so we wont get exception from the constructor

END_TEST

BEGIN_TEST(enque)
	ds::QueueStack q(100);
	q.enqueue(5);
	q.enqueue(4);
	q.enqueue(3);

	ASSERT_THAT(q.dequeue() == 5);

END_TEST

BEGIN_TEST(deque)
	ds::QueueStack q(100);
	q.enqueue(5);
	q.enqueue(4);
	q.enqueue(3);
	q.dequeue();
	q.dequeue();
	q.enqueue(4);
	q.dequeue();
	q.enqueue(3);
	ASSERT_THAT(q.dequeue() == 4);
END_TEST

TEST_SUITE(決して道から外れてはいけません)
	TEST(Qcreate)
	TEST(enque)
	TEST(deque)
END_SUITE
