#include <cstddef>
#include <iostream>
#include <cassert>
#include <cmath>

namespace matrix
{
template<typename T>
class SymMatrix
{
public:
    explicit SymMatrix(size_t a_dim);

    SymMatrix(SymMatrix const& a_other);
    template <typename U>
    SymMatrix(SymMatrix<U> const& a_other);

    SymMatrix& operator=(SymMatrix const& a_other);
    template <typename U>
    SymMatrix<T>& operator=(SymMatrix<U> const& a_other);

    ~SymMatrix();

    T& operator()(size_t a_row, size_t a_column);
    T const& operator()(size_t a_row, size_t a_column) const;
    
    SymMatrix& operator+=(SymMatrix const& a_other); 
    template<typename U>
	SymMatrix& operator+=(SymMatrix<U> const& a_other);

    template<typename U>
    friend SymMatrix<U> operator+(SymMatrix<U> const& a_lVal, SymMatrix<U> const& a_rVal);

    template<typename U>
    friend std::ostream& operator<<(std::ostream &a_out, const SymMatrix<U> &a_matrix);

    size_t get_dim() const;

private:
    size_t m_dimension;
    T* m_data;
    template<typename U>
    friend class SymMatrix;
};

size_t find_n_from_sum(size_t sum)
{
    int discriminant = 1 + 8 *sum;
    size_t root = (std::sqrt(discriminant) - 1) / 2;
    return root;
}

size_t sum_from_1_to_n(size_t n)
{
    return n*(n + 1)/2;
}

size_t translate_index(size_t a_row, size_t a_col)
{
    if (a_row < a_col)
        std::swap(a_row, a_col);

    return a_row * (a_row - 1) / 2 + a_col;
}

template <typename T>
size_t SymMatrix<T>::get_dim() const
{
    return m_dimension;
}

template <typename T>
SymMatrix<T>::SymMatrix(size_t a_dim)
:m_dimension(sum_from_1_to_n(a_dim))
,m_data(new T[m_dimension]{})
{

}

template <typename T>
SymMatrix<T>::SymMatrix(SymMatrix const& a_other)
:m_dimension(a_other.m_dimension)
,m_data(new T[m_dimension])
{
    std::copy(a_other.m_data, a_other.m_data + a_other.get_dim(), m_data);
}

template <typename T>
template <typename U>
SymMatrix<T>::SymMatrix(SymMatrix<U> const& a_other)
: m_dimension(a_other.get_dim())
, m_data(new T[m_dimension])
{
    std::copy(a_other.m_data, a_other.m_data + a_other.get_dim(), m_data);
}

template <typename T>
SymMatrix<T>& SymMatrix<T>::operator=(SymMatrix<T> const& a_other)
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
template <typename U>
SymMatrix<T>& SymMatrix<T>::operator=(SymMatrix<U> const& a_other)
{
	void const* that = &a_other;
	void const* self = this;

	if (self != that) {
		SymMatrix c{a_other};
		swap(c);
	}

	return *this;
}


template <typename T>
SymMatrix<T>::~SymMatrix()
{
    delete[] m_data;
}

template <typename T>
T& SymMatrix<T>::operator()(size_t a_row, size_t a_col)
{
    assert(a_row < m_dimension && a_col < m_dimension);
    size_t index = translate_index(a_row, a_col);
    return m_data[index];
}

template <typename T>
T const& SymMatrix<T>::operator()(size_t a_row, size_t a_col) const
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

template <typename T>
template <typename U>
SymMatrix<T>& SymMatrix<T>::operator+=(SymMatrix<U> const& a_other)
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

template <typename T>
SymMatrix<T> operator+(SymMatrix<T> const& a_lVal, SymMatrix<T> const& a_rVal)
{
    assert(a_lVal.m_dimension == a_rVal.m_dimension);
    SymMatrix<T> new_matrix(a_lVal);
    new_matrix += a_rVal;
    return new_matrix;
}

template<typename U>
std::ostream& operator<<(std::ostream &a_out, const SymMatrix<U> &a_matrix)
{
    size_t n = find_n_from_sum(a_matrix.m_dimension);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (j <= i)
                a_out << a_matrix(i, j) << ",";
            else
                a_out << a_matrix(j, i) << ",";
        }
        a_out << "\n";
    }
    return a_out;
}
}//namespace matrix