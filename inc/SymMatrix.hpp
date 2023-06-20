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

    size_t get_dim();

private:
    size_t m_dimension;
    T* m_data;
};

size_t sum_from_1_to_n(size_t n)
{
    return n*(n + 1)/2;
}

size_t translate_index(size_t a_row, size_t a_col)
{
    return (a_row * (a_row + 1)) / 2 + a_col;
}

template <typename T>
size_t SymMatrix<T>::get_dim()
{
    return m_dimension;
}

template <typename T>
SymMatrix<T>::SymMatrix(size_t a_dim)
:m_dimension(sum_from_1_to_n(a_dim))
,m_data(new T[m_dimension]())
{

}

template <typename T>
SymMatrix<T>::SymMatrix(SymMatrix const& a_other)
:m_dimension(a_other.m_dimension)
,m_data(new T[m_dimension])
{
    for(size_t i = 0 ; i < m_dimension; i++)
    {
        this->m_data[i] = a_other.m_data[i];
    }
}

template <typename T>
SymMatrix<T>& SymMatrix<T>::operator=(SymMatrix const& a_other)
{
    if (this != &a_other) 
    {
        m_dimension = a_other.m_dimension;
        T* m_safe_data = new T[m_dimension];

        for(size_t i = 0 ; i < m_dimension; i++)
        {
           m_safe_data[i] = a_other.m_data[i];
        }

        delete[] m_data;
        m_data = m_safe_data;
    }
    return *this;
}

template <typename T>
SymMatrix<T>::~SymMatrix()
{
    delete[] m_data;
}

template <typename T>
T& SymMatrix<T>::operator()(size_t a_row, size_t a_column)
{
    assert(a_row < m_dimension && a_col < m_dimension);
    size_t index = translate_index(a_row, a_col);
    return m_data[index];
}

template <typename T>
T const& SymMatrix<T>::operator()(size_t a_row, size_t a_column) const
{
    assert(a_row < m_dimension && a_col < m_dimension);
    size_t index = translate_index(a_row, a_col);
    return m_data[index];
}

template <typename T>
SymMatrix<T>& SymMatrix<T>::operator+=(SymMatrix const& a_other)
{
    assert(m_dimension == a_other.m_dimension);
    T* m_safe_data = new T[m_dimension];

    for(size_t i = 0 ; i < m_dimension; i++)
    {
        m_safe_data[i] = m_data[i] + a_other.m_data[i];
    }

    delete[] m_data;
    m_data = m_safe_data;

    return *this;
}