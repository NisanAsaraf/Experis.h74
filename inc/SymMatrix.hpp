#include <cstddef>

template<typename T>
class SymMatrix
{
public:
    SymMatrix(size_t a_dim);
    SymMatrix(SymMatrix const& a_other);
    SymMatrix& operator=(SymMatrix const& a_other);
    ~SymMatrix();

    T& operator()(size_t a_row, size_t a_column);
    T const& operator()(size_t a_row, size_t a_column) const;
    
    SymMatrix& operator+=(SymMatrix const& a_other);
    
    template<typename U>
    friend SymMatrix operator+(SymMatrix<U> const& a_lVal, SymMatrix<U> const& a_rVal) ;
  
    template<typename U>
    friend std::ostream& operator<<(std::ostream &a_out, const SymMatrix<U> &a_matrix);

private:
    size_t m_dimension;
    T* m_data;
};