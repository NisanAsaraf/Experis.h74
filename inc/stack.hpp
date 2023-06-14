#include <cstddef>

namespace ds
{

class Stack
{
public:
    explicit Stack(size_t a_capacity);
    Stack(const Stack& a_origin);
    Stack& operator=(const Stack& a_other);
    ~Stack();

    void push(int a_value);
    int pop();
    int peek() const;

    void print() const;
    size_t size() const;
    bool empty() const;
    bool full() const;
    Stack& operator+=(Stack& a_other);

private:
    size_t m_capacity;
    size_t m_top;
    int* m_data;
};

void info(Stack const& a_stack);
void drain(Stack& a_stackA, Stack& a_stackB);

} // namespace ds
