#include "../inc/stack.hpp"
#include <cstdio>
#include <cstddef>
#include <cassert>
#include <cstring>
#include <iostream>

namespace ds
{

Stack::Stack(size_t a_capacity)
: m_capacity(a_capacity)
, m_top(0)
, m_data(new int[a_capacity])
{
}

Stack::Stack(const Stack& a_origin)
: m_capacity(a_origin.m_capacity)
, m_top(a_origin.m_top)
, m_data(new int[a_origin.m_capacity])
{
    std::memcpy(m_data, a_origin.m_data, m_top * sizeof(int));
}

Stack::~Stack()
{
    delete[] m_data;
}

Stack& Stack::operator=(const Stack& a_other)
{
    if (this != &a_other)
    {
        Stack temp(a_other); 

        std::swap(m_capacity, temp.m_capacity);
        std::swap(m_top, temp.m_top);
        std::swap(m_data, temp.m_data);
    }

    return *this;
}


void Stack::push(int a_value)
{
    assert(size() != m_capacity);
    m_data[m_top++] = a_value;
}

int Stack::pop()
{
    assert(not empty());
    return m_data[--m_top];
}

int Stack::peek() const
{
    assert(not empty());
    return m_data[m_top - 1];
}

Stack& Stack::operator+=(Stack& a_other)
{
    size_t otherSize = a_other.m_top;
    size_t newSize = m_top + otherSize;
    int* newData = new int[newSize];

    //memmove cant be done
    std::memcpy(newData, m_data, m_top * sizeof(int));
    std::memcpy(newData + m_top, a_other.m_data, otherSize * sizeof(int));
    
    delete[] m_data;
    
    m_data = newData;
    m_capacity = newSize;
    m_top = newSize;
    
    a_other.m_top = 0; //"empty it"
    return *this;
}


void Stack::print() const
{
    std::cout << "Stack: [";
    for(size_t i = 0; i < m_top; ++i)
    {
        if(i == m_top - 1)
        {
            std::cout << m_data[i];
            break;
        }

        std::cout << m_data[i] << ", ";
    }

    std::cout << "]\n";
}

bool Stack::empty() const
{
    return m_top == 0;
}

bool Stack::full() const
{
    return m_top == m_capacity;
}

size_t Stack::size() const
{
    return m_top;
}

void drain(Stack& a_stackA, Stack& a_stackB)
{
    while(not a_stackA.empty())
    {
        a_stackB.push(a_stackA.pop());
    }
}


} // namespace ds
