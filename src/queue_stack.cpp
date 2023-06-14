#include "../inc/queue_stack.hpp"

#include <cassert>

namespace ds 
{
QueueStack::QueueStack(size_t capacity) : m_enQstack(capacity), m_deQstack(capacity)
{

}

QueueStack::QueueStack(const QueueStack& a_original) = default;
QueueStack& QueueStack::operator=(const QueueStack& a_other) = default;

QueueStack::~QueueStack()
{
}

void QueueStack::enqueue(int value)
{
    m_enQstack.push(value);
}


int QueueStack::dequeue()
{
    if(m_deQstack.empty())
    {
        drain(m_enQstack, m_deQstack);
    } 

    return m_deQstack.pop();
}

}
