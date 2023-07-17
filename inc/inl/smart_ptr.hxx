#ifndef SMART_PTR_HXX
#define SMART_PTR_HXX
#include "../smart_ptr.hpp"
#include <exception>
namespace ptr_utils
{
    template <typename T>
    SmartPtr<T>::SmartPtr(T* ptr) 
    : ptr(ptr)
    {
        try 
        {
            ref_count = new size_t(1);
        } 
        catch (const std::bad_alloc&) 
        {
            delete ptr; 
            throw;     
        }
    }

    template <typename T>
    SmartPtr<T>::SmartPtr(SmartPtr&& other) noexcept
    : ptr(other.ptr)
    , ref_count(other.ref_count)
    {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    template <typename T>   
    T& SmartPtr<T>::operator*()
    { 
        return *ptr; 
    }

    template <typename T>
    T& SmartPtr<T>::operator*() const 
    {
        return *ptr; 
    }

    template <typename T>
    T* SmartPtr<T>::operator->()const noexcept
    {
        return ptr; 
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
    template <typename U>
    SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr<U>&& a_other) noexcept
    {
        delete ptr;
        ptr = a_other.ptr;
        ref_count = a_other.ref_count;
        a_other.ptr = nullptr;
        a_other.ref_count = nullptr;
    }

    template <typename T>
    SmartPtr<T>::~SmartPtr() 
    {
        if(ref_count)
        {
            if (--*ref_count == 0)
            {
                delete ptr;
            }
        }
    }

    template <typename T>
    bool SmartPtr<T>::operator==(const SmartPtr& other)
    {
        return this->ptr == other.ptr;
    }

/*     template <typename T>
    bool SmartPtr<T>::operator==(SmartPtr& other)
    {
        return this->ptr == other.ptr;
    }

    template <typename T>
    bool SmartPtr<T>::operator!() const 
    {
        return ptr == nullptr;
    } 
 */
    template <typename T>
    SmartPtr<T>::operator bool() const
    {
        return ptr != nullptr;
    }
}//namespace ptr_utils
#endif //SMART_PTR_HXX