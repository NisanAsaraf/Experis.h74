#include "../inc/periodic_executor.hpp"
#include <algorithm>

namespace threading
{  
    PeriodicTaskExecutor::PeriodicTaskExecutor(size_t a_initial_capacity = 16)
    {
        m_tasks.reserve(a_initial_capacity);
    }

    void PeriodicTaskExecutor::add(Task& a_Task, size_t a_delay , size_t a_period)
    {
        std::chrono::milliseconds period(a_period);
        std::chrono::time_point<std::chrono::steady_clock> due = std::chrono::steady_clock::now() + std::chrono::milliseconds(a_delay);;

        PeriodicTask newTask{&a_Task, due , period};

        m_tasks.emplace_back(newTask);
    }

    void PeriodicTaskExecutor::start()
    {
        if(m_state == State::Running)
        {
            return;
        }
        for(auto& pt:m_tasks)
        {
            pt.m_time_due = std::chrono::steady_clock::now() + pt.m_delay;
        }
        std::make_heap(m_tasks.begin(), m_tasks.end() , [](PeriodicTask task1, PeriodicTask task2){
            return task1.m_time_due < task2.m_time_due;
        });
        
    }

}//namespace threading
