#include <cstddef>
#include <iostream>
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
        
        T m_data;
        Node<T>* m_next;
        Node<T>* m_prev;
    private:
    };

    template <typename T>
    class Linked_List
    {
    public:
        Linked_List();
        Linked_List(const Linked_List& a_data);
        Linked_List& operator=(const Linked_List& a_other);
        ~Linked_List();

        Linked_List<T>& push_head(const T& a_data);
        Linked_List<T>& push_tail(const T& a_data);
        Linked_List& append(const T& a_data);

        Linked_List<T>& print();

        size_t size() const; 
        Linked_List& clear();

    private:
        Node<T>* m_head;
        Node<T>* m_tail;
    };

    template <typename T>
    Node<T>::Node()
    :m_next(nullptr)
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
        }
        return *this;
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
    Linked_List<T>::Linked_List(const Linked_List& a_list)
    : m_head(new Node<T>())
    , m_tail(new Node<T>())
    {
        m_head->m_next = m_tail;
        m_tail->m_prev = m_head;

        Node<T>* current_node = a_list.m_head->m_next;

        while (current_node != a_list.m_tail)
        {
            this->push_tail(current_node->m_data);
            current_node = current_node->m_next;
        }
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::operator=(const Linked_List& a_other)
    {
        if (this != &a_other)
        {
            clear();

            Node<T>* current_node = a_other.m_head->m_next;
            while (current_node != a_other.m_tail)
            {
                push_tail(current_node->m_data);
                current_node = current_node->m_next;
            }
        }
        return *this;
    }

    template <typename T>
    Linked_List<T>::~Linked_List()
    {
        //clear();  
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::push_head(const T& a_data)
    {
        Node<T>* new_node = new Node<T>(a_data);

        new_node->m_prev = m_head;
        new_node->m_next = m_head->m_next;

        m_head->m_next->m_prev = new_node;
        m_head->m_next = new_node;

        return *this;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::push_tail(const T& a_data)
    {
        Node<T>* new_node = new Node<T>(a_data);

        new_node->m_prev = m_tail->m_prev;
        new_node->m_next = m_tail;

        m_tail->m_prev->m_next = new_node;
        m_tail->m_prev = new_node;

        return *this;
    }
    
    template <typename T>
    Linked_List<T>& Linked_List<T>::append(const T& a_data)
    {
        return push_tail(a_data);
    }

    template <typename T>
    size_t Linked_List<T>::size() const
    {
        size_t count = 0;
        Node<T>* current = m_head->m_next;
        while(current != m_tail)
        {
            count += 1;
            current = current->m_next;
        }
        return count;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::print() 
    {
        Node<T>* current = m_head->m_next;
        while (current != m_tail)
        {
            std::cout << current->m_data << '\n';
            current = current->m_next;
        }
        return *this;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::clear()
    {
        Node<T>* current = m_head->m_next;
        while (current != m_tail)
        {
            Node<T>* next_node = current->m_next;
            delete current;
            current = next_node;
        }
        m_head->m_next = m_tail;
        m_tail->m_prev = m_head;
        return *this;
    }

} // namespace ds



