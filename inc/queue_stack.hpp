#include <cstddef>
#include "stack.hpp"

namespace ds
{
class QueueStack 
{
public:
    explicit QueueStack(size_t capacity);
    QueueStack(QueueStack const& a_original);
    QueueStack& operator=(const QueueStack& a_other);
    ~QueueStack();

    void enqueue(int value);
    int dequeue();

private:
    Stack m_enQstack;
    Stack m_deQstack;
};

} // namespace ds
