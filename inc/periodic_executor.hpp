#ifndef PERIODIC_EXEC_
#define PERIODIC_EXEC_
#include <string>
#include "task.hpp"
#include <vector>
#include <chrono>
#include "thread.hpp"
#include "thread.hxx"
#include <thread>

namespace threading
{

    struct PeriodicTask
    {
        Task* m_task;
        std::chrono::time_point<std::chrono::steady_clock> m_time_due;
        std::chrono::milliseconds m_period_ms;
        std::chrono::milliseconds m_delay;
    };

    bool operator<(PeriodicTask const& first, PeriodicTask const& second)
    {
        return first.m_time_due < second.m_time_due;
    }

class CyclicExecutor
{
public:
    using PeriodicTasks = std::vector<PeriodicTask>;

    CyclicExecutor(PeriodicTasks& a_tasks)
    :m_tasks{a_tasks}
    {

    }

    void operator()()noexcept
    {
        auto it = m_tasks.begin();
        std::this_thread::sleep_until(it->m_time_due);
        it->m_task;
    }

private:
    PeriodicTasks& m_tasks;
};
 

class PeriodicTaskExecutor
{
public:    
    PeriodicTaskExecutor(size_t a_initial_capacity);
    ~PeriodicTaskExecutor() = default;
    PeriodicTaskExecutor(PeriodicTaskExecutor const&) = delete;
    PeriodicTaskExecutor& operator=(PeriodicTaskExecutor const&) = delete;

    void add(Task& a_Task, size_t a_delay , size_t a_period);
    void start() noexcept;
    enum class State {Adding , Running};

private:
    std::vector<PeriodicTask> m_tasks;
    State m_state;
    Thread<CyclicExecutor> m_executor{m_tasks};
};

}//namespace threading
#endif