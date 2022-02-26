#pragma once 

#include "noncopyable.hpp"
#include "Socket.hpp"
#include "Channel.hpp"

#include <functional>


class EventLoop;
class InetAddress;

class Acceptor : noncopyable
{
public:
    using NewConnectionCallback = std::function<void(int sockfd, const InetAddress&)>;

    Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reuseport);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback& cb)
    {
        newConnectionCallback_ = cb;
    }

    bool listenning() const { return listenning_; }
    void listen();
private:
    void handleRead();

    EventLoop* loop_;   // Acceptor用的就是用户定义的那个baseLoop，也称作mainloop
    Socket acceptSocket_;
    Channel acceptChannel_; // clientfd conn success!!!
    NewConnectionCallback newConnectionCallback_;
    bool listenning_;
};