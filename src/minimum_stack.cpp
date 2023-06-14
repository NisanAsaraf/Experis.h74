#include "../inc/minimum_stack.hpp"
#include <climits>
#include <cassert>

namespace ds 
{
MinimumStack::MinimumStack(size_t capacity) : m_stack(capacity), m_minStack(capacity) 
{
    
}

MinimumStack::MinimumStack(MinimumStack const& a_original) = default;
MinimumStack& MinimumStack::operator=(const MinimumStack& a_other) = default;

MinimumStack::~MinimumStack() = default;

void MinimumStack::push(int value) 
{
    m_stack.push(value);
    if (m_minStack.empty() || value < m_minStack.peek()) 
    {
        m_minStack.push(value);
    }
}

int MinimumStack::pop() 
{  
    int top = m_stack.pop();
    
    if (top == m_minStack.peek()) 
    {
        m_minStack.pop();
    }

    return top;
}

bool MinimumStack::empty() const
{
    return m_stack.empty();
}

void MinimumStack::printMin() const 
{
    m_minStack.print();
}

int MinimumStack::getMinimum() 
{
    assert(not m_minStack.empty());
    return m_minStack.peek();
}

}
