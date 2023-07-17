#ifndef SMART_PTR
#define SMART_PTR

namespace ptr_utils
{

template<typename T>
class SmartPtr 
{
public:
    explicit SmartPtr(T* ptr = nullptr);
    SmartPtr(const SmartPtr&) = delete;
    SmartPtr(SmartPtr&&) noexcept; 
    T& operator*();
    T& operator*() const; 
    T* operator->() const noexcept;
    SmartPtr& operator=(const SmartPtr&) = delete;
    SmartPtr& operator=(SmartPtr&&) noexcept;
    template <typename U>
    SmartPtr<T>& operator=(SmartPtr<U>&& a_other) noexcept;

    bool operator==(const SmartPtr&); 
    friend bool operator==(SmartPtr const&, SmartPtr const&);
    /* 
    bool operator!() const; 
    */
    explicit operator bool() const;
    ~SmartPtr();
    /* print , swap */
private:
    T* ptr;
    size_t* ref_count;
};

template <typename T>
bool operator==(SmartPtr<T> const& left, SmartPtr<T> const& right)
{
    return left.ptr == right.ptr;
}

}//namespace ptr_utils

#include "inl/smart_ptr.hxx"

#endif //SMART_PTR