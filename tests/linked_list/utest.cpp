#include "mu_test.h"

#include <string>
#include "../../inc/linked_list.hpp"

BEGIN_TEST(_linked_list_creation_empty)
	ds::Linked_List<int> new_list;
	ASSERT_THAT(new_list.size() == 0);
END_TEST


TEST_SUITE(決して道から外れてはいけません)

END_SUITE
