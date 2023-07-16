#ifndef SMART_PTR
#define SMART_PTR

namespace ptr_utils
{

template<typename T>
class SmartPtr 
{
public:
    SmartPtr(T* ptr = nullptr);
    SmartPtr(const SmartPtr&); 
    SmartPtr(SmartPtr&&) noexcept; 
    T& operator*();
    const T& operator*() const; 
    T* operator->();
    const T* operator->() const;
    SmartPtr& operator=(const SmartPtr&); 
    SmartPtr& operator=(SmartPtr&&) noexcept; 
    ~SmartPtr();

private:
    T* ptr;
    size_t ref_count;
};

}//namespace ptr_utils

#include "inl/smart_ptr.hxx"

#endif //SMART_PTR