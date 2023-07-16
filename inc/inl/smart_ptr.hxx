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
    SmartPtr<T>::SmartPtr(const SmartPtr& other) 
    : ptr(other.ptr)
    , ref_count(other.ref_count)
    {
        try 
        {
            if (ref_count) 
            {
                ++(*ref_count);
            }
        } 
        catch (...) 
        {
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
        if (ptr == nullptr) 
        {
            throw std::runtime_error("Dereferencing a null pointer!");
        }
        return *ptr; 
    }

    template <typename T>
    const T& SmartPtr<T>::operator*() const 
    {
        if (ptr == nullptr) 
        {
            throw std::runtime_error("Dereferencing a null pointer!");
        }
        return *ptr; 
    }

    template <typename T>
    T* SmartPtr<T>::operator->()
    {
        if (ptr == nullptr) 
        {
            throw std::runtime_error("Dereferencing a null pointer!");
        }
        return ptr; 
    }

    template <typename T>
    const T* SmartPtr<T>::operator->() const
    { 
        if (ptr == nullptr) 
        {
            throw std::runtime_error("Dereferencing a null pointer!");
        }
        return ptr; 
    }

    template <typename T>
    SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr& other) 
    {
        if (this != &other) 
        {
            try 
            {
                if (other.ptr == nullptr) 
                {
                    throw std::runtime_error("Dereferencing a null pointer!");
                }

                ptr = other.ptr;
                ref_count = other.ref_count;

                ++*ref_count;
            } 
            catch (const std::runtime_error& e) 
            {
                throw e;
            }
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

    template <typename T>
    bool SmartPtr<T>::operator==(SmartPtr& other)
    {
        return this->ptr == other.ptr;
    }

    template <typename T>
    bool SmartPtr<T>::operator!() const 
    {
        return ptr == nullptr;
    }

}//namespace ptr_utils
#endif //SMART_PTR_HXX