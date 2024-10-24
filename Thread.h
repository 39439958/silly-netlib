#pragma once

#include <string>
#include <functional>
#include <memory>
#include <thread>
#include <atomic>

class Thread
{
public:
    using ThreadFunc = std::function<void()>;
    
    explicit Thread(ThreadFunc func, const std::string &name);
    ~Thread();

    void start();
    void join();
    
    void setDefaultName();

    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const std::string &name() const { return name_; }

    static int numCreated() { return numCreated_; }

private:
    bool started_;
    bool joined_;
    ThreadFunc func_;

    std::shared_ptr<std::thread> thread_;
    pid_t tid_;

    std::string name_;

    static std::atomic_int numCreated_;
};