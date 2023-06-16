#include "mu_test.h"

#include <string>
#include "../../inc/linked_list.hpp"

BEGIN_TEST(_linked_list_creation_empty)
	ds::Linked_List<int> new_list;
	ASSERT_THAT(new_list.size() == 0);
END_TEST

BEGIN_TEST(_linked_list_creation_copy)
	ds::Linked_List<int> new_list;
	new_list.push_head(1).push_head(2).push_head(3).push_head(4).push_head(5);
	ds::Linked_List<int> copy_list(new_list);

	ASSERT_THAT(new_list.size() == 5);
	ASSERT_THAT(copy_list.size() == 5);
END_TEST

BEGIN_TEST(_linked_list_creation_eq)
	ds::Linked_List<int> new_list;
	new_list.push_head(1).push_head(2).push_head(3).push_head(4).push_head(5);
	ds::Linked_List<int> copy_list = new_list;

	ASSERT_THAT(new_list.size() == 5);
	ASSERT_THAT(copy_list.size() == 5);
END_TEST

BEGIN_TEST(_linked_list_push_head)
	ds::Linked_List<int> new_list;
	new_list.push_head(1).push_head(2).push_head(3).push_head(4).push_head(5);
	ASSERT_THAT(new_list.size() == 5);
END_TEST

BEGIN_TEST(_linked_list_push_tail)
	ds::Linked_List<int> new_list;
	new_list.push_tail(1).push_tail(2).push_tail(3).push_tail(4).push_tail(5);
	ASSERT_THAT(new_list.size() == 5);
END_TEST

BEGIN_TEST(_linked_list_pop_head)
	ds::Linked_List<int> new_list;
	new_list.push_head(1).push_head(2).push_head(3).push_head(4).push_head(5);
	ASSERT_THAT(new_list.size() == 5);
	int val = new_list.pop_head();  
	ASSERT_THAT(new_list.size() == 4);
	ASSERT_THAT(val == 5);
END_TEST

BEGIN_TEST(_linked_list_pop_tail)
	ds::Linked_List<int> new_list;
	new_list.push_head(1).push_head(2).push_head(3).push_head(4).push_head(5);
	ASSERT_THAT(new_list.size() == 5);
	int val = new_list.pop_tail();
	ASSERT_THAT(new_list.size() == 4);
	ASSERT_THAT(val == 1);
END_TEST

BEGIN_TEST(_linked_list_append)
	ds::Linked_List<int> new_list;
	new_list.append(1).append(2).append(3).append(4).append(5).append(6);
	ASSERT_THAT(new_list.size() == 6);
END_TEST

BEGIN_TEST(_linked_list_insert_before)
	ds::Linked_List<int> new_list;
	new_list.push_head(1).push_head(2).push_head(3).push_head(4).push_head(5);
	ASSERT_THAT(new_list.size() == 5);
	new_list.insert_before(4,42);
	ASSERT_THAT(new_list.size() == 6);
	//new_list.print();
END_TEST

BEGIN_TEST(_linked_list_insert_after)
	ds::Linked_List<int> new_list;
	new_list.push_tail(1).push_tail(2).push_tail(3).push_tail(4).push_tail(5);
	ASSERT_THAT(new_list.size() == 5);
	new_list.insert_after(0,42);
	ASSERT_THAT(new_list.size() == 6);
	//new_list.print();

END_TEST

BEGIN_TEST(_linked_list_swap)
	ds::Linked_List<int> new_list;
	new_list.push_tail(1).push_tail(2).push_tail(3).push_tail(4).push_tail(5);
	ASSERT_THAT(new_list.size() == 5);
	new_list.swap(0,4);

	//new_list.print();

END_TEST

BEGIN_TEST(_linked_list_size)
	ds::Linked_List<int> new_list;
	new_list.append(1).append(2).append(3).append(4).append(5).append(6);
	ASSERT_THAT(new_list.size() == 6);
END_TEST

BEGIN_TEST(_linked_list_contains)
	ds::Linked_List<int> new_list;
	new_list.append(1).append(2).append(3).append(4).append(5).append(6);
	ASSERT_THAT(new_list.size() == 6);
	ASSERT_THAT(new_list.contains(42) == false);
	ASSERT_THAT(new_list.contains(6) == true);
END_TEST

BEGIN_TEST(_linked_list_clear)
	ds::Linked_List<int> new_list;
	new_list.append(1).append(2).append(3).append(4).append(5).append(6);
	ASSERT_THAT(new_list.size() == 6);
	new_list.clear();
	ASSERT_THAT(new_list.size() == 0);
END_TEST

BEGIN_TEST(_linked_list_print)
	ds::Linked_List<int> new_list;
	new_list.push_head(142).push_head(61).push_head(641).push_head(121).push_head(90);
	new_list.print();
	ASSERT_THAT(true);
END_TEST

TEST_SUITE(決して道から外れてはいけません)
	TEST(_linked_list_creation_empty)
 	TEST(_linked_list_creation_copy)
	TEST(_linked_list_creation_eq)
	TEST(_linked_list_push_head)
	TEST(_linked_list_pop_head)
	TEST(_linked_list_push_tail)
	TEST(_linked_list_pop_tail)
	TEST(_linked_list_append)
	TEST(_linked_list_insert_before)
	TEST(_linked_list_insert_after)
	TEST(_linked_list_size)
	TEST(_linked_list_clear)
	TEST(_linked_list_swap)
	TEST(_linked_list_contains)
	IGNORE_TEST(_linked_list_print)

END_SUITE
