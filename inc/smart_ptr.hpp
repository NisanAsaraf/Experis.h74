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
    bool operator==(const SmartPtr&); 
/*     bool operator==(SmartPtr&);
    bool operator!() const; */
    explicit operator bool() const;
    ~SmartPtr();

private:
    T* ptr;
    size_t* ref_count;
};

}//namespace ptr_utils

#include "inl/smart_ptr.hxx"

#endif //SMART_PTR