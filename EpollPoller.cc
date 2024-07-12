#include "EpollPoller.h"
#include "Logger.h"
#include "Channel.h"

#include <errno.h>
#include <cstring>

using namespace silly;

const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;


EpollPoller::EpollPoller(EventLoop *loop) 
    : Poller(loop),
      epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
      events_(kInitEventListSize)
{
    if (epollfd_ < 0) {
        LOG_FATAL("epoll_create error:%d \n", errno);
    }
}

EpollPoller::~EpollPoller() {
    ::close(epollfd_);
}

void EpollPoller::removeChannel(Channel* channel) {
    const int index = channel->index();
    LOG_INFO("fd=%d events=%d index=%d \n", channel->fd(), channel->events(), index);

    if (index == kNew || index == kDeleted) {
        if (index == kNew) {
            int fd = channel->fd();
            channels_[fd] = channel;
        }
        
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
    } else {
        int fd = channel->fd();
        if (channel->isNoneEvent()) {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        } else {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EpollPoller::updateChannel(Channel* channel) {
    
}

void EpollPoller::fillActiveChannels(int numEvents, ChannelList *activeChannels) const {

}

void EpollPoller::update(int operation, Channel* channel) {
    struct epoll_event event;
    memset(&event, 0, sizeof event);
    event.events = channel->events();
    event.data.ptr = channel;
    int fd = channel->fd();

    if (::epoll_ctl(epollfd_, operation, fd, &event) < 0) {
        if (operation == EPOLL_CTL_DEL) {
            LOG_ERROR("epoll_ctl del error:%d\n", errno);
        } else {
            LOG_FATAL("epoll_ctl add/mod error:%d\n", errno);
        }
    }
}

Timestamp EpollPoller::poll(int timeoutMs, ChannelList *activeChannels) {

}


