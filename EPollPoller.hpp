#pragma once

#include "Poller.hpp"
#include "Timestamp.hpp"

#include <vector>
#include <sys/epoll.h>

/**
 * epoll的使用
 * epoll_create
 * epoll_ctl    add/mod/del
 * epoll_wait   poll
 */

class EPollPoller : public Poller
{
public:
    EPollPoller(EventLoop* loop);
    // C++11新特性，让编译器检查父类是否留了个虚函数需要覆写
    ~EPollPoller() override;

    // 重写基类Poller的抽象方法
    Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;
    void updateChannel(Channel* channel) override;
    void removeChannel(Channel* channle) override;

private:
    static const int kInitEventListSize = 16;

    // 填写活跃的连接
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;
    // 更新channel通道
    void update(int operation, Channel* channel);

    using EventList = std::vector<epoll_event>;

    int epollfd_;
    EventList events_;
};