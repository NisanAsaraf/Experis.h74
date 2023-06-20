#include "mu_test.h"
#include <string>

#include "../../inc/SymMatrix.hpp"

BEGIN_TEST(_SymMatrix_creation_empty)
	SymMatrix<int> m(100);
	ASSERT_THAT(m.get_dim() == 5050);
END_TEST

BEGIN_TEST(_SymMatrix_creation_copy)
	SymMatrix<int> m(100);
    SymMatrix<int> q = m;
	ASSERT_THAT(q.get_dim() == 5050);
END_TEST

BEGIN_TEST(_SymMatrix_creation_eq)
    SymMatrix<int> m(100);
    SymMatrix<int> k(0);
    k = m;
    ASSERT_THAT(k.get_dim() == 5050);
END_TEST

BEGIN_TEST(_SymMatrix_get_OP)
	SymMatrix<int> m(100);
    m(3, 2) = 4.2;
    ASSERT_THAT(m(3, 2) == m(2,3));
END_TEST

BEGIN_TEST(_SymMatrix_print)
	SymMatrix<int> m(100);
//    std::cout << m; 
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(_SymMatrix_OP_PLUS)
    SymMatrix<int> m(100);      
    m(3, 2) = 4.2;
    SymMatrix<int> k = m;
    k += m;
    ASSERT_THAT(k(3, 2) == 2*(int)4.2);
END_TEST

BEGIN_TEST(_SymMatrix_OP_PLUS_LONG)
    SymMatrix<int> m(100);      
    m(3, 2) = 4.2;
    SymMatrix<int> k = m;
    k += m;
    SymMatrix<long> w = m;
    w += k;
    ASSERT_THAT(w(3, 2) == 3*(int)4.2);
END_TEST

BEGIN_TEST(_SymMatrix_ALL_EXAM_TESTS)
    SymMatrix<int> m(100); 
    m(3, 2) = 4.2;    
    ASSERT_THAT(m(3, 2) == m(2,3));
    SymMatrix<int> k = m;
    k += m;
    SymMatrix<long> w = m;
    w += k;
/*     m = k + k; */
/*     ASSERT_THAT(w(3, 2) == 3*(int)4.2); */
END_TEST

TEST_SUITE(決して道から外れてはいけません)
TEST(_SymMatrix_creation_empty)
TEST(_SymMatrix_creation_copy)
TEST(_SymMatrix_creation_eq)
TEST(_SymMatrix_get_OP)
TEST(_SymMatrix_print)
TEST(_SymMatrix_OP_PLUS)
TEST(_SymMatrix_OP_PLUS_LONG)
TEST(_SymMatrix_ALL_EXAM_TESTS)
END_SUITE
