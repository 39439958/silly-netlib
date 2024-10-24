#include "Thread.h"
#include "CurrentThread.h"
#include <semaphore.h>

std::atomic_int Thread::numCreated_(0);

Thread::Thread(ThreadFunc func, const std::string &name = std::string())
    : started_(false)
      ,joined_(false)
      ,tid_(0)
      ,func_(std::move(func))
      ,name_(name)
{
    setDefaultName();
}

Thread::~Thread() {
    // 如果当前在子线程中，线程状态已经开始且未被joined同步，
    // 则detach分离一下，防止程序终止
    if (started_ && !joined_)
    {
        thread_->detach();
    }
}

void Thread::start()
{
    started_ = true;
    sem_t sem;
    sem_init(&sem, false, 0);

    thread_ = std::shared_ptr<std::thread>(new std::thread([&](){
        tid_ = CurrentThread::tid();
        sem_post(&sem);

        func_();
    }));

    
    sem_wait(&sem);
}

void Thread::join()
{
    joined_ = true;
    thread_->join();
}

void Thread::setDefaultName()
{
    int num = ++numCreated_;
    if (name_.empty())
    {
        name_ = "Thread" + std::to_string(num);
    }
}