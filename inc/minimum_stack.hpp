#include <cstddef>
#include "stack.hpp"

namespace ds
{

class MinimumStack 
{
public:
    explicit MinimumStack(size_t capacity);
    MinimumStack(MinimumStack const& a_original);
    MinimumStack& operator=(const MinimumStack& a_other);
    ~MinimumStack();

    void push(int value);
    int pop();
    int getMinimum();
    bool empty() const;
    void printMin() const;
private:
    Stack m_stack;
    Stack m_minStack;
};

} // namespace ds
