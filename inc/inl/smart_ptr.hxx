#ifndef SMART_PTR_HXX
#define SMART_PTR_HXX
#include "../smart_ptr.hpp"

namespace ptr_utils
{
    template <typename T>
    SmartPtr<T>::SmartPtr(T* ptr) 
    : ptr(ptr)
    ,ref_count(0)
    {

    }

    template <typename T>
    SmartPtr<T>::SmartPtr(const SmartPtr& other) 
    : ptr(other.ptr)
    , ref_count(other.ref_count)
    {

    }

    template <typename T>
    SmartPtr<T>::SmartPtr(SmartPtr&& other) noexcept
    : ptr(other.ptr)
    , ref_count(other.ref_count)
    {
        other.ptr = nullptr;
        other.ref_count = 0;
    }

    template <typename T>   
    T& SmartPtr<T>::operator*()
    { 
        return *ptr; 
    }

    template <typename T>
    const T& SmartPtr<T>::operator*() const 
    {
        return *ptr; 
    }

    template <typename T>
    T* SmartPtr<T>::operator->()
    {
        return ptr;
    }

    template <typename T>
    const T* SmartPtr<T>::operator->() const
    { 
        return ptr; 
    }

    template <typename T>
    SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& other) 
    {
        if (this != &other) 
        {
            ptr = other.ptr;
            ref_count = other.ref_count;
            
            ++ref_count;
        }
        return *this;
    }

    template <typename T>
    SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr&& other) noexcept
    {
        if (this != &other) 
        {
            ptr = other.ptr;
            ref_count = other.ref_count;

            other.ptr = nullptr;
            other.ref_count = 0;
        }
        return *this;
    }

    template <typename T>
    SmartPtr<T>::~SmartPtr() 
    {
        if (--ref_count == 0) 
        {
            delete ptr;
        }
    }
}//namespace ptr_utils
#endif //SMART_PTR_HXX