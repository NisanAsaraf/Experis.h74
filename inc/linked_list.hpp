#include <cstddef>
#include <iostream>
#include <optional>
#include <cassert>

namespace ds
{
    template <typename T>
    class Node
    {
    public:
        Node() = default;
        Node(const T& a_data);
        Node& operator=(const Node& a_other);
        ~Node();
        
        Node& flip();

        T& data();
        Node<T>*& next();
        Node<T>*& prev();

    private:
        T m_data;
        Node<T>* m_next = nullptr;
        Node<T>* m_prev = nullptr;
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

        Linked_List<T>& insert_after(const T& a_look, const T& a_put);
        Linked_List<T>& insert_after_index(const size_t& a_index, const T& a_data);
        Linked_List<T>& insert_before(const T& a_look, const T& a_put);
        Linked_List<T>& insert_before_index(const size_t& index, const T& a_data);
        Linked_List<T>& remove(const T& a_data);

        T remove_at_index(const size_t& index);
        Linked_List<T>& insert_at_index(const size_t& a_index, const T& a_data);
        Linked_List<T>& swap(const T& a_look, const T& a_put);
        Linked_List<T>& swap_at_index(const size_t& a_index1, const size_t& a_index2);

        bool is_empty();

        bool operator==(const Linked_List& a_other) const;
        bool operator!=(const Linked_List& a_other) const;
        bool operator<(const Linked_List& a_other) const;
        bool operator>(const Linked_List& a_other) const;
        bool operator<=(const Linked_List& a_other) const;
        bool operator>=(const Linked_List& a_other) const;

        Node<T>* get_head();
        Node<T>* get_tail();
        Node<T>* find_node(const T& a_data);

        T pop_head();
        T pop_tail();

        bool contains(const T& a_data);

        Linked_List<T>& print();
        size_t size() const;
        void set_size(size_t);
        Linked_List& clear();

        Linked_List& reverse();
        template <typename C>
        size_t for_each(int (*action)(T&,C&), C&);

        template <typename C>
        friend C sum(Linked_List<C>& a_list);

        template <typename C>
        friend Linked_List<C>& splice(Linked_List<C>& a_list1, Linked_List<C>& a_list2);

    private:
        Node<T>* m_head;
        Node<T>* m_tail;
        size_t m_size;
    };

    template <typename T>
    Node<T>& Node<T>::operator=(const Node<T>& a_other)
    {
        if (this != &a_other) 
        {
            m_data = a_other.m_data;
            m_next = a_other.m_next;
            m_prev = a_other.m_prev;
        }
        return *this;
    }

    template <typename T>
    Node<T>::Node(const T& a_data)
    :m_data(a_data)
    {
    }

    template <typename T>
    Node<T>::~Node()
    {
        if(not (this == m_next || this == m_prev))
        {
            m_next->m_prev = m_prev;
            m_prev->m_next = m_next;
        }
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
    T& Node<T>::data()
    {
        return m_data;
    }

    template <typename T>
    Node<T>*& Node<T>::next()
    {
        return m_next;
    }

    template <typename T>
    Node<T>*& Node<T>::prev()
    {
        return m_prev;
    }

    template <typename T>
    Linked_List<T>::Linked_List()
    : m_head(new Node<T>())
    , m_tail(new Node<T>())
    , m_size(0)
    {  
        m_head->next() = m_tail;
        m_head->prev() = m_head;
        m_tail->prev() = m_head;
        m_tail->next() = m_tail;
    }

    template <typename T>
    Linked_List<T>::Linked_List(const Linked_List& a_list)
    : m_head(new Node<T>())
    , m_tail(new Node<T>())
    , m_size(0)
    {
        m_head->next() = m_tail;
        m_head->prev() = m_head;
        m_tail->prev() = m_head;
        m_tail->next() = m_tail;

        Node<T>* current_node = a_list.m_head->next();

        while (current_node != a_list.m_tail)
        {
            T new_data = current_node->data();
            this->push_tail(new_data);
            current_node = current_node->next();
        }
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::operator=(const Linked_List& a_other)
    {
        if (this != &a_other)
        {
            clear();

            Node<T>* current_node = a_other.m_head->next();
            while (current_node != a_other.m_tail)
            {
                push_tail(current_node->data());
                current_node = current_node->next();
            }
        }
        return *this;
    }

    template <typename T>
    Linked_List<T>::~Linked_List()
    {
        Node<T>* current = m_head->next();
        while (current != m_tail)
        {
            Node<T>* next = current->next();
            delete current;
            current = next;
        }

        delete m_head;
        delete m_tail;
    }


    template <typename T>
    bool Linked_List<T>::is_empty()
    {
        return size() == 0;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::push_head(const T& a_data)
    {

        Node<T>* new_node = new Node<T>(a_data);

        new_node->prev() = m_head;
        new_node->next() = m_head->next();

        m_head->next()->prev() = new_node;
        m_head->next() = new_node;
        m_size += 1;

        return *this;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::push_tail(const T& a_data)
    {
        Node<T>* new_node = new Node<T>(a_data);

        new_node->prev() = m_tail->prev();
        new_node->next() = m_tail;

        m_tail->prev()->next() = new_node;
        m_tail->prev() = new_node;

        m_size += 1;

        return *this;
    }

    template <typename T>
    T Linked_List<T>::pop_head()
    {
        if (is_empty())
        {
            return T();
        }

        Node<T>* current = m_head->next();
        current->next()->prev() = m_head;
        m_head->next() = current->next();

        T data = current->data();
        delete current;

        m_size -= 1;
        return data;
    }

    template <typename T>
    void Linked_List<T>::set_size(size_t new_size)
    {
        m_size = new_size;
    }

    template <typename T>
    T Linked_List<T>::pop_tail()
    {
        if (is_empty())
        {
            return T();
        }

        Node<T>* current = m_tail->prev();
        current->prev()->next() = m_tail;
        m_tail->prev() = current->prev();

        T data = current->data();
        delete current;

        m_size -= 1;
        return data;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::append(const T& a_data)
    {
        return push_tail(a_data);
    }


    template <typename T>
    Node<T>* Linked_List<T>::find_node(const T& a_data)
    {
        assert(!is_empty());

        Node<T>* current = m_head->next();

        while(current != m_tail)
        {
            if(current->data() == a_data)
            {
                return current;
            }
            current = current->next();
        }
        return current;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::insert_before(const T& a_look, const T& a_put)
    {
        if (is_empty())
        {
            return *this;
        }

        Node<T>* found = find_node(a_look);

        if(found != m_tail)
        {
            Node<T>* new_node = new Node<T>(a_put);
            Node<T>* before = found->prev();

            new_node->next() = found;
            new_node->prev() = before;
            before->next() = new_node;
            found->prev() = new_node;
            m_size += 1;
        }
        return *this;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::insert_after(const T& a_look, const T& a_put)
    {
        if (is_empty())
        {
            return *this;
        }

        Node<T>* found = find_node(a_look);
        
        if(found != m_tail)
        {
            Node<T>* new_node = new Node<T>(a_put);
            Node<T>* after = found->next();

            new_node->next() = after;
            new_node->prev() = found;
            after->prev() = new_node;
            found->next() = new_node;
            m_size += 1;
        }      
        
        return *this;
    }
    
    template <typename T>
    Linked_List<T>& Linked_List<T>::insert_after_index(const size_t& a_index, const T& a_data)
    {
        if (a_index >= size())
        {
            return *this;
        }

        size_t position = 0;
        Node<T>* current = m_head->next();
        Node<T>* new_node = new Node<T>(a_data);

        while(current != m_tail)
        {
            if(position == a_index)
            {
                Node<T>* after = current->next();
                new_node->next() = after;
                new_node->prev() = current;
                after->prev() = new_node;
                current->next() = new_node;
                break;
            }
            current = current->next();
            position += 1;
        }
        m_size += 1;

        return *this;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::insert_before_index(const size_t& a_index, const T& a_data)
    {
        if (a_index >= size())
        {
            return *this;
        }

        size_t position = 0;
        Node<T>* current = m_head->next();
        Node<T>* new_node = new Node<T>(a_data);

        while(current != m_tail)
        {
            if(position == a_index)
            {
                Node<T>* before = current->prev();
                new_node->next() = current;
                new_node->prev() = before;
                before->next() = new_node;
                current->prev() = new_node;
                break;
            }
            current = current->next();
            position += 1;
        }
        m_size += 1;
        return *this;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::remove(const T& a_data)
    {
        if (is_empty())
        {
            return *this;
        }

        Node<T>* found = find_node(a_data);
        
        if(found != m_tail)
        {
            delete found;
            m_size -= 1;
        }

        return *this;
    }

    template <typename T>
    T Linked_List<T>::remove_at_index(const size_t& a_index)
    {
        if (a_index >= size()) 
        {
            throw std::out_of_range("Index out of bounds");
        }
        size_t position = 0;
        Node<T>* current = m_head->next();
        T data;
        while(current != m_tail)
        {
            if(position == a_index)
            {
                data = current->data();
                current->prev()->next() = current->next();
                current->next()->prev() = current->prev();
                delete current;
                break;
            }
            current = current->next();
            position += 1;
        }
        m_size -= 1;
        return data;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::insert_at_index(const size_t& a_index, const T& a_data)
    {
        if (a_index >= size()) 
        {
            throw std::out_of_range("Index out of bounds");
        }
        size_t position = 0;
        Node<T>* current = m_head->next();

        while(current != m_tail)
        {
            if(position == a_index)
            {
                current->data() = a_data;
                break;
            }
            current = current->next();
            position += 1;
        }
        m_size += 1;
        return *this;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::swap(const T& a_look, const T& a_put)
    {
        if (is_empty())
        {
            return *this;
        }

        Node<T>* found = find_node(a_look);

        if(found != m_tail)
        {
            found->data() = a_put;
        }
        return *this;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::swap_at_index(const size_t& a_index1, const size_t& a_index2)
    {
        size_t list_size = size();
        if (a_index1 >= list_size || a_index2 >= list_size) 
        {
            return *this;
        }

        size_t position = 0;
        Node<T>* current = m_head->next();
        T tmpData;
        Node<T>* Node1;
        Node<T>* Node2;

        while(current != m_tail)
        {
            if(position == a_index1)
            {
                Node1 = current;
                break;
            }
            current = current->next();
            position += 1;
        }

        current = m_head->next();
        while(current != m_tail)
        {
            if(position == a_index2)
            {
                Node2 = current;
                break;
            }
            current = current->next();
            position += 1;
        }

        tmpData = Node1->data();
        Node1->data() = Node2->data();
        Node2->data() = tmpData;
        return *this;
    }

    template <typename T>
    bool Linked_List<T>::contains(const T& a_data)
    {
        if (is_empty())
        {
            return false;
        }

        Node<T>* found = find_node(a_data);

        if(found != m_tail)
        {
            return true;
        }

        return false;
    }
    
    template <typename T>
    Linked_List<T>& Linked_List<T>::reverse()
    {
        Node<T>* current = m_head->next();
        while(current != m_tail)
        {
            current->flip();
            current = current->prev();
        }

        m_head->next()->next() = m_tail;
        m_tail->prev()->prev() = m_head;

        Node<T>* temp = m_head->next();
        m_head->next() = m_tail->prev();
        m_tail->prev() = temp;

        return *this;
    }

    template <typename T>
    template <typename C>
    size_t Linked_List<T>::for_each(int (*action)(T&,C&), C& a_context)
    {
        Node<T>* current = m_head->next();
        size_t count = 0;
        while (current != m_tail)
        {
            if(action(current->data(), a_context) == 0)
            {
                break;
            }

            current = current->next();
            count++;
        }
        return count;
    }

    template <typename T>
    size_t Linked_List<T>::size() const
    {
        return m_size;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::print() 
    {
        Node<T>* current = m_head->next();
        while (current != m_tail)
        {
            std::cout << current->data() << '\n';
            current = current->next();
        }
        return *this;
    }

    template <typename T>
    Linked_List<T>& Linked_List<T>::clear()
    {
        Node<T>* current = m_head->next();
        while (current != m_tail)
        {
            Node<T>* next_node = current->next();
            delete current;
            current = next_node;
        }
        m_head->next() = m_tail;
        m_tail->prev() = m_head;
        m_size = 0;
        return *this;
    }

    template <typename T>
    bool Linked_List<T>::operator==(const Linked_List& a_other) const
    {
        if (this == &a_other)
        {
            return true;
        }

        Node<T>* current_this = m_head->next();
        Node<T>* current_other = a_other.m_head->next();

        while (current_this != m_tail && current_other != a_other.m_tail)
        {
            if(current_this->data() != current_other->data())
            {
                return false;
            }
            current_this = current_this->next();
            current_other = current_other->next();
        }

        return (current_this == m_tail && current_other == a_other.m_tail);
    }

    template <typename T>
    bool Linked_List<T>::operator!=(const Linked_List& a_other) const
    {
        return !(*this == a_other);
    }

    template <typename T>
    bool Linked_List<T>::operator<(const Linked_List& a_other) const
    {
        Node<T>* current_this = m_head->next();
        Node<T>* current_other = a_other.m_head->next();

        while (current_this != m_tail && current_other != a_other.m_tail)
        {
            if(current_this->data() != current_other->data())
            {
                return false;
            }
            current_this = current_this->next();
            current_other = current_other->next();
        }

        return (current_this == m_tail && current_other != a_other.m_tail);
    }

    template <typename T>
    bool Linked_List<T>::operator>(const Linked_List& a_other) const
    {
        Node<T>* current_this = m_head->next();
        Node<T>* current_other = a_other.m_head->next();

        while (current_this != m_tail && current_other != a_other.m_tail)
        {
            if (current_this->data() != current_other->data())
            {
                return current_this->data() > current_other->data();
            }
            current_this = current_this->next();
            current_other = current_other->next();
        }

        return current_this != m_tail && current_other == a_other.m_tail;
    }

    template <typename T>
    bool Linked_List<T>::operator<=(const Linked_List& a_other) const
    {
        return !(*this > a_other);
    }

    template <typename T> 
    bool Linked_List<T>::operator>=(const Linked_List& a_other) const
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
            sum += current->data();
            current = current->next();
        }
        return sum;
    }

    template <typename T>
    Linked_List<T>& splice(Linked_List<T>& a_list1, Linked_List<T>& a_list2) // splices list2 into list1
    {
        Node<T>* tail1 = a_list1.get_tail();
        Node<T>* head2 = a_list2.get_head();
        Node<T>* tail2 = a_list2.get_tail();

        tail1->prev()->next() = head2->next();
        head2->next()->prev() = tail1->prev();

        tail2->prev()->next() = tail1;
        tail1->prev() = tail2->prev();

        head2->next() = tail2;

        a_list1.set_size(a_list1.size() + a_list2.size());
        return a_list1;
    }


} // namespace ds
