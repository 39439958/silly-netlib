#pragma once

#include "noncopyable.h"
#include "Timestamp.h"

#include <vector>
#include <unordered_map>


class Channel;
class EventLoop;

// silly库中的多路事件分发器的核心IO复用模块
class Poller : noncopyable {
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop *loop);
    virtual ~Poller();

    // 给所有IO复用保留统一的接口
    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;
    virtual void updateChannel(Channel *Channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;
 
    bool hasChannel(Channel *channel) const;

    static Poller* newDefaultPoller(EventLoop *loop);

protected:
    using ChannelMap = std::unordered_map<int, Channel*>;
    ChannelMap channels_;
private:
    EventLoop* ownerLoop_; 

};

