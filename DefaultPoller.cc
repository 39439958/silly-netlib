#include "Poller.h"

#include <stdlib.h>

namespace silly {

Poller* Poller::newDefaultPoller(EventLoop* loop) {
    if (::getenv("SILLY_USE_POLL")) {
        return nullptr;
    } else {
        return nullptr;
    }
}

} 