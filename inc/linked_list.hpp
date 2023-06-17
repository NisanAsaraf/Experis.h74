#include <cstddef>
#include <iostream>
#include <optional>

namespace ds
{
    template <typename T>
    class Node
    {
    public:
        Node() = default;
        Node(const T& a_data);
        Node& operator=(const Node& a_other);
        ~Node() = default;
        
        Node& flip();

        T m_data;
        Node<T>* m_next = nullptr;
        Node<T>* m_prev = nullptr;
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

        Linked_List<T>& insert_after(const size_t& index, const T& a_data);
        Linked_List<T>& insert_before(const size_t& index, const T& a_data);

        T remove(const size_t& index);
        Linked_List<T>& insert_at(const size_t& a_index, const T& a_data);
        Linked_List<T>& swap(const size_t& a_index1, const size_t& a_index2);

        bool operator==(const Linked_List& a_other);
        bool operator!=(const Linked_List& a_other);
        bool operator<(const Linked_List& a_other);
        bool operator>(const Linked_List& a_other);
        bool operator<=(const Linked_List& a_other);
        bool operator>=(const Linked_List& a_other);

        Node<T>* get_head();
        Node<T>* get_tail();

        T pop_head();
        T pop_tail();

        bool contains(const T& a_data);

        Linked_List<T>& print();
        size_t size() const; 
        Linked_List& clear();

        Linked_List& reverse();
        size_t for_each(int (*action)(T&));

    private:
        Node<T>* m_head;
        Node<T>* m_tail;
    };

    template <typename T>
    T sum(Linked_List<T>& a_list);

    template <typename T>
    Linked_List<T>& splice(Linked_List<T>& a_list1, Linked_List<T>& a_list2);

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
    Node<T>::Node(const T& a_data)
    :m_data(a_data)
    {
    }

    template <typename T>
    Node<T>& Node<T>::flip()
    {
        Node<T>* temp = m_next;
        m_next = m_prev;
        m_prev = temp;
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
        Node<T>* current = m_head;
        while (current != nullptr) 
        {
            Node<T>* next = current->m_next;
            delete current;
            current = next;
        }
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
    T Linked_List<T>::pop_head()
    {
        if(m_head->m_next == m_tail)
        {
            throw std::runtime_error("Cannot pop head from an empty list");
        }

        Node<T>* current = m_head->m_next;
        current->m_next->m_prev = m_head;
        m_head->m_next = current->m_next;

        T data = current->m_data;
        delete current;

        return data;
    }

    template <typename T>
    T Linked_List<T>::pop_tail()
    {
        if(m_head->m_next == m_tail)
        {
            throw std::runtime_error("Cannot pop tail from an empty list");
        }

        Node<T>* current = m_tail->m_prev;
        current->m_prev->m_next = m_tail;
        m_tail->m_prev = current->m_prev;

        T data = current->m_data;
        delete current;

        return data;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::append(const T& a_data)
    {
        return push_tail(a_data);
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::insert_after(const size_t& a_index, const T& a_data)
    {
        if (a_index >= size()) 
        {
            throw std::out_of_range("Index out of bounds");
        }

        size_t position = 0;
        Node<T>* current = m_head->m_next;
        Node<T>* new_node = new Node<T>(a_data);

        while(current != m_tail)
        {
            if(position == a_index)
            {
                Node<T>* after = current->m_next;
                new_node->m_next = after;
                new_node->m_prev = current;
                after->m_prev = new_node;
                current->m_next = new_node;
                break;
            }
            current = current->m_next;
            position += 1;
        }
        return *this;
    }
    
    template <typename T>
    Linked_List<T>& Linked_List<T>::insert_before(const size_t& a_index, const T& a_data)
    {
        if (a_index >= size()) 
        {
            throw std::out_of_range("Index out of bounds");
        }
        size_t position = 0;
        Node<T>* current = m_head->m_next;
        Node<T>* new_node = new Node<T>(a_data);

        while(current != m_tail)
        {
            if(position == a_index)
            {
                Node<T>* before = current->m_prev;
                new_node->m_next = current;
                new_node->m_prev = before;
                before->m_next = new_node;
                current->m_prev = new_node;
                break;
            }
            current = current->m_next;
            position += 1;
        }
        return *this;
    }

    template <typename T>
    T Linked_List<T>::remove(const size_t& a_index)
    {
        if (a_index >= size()) 
        {
            throw std::out_of_range("Index out of bounds");
        }
        size_t position = 0;
        Node<T>* current = m_head->m_next;
        T data;
        while(current != m_tail)
        {
            if(position == a_index)
            {
                data = current->m_data;
                current->m_prev->m_next = current->m_next;
                current->m_next->m_prev = current->m_prev;
                delete current;
                break;
            }
            current = current->m_next;
            position += 1;
        }
        return data;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::insert_at(const size_t& a_index, const T& a_data)
    {
        if (a_index >= size()) 
        {
            throw std::out_of_range("Index out of bounds");
        }
        size_t position = 0;
        Node<T>* current = m_head->m_next;

        while(current != m_tail)
        {
            if(position == a_index)
            {
                current->m_data = a_data;
                break;
            }
            current = current->m_next;
            position += 1;
        }
        return *this;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::swap(const size_t& a_index1, const size_t& a_index2)
    {
        size_t list_size = size();
        if (a_index1 >= list_size || a_index2 >= list_size) 
        {
            throw std::out_of_range("Index out of bounds");
        }
        size_t position = 0;
        Node<T>* current = m_head->m_next;
        T tmp;
        Node<T>* Node1;
        Node<T>* Node2;

        while(current != m_tail)
        {
            if(position == a_index1)
            {
                Node1 = current;
                break;
            }
            current = current->m_next;
            position += 1;
        }

        current = m_head->m_next;
        while(current != m_tail)
        {
            if(position == a_index2)
            {
                Node2 = current;
                break;
            }
            current = current->m_next;
            position += 1;
        }

        tmp = Node1->m_data;
        Node1->m_data = Node2->m_data;
        Node2->m_data = tmp;
        return *this;
    }

    template <typename T>
    bool Linked_List<T>::contains(const T& a_data)
    {
        size_t position = 0;
        Node<T>* current = m_head->m_next;

        while(current != m_tail)
        {
            if(current->m_data == a_data)
            {
                return true;
            }
            current = current->m_next;
            position += 1;
        }
        return false;
    }
    
    template <typename T>
    Linked_List<T>& Linked_List<T>::reverse()
    {
        Node<T>* current = m_head->m_next;
        while(current != m_tail)
        {
            current->flip();
            current = current->m_prev;
        }

        m_head->m_next->m_next = m_tail;
        m_tail->m_prev->m_prev = m_head;

        Node<T>* temp = m_head->m_next;
        m_head->m_next = m_tail->m_prev;
        m_tail->m_prev = temp;

        return *this;
    }

    template <typename T>
    size_t Linked_List<T>::for_each(int (*action)(T&))
    {
        Node<T>* current = m_head->m_next;
        size_t count = 0;
        while (current != m_tail)
        {
            if(action(current->m_data) == 0)
            {
                break;
            }

            current = current->m_next;
            count++;
        }
        return count;
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

    template <typename T>
    bool Linked_List<T>::operator==(const Linked_List& a_other)
    {
        if (this == &a_other)
        {
            return true;
        }

        Node<T>* current_this = m_head->m_next;
        Node<T>* current_other = a_other.m_head->m_next;

        while (current_this != m_tail && current_other != a_other.m_tail)
        {
            if(current_this->m_data != current_other->m_data)
            {
                return false;
            }
            current_this = current_this->m_next;
            current_other = current_other->m_next;
        }

        return (current_this == m_tail && current_other == a_other.m_tail);
    }

    template <typename T>
    bool Linked_List<T>::operator!=(const Linked_List& a_other)
    {
        return !(*this == a_other);
    }

    template <typename T>
    bool Linked_List<T>::operator<(const Linked_List& a_other)
    {
        Node<T>* current_this = m_head->m_next;
        Node<T>* current_other = a_other.m_head->m_next;

        while (current_this != m_tail && current_other != a_other.m_tail)
        {
            if(current_this->m_data != current_other->m_data)
            {
                return false;
            }
            current_this = current_this->m_next;
            current_other = current_other->m_next;
        }

        return (current_this == m_tail && current_other != a_other.m_tail);
    }

    template <typename T>
    bool Linked_List<T>::operator>(const Linked_List& a_other)
    {
        Node<T>* current_this = m_head->m_next;
        Node<T>* current_other = a_other.m_head->m_next;

        while (current_this != m_tail && current_other != a_other.m_tail)
        {
            if (current_this->m_data != current_other->m_data)
            {
                return current_this->m_data > current_other->m_data;
            }
            current_this = current_this->m_next;
            current_other = current_other->m_next;
        }

        return current_this != m_tail && current_other == a_other.m_tail;
    }

    template <typename T>
    bool Linked_List<T>::operator<=(const Linked_List& a_other)
    {
        return !(*this > a_other);
    }

    template <typename T>
    bool Linked_List<T>::operator>=(const Linked_List& a_other)
    {
        return !(*this < a_other);
    }

    template <typename T>
    Node<T>* Linked_List<T>::get_head()
    {
        return m_head;
    }

    template <typename T>
    Node<T>* Linked_List<T>::get_tail()
    {
        return m_tail;
    }

    template <typename T>
    T sum(Linked_List<T>& a_list)
    {
        T sum = 0;
        Node<T>* current = a_list.get_head();
        Node<T>* tail = a_list.get_tail();
        while (current != tail)
        {
            sum += current->m_data;
            current = current->m_next;
        }
        return sum;
    }

    template <typename T>
    Linked_List<T>& splice(Linked_List<T>& a_list1, Linked_List<T>& a_list2) // splices list2 into list1
    {
        Node<T>* tail1 = a_list1.get_tail();
        Node<T>* head2 = a_list2.get_head();
        Node<T>* tail2 = a_list2.get_tail();

        tail1->m_prev->m_next = head2->m_next;
        head2->m_next->m_prev = tail1->m_prev;

        tail2->m_prev->m_next = tail1;
        tail1->m_prev = tail2->m_prev;

        head2->m_next = tail2;

        return a_list1;
    }

} // namespace ds
