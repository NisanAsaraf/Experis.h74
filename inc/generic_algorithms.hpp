#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>

template<typename T, typename Iter>
T sum(Iter begin, Iter end)
{
    T s = T{};
    while(begin != end) 
    {
        s += *begin;
        ++begin;
    }
    return s;
}

template<typename Iter>
void root(Iter begin, Iter end)
{
    while(begin != end) 
    {
        *begin = sqrt(*begin);
        ++begin;
    }    
}

template<typename Iterator>
void print(Iterator begin, Iterator end) {    
    while( begin != end ) 
    {
        std::cout << *begin << ", ";
        ++begin;
    }
    std::cout << '\n';
}

template<typename Container>
void print(Container & c) 
{
    print(c.begin(), c.end());

    typename Container::iterator it = c.begin();
    typename Container::iterator e = c.end();
    while( it != e ) 
    {
        std::cout << *it << ", ";
        ++it;
    }
    std::cout << '\n';
}

template<typename Container, typename T = typename Container::value_type>
std::ostream& operator<<(std::ostream& os, Container& c)
{
    size_t size = c.size();

    os << "[";
    auto it = c.begin();
    if (it != c.end()) 
    {
        os << *it;
        ++it;
        for (size_t i = 1; i < size; ++i, ++it) 
        {
            os << ", " << *it;
        }
    }
    os << "]";
    return os;
}