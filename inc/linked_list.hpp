#include <cstddef>

namespace ds
{
    template <typename T>
    class Node
    {
    public:
        Node(const T& a_data);
        Node& operator=(const Node& a_other);
        ~Node();

    private:
        T m_data;
        Node<T>* m_next;
        Node<T>* m_prev;
    };
    
    template <typename T>
    class Linked_List
    {
    public:
        Linked_List(const Linked_List& a_data);
        Linked_List& operator=(const Linked_List& a_other);
        ~Linked_List();

    private:
        Node<T>* m_head;
        Node<T>* m_tail;
    };
















    template <typename T>
    Node<T>::Node(const T& a_data)
        : m_data(a_data)
        , m_next(nullptr)
        , m_prev(nullptr)
    {
    }

    template <typename T>
    Node<T>& Node<T>::operator=(const Node<T>& a_other)
    {
        if (this != &a_other) // Check for self-assignment
        {
            m_data = a_other.m_data;
            m_next = a_other.m_next;
            m_prev = a_other.m_prev;

            if (m_next)
                m_next->m_prev = this;
            if (m_prev)
                m_prev->m_next = this;
            return *this;
        }
    }

    template <typename T>
    Node<T>::~Node()
    {

    }

} // namespace ds
