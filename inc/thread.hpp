#ifndef THREADING_THREAD_
#define THREADING_THREAD_

#include <pthread.h>
namespace threading
{

template <typename Func>
class Thread
{
public:
    Thread(Func a_func);
    ~Thread();

    void start();
private:
    Func m_func;
    pthread_t m_thread;

    static void* threadEntryPoint(void* arg) 
    {
        Thread* self = static_cast<Thread*>(arg);
        self->m_func();
        return nullptr;
    }

};

}//namespace threading
#endif //THREADING_THREAD_