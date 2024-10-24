#include "EventLoopThreadPoll.h"

EventLoopThreadPoll::EventLoopThreadPoll(EventLoop *baseLoop, const std::string &nameArg)
    : baseLoop_(baseLoop)
    , name_(nameArg)
    , started_(false)
    , numThreads_(0)
    , next_(0)
{

}

EventLoopThreadPoll::~EventLoopThreadPoll()
{

}

void EventLoopThreadPoll::start(const ThreadInitCallback &cb = ThreadInitCallback())
{
    started_ = true;

    for (int i = 0; i < numThreads_; ++i) 
    {
        std::string name = name_ + std::to_string(i);
        EventLoopThread *t = new EventLoopThread(cb, name);
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));
        loops_.push_back(t->startLoop());
    }

    if(numThreads_ == 0 && cb) 
    {
        cb(baseLoop_);
    }
}

EventLoop* EventLoopThreadPoll::getNextLoop()
{
    EventLoop *loop = baseLoop_;

    if (!loops_.empty())
    {
        loop = loops_[next_];
        ++next_;
        if (next_ >= loops_.size())
        {
            next_ = 0;
        }
    }
    
    return loop;
}

std::vector<EventLoop*> EventLoopThreadPoll::getAllLoops() 
{
    if (!loops_.empty()) {
        return loops_;
    }
    return std::vector<EventLoop*>(1, baseLoop_);
}