#ifndef THREADING_TASK_
#define THREADING_TASK_

namespace threading
{
class Task
{
public:
    virtual ~Task() noexcept = default;
    virtual bool run() noexcept = 0;

protected:
    Task() = default;
    Task(Task const&) = delete;
    Task& operator=(Task const&) = delete;

};
}//namespace threading

#endif //THREADING_TASK_