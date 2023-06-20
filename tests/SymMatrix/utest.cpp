#include "mu_test.h"
#include <string>

#include "../../inc/SymMatrix.hpp"

BEGIN_TEST(_SymMatrix_creation_empty)
	SymMatrix<int> m(100);
	ASSERT_THAT(m.get_dim() == 100);
END_TEST


TEST_SUITE(決して道から外れてはいけません)
TEST(_SymMatrix_creation_empty)
	
END_SUITE
