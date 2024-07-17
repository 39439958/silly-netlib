#include "Poller.h"
#include "EpollPoller.h"

#include <stdlib.h>


Poller* Poller::newDefaultPoller(EventLoop* loop) {
    if (::getenv("SILLY_USE_POLL")) {
        return nullptr;
    } else {
        return new EpollPoller(loop);
    }
}

