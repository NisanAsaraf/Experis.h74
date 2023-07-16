#include "../../inc/mu_test.h"
#include "../../inc/thread.hpp"
#include "../../inc/inl/thread.hxx"
#include "../../inc/task.hpp"
#include <iostream>
#include <functional>

using namespace threading;

void printNum()
{
    for(int i = 0 ; i < 10 ; i ++)
    {
        std::cout << i << '\n';
    }
}

class PrintNum
{
public:
    void operator()() 
    {
        for (int i = 0; i < 10; i++) 
        {
            std::cout << i << '\n';
        }
    }
};
template <typename Func>
class CountedTask : public Task
{
public:
    CountedTask(int a_count , std::string a_str , Func a_func)
    :m_count{a_count}
    ,m_str{a_str}
    ,m_func{a_func}
    {
    }

    bool run() noexcept override
    {
        std::cout << "task" << m_str << ":" << m_count << '\n';
        m_func();
        --m_count;
        return m_count > 0;
    }

private:
    int m_count;
    std::string m_str;
    Func m_func;
};

template <typename Func>
Task* make_task(int a_count , std::string a_str , Func a_func)
{
    return new CountedTask(a_count, a_str , a_func);
}

BEGIN_TEST(thread_test_function)
    Thread<void(*)()> func_thread(printNum);
    func_thread.start();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(thread_test_function_object)
    PrintNum printObj;
    Thread<std::function<void()>> func_thread(printObj);
    func_thread.start();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(thread_test_lambda)
    Thread<void(*)()> func_thread([](){
        for (int i = 0; i < 10; i++) 
        {
            std::cout << i << '\n';
        }
    }
    );
    func_thread.start();
    ASSERT_THAT(true);
END_TEST

BEGIN_TEST(test_task)
    auto t = make_task(10, "printnumbers", printNum);
    t->run();
    t->run();
    ASSERT_THAT(true);
END_TEST

TEST_SUITE(決して道から外れてはいけません)
TEST(thread_test_function)
TEST(thread_test_function_object)
TEST(thread_test_lambda)
TEST(test_task)

END_SUITE
