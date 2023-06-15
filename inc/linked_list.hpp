#include <cstddef>

namespace ds
{
    template <typename T>
    class Node
    {
    public:
        Node();
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
        Linked_List();
        Linked_List(const Linked_List& a_data);
        Linked_List& operator=(const Linked_List& a_other);
        ~Linked_List();

        const T& push_head(const T& a_data);
        const T& push_tail(const T& a_data);

        size_t size(); const

    private:
        Node<T>* m_head;
        Node<T>* m_tail;
    };

    template <typename T>
    Node<T>::Node()
    : m_data(nullptr)
    , m_next(nullptr)
    , m_prev(nullptr)
    {  
    }

    template <typename T>
    Node<T>::Node(const T& a_data)
        : m_data(a_data)
        , m_next(nullptr)
        , m_prev(nullptr)
    {
    }

    template <typename T>
    Node<T>::~Node()
    {
    }

    template <typename T>
    Node<T>& Node<T>::operator=(const Node<T>& a_other)
    {
        if (this != &a_other) 
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
    Linked_List<T>::Linked_List()
    : m_head(new Node<T>())
    , m_tail(new Node<T>())
    {  
        //other pointer values are defaulted to nullptr
        m_head->m_next = m_tail;
        m_tail->m_prev = m_head;
    }

    template <typename T>
    Linked_List<T>::Linked_List(const Linked_List& a_data)
    : m_head(new Node<T>())
    , m_tail(new Node<T>())
    {
        Node<T>* current = a_data.m_head;
        while(current != nullptr)
        {

        }
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::operator=(const Linked_List& a_other)
    {

    }

    template <typename T>
    const T&Linked_List<T>::push_head(const T& a_data)
    {
        Node<T>* new_node = new Node<T>(a_data);
        if(m_head->m_next == m_tail)
        {
            m_tail->m_next = new_node;
            m_head->m_prev = new_node;
            new_node->m_next = m_head;
            new_node->m_prev = m_tail;

        }else{
            new_node->m_prev = m_head->m_prev;
            m_head->m_prev->m_next = new_node;

            new_node->m_next = m_head;
            m_head->m_prev = new_node;
        }
    }

    template <typename T>
    const T& Linked_List<T>::push_tail(const T& a_data)
    {
        Node<T>* new_node = new Node<T>(a_data);

        if (m_head->m_next == m_tail)
        {
            m_tail->m_next = new_node;
            m_head->m_prev = new_node;
            new_node->m_next = m_tail;
            new_node->m_prev = m_head;
        }
        else
        {
            new_node->m_next = m_tail;
            new_node->m_prev = m_tail->m_prev;
            m_tail->m_prev->m_next = new_node;
            m_tail->m_prev = new_node;
        }
    }

    template <typename T>
    size_t Linked_List<T>::size()
    {
        Node<T>* current = m_head->m_next;
        while(current != m_tail)
        {
            count += 1;
            current = current->m_next;
        }
        return count;
    }

} // namespace ds



