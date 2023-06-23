#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>
#include <cstring>

namespace pets
{
class Cat
{
    public:
    Cat();
    Cat(const std::string& name);
    ~Cat();

    const std::string& operator*() const;
    std::string& operator*();
    friend std::ostream& operator<<(std::ostream& os, const Cat& cat);
    private:
    std::string m_name;
};

Cat::Cat(const std::string& name)
: m_name(name)
{
}

Cat::~Cat()
{
}

const std::string& Cat::operator*() const 
{
    return m_name;
}

std::string& Cat::operator*()
{
    return m_name;
}

std::ostream& operator<<(std::ostream& os, const Cat& cat)
{
    os<<*cat;
    return os;
}
}//namespace pets

template<typename Container, typename Iter = typename Container::const_iterator>
std::ostream& operator<<(std::ostream& os, Container const& c)
{
    os << '[';
    Iter it = c.begin();
    if (it != c.end())
    {
        os << *it;
        ++it;
    }
    while (it != c.end())
    {
        os << ", " << *it;
        ++it;
    }
    os << "]\n";

    return os;
}

template<typename Iterator>
void print(Iterator begin, Iterator end) 
{   
    std::cout << '[';
    if (begin != end)
    {
        std::cout << *begin;
        ++begin;
    }
    while( begin != end ) 
    {
        std::cout << ", "<< *begin;
        ++begin;
    }
    std::cout << "]\n";
}

template<typename Container>
void print(Container & c) 
{
    print(c.begin(), c.end());
}

template<typename T = int,typename Iter>
int mul(Iter begin, Iter end)
{
    T mul = *begin;
    ++begin;
    while(begin != end) 
    {
        mul *= *begin;
        ++begin;
    }
    return mul;
}

template<typename T = int,typename Iter>
int add(Iter begin, Iter end)
{
    T add = 0;
    while(begin != end) 
    {
        add += *begin;
        ++begin;
    }
    return add;
}

template<typename T = int, typename Iter>
T foldit(Iter begin, Iter end, int (*f)(Iter, Iter))
{
    return f(begin, end);
}

template<typename Container>
Container merge(Container const& a, Container const& b ,Container & c) 
{
    std::merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
    std::sort(c.begin(), c.end());
    return c;
}

template<typename Container>
void replace_with_left_bigger(Container& v) 
{
    typename Container::iterator begin = v.begin();
    typename Container::iterator end = v.end();
    

}
