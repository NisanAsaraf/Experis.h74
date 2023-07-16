#include "../thread.hpp"

namespace threading
{

template <typename Func>
Thread<Func>::Thread(Func a_func)
:m_func(a_func)
{

}

template <typename Func>
Thread<Func>::~Thread()
{
    pthread_join(m_thread, nullptr);
}

template <typename Func>
void Thread<Func>::start()
{
    pthread_create(&m_thread, nullptr, &Thread::threadEntryPoint, this);
}


}//namespace threading
