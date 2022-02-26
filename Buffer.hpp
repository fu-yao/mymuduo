#pragma once

#include <vector>
#include <string>
#include <algorithm>

// 网络库底层的缓冲区类型定义
class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;

    explicit Buffer(size_t initialSize = kInitialSize)
        : buffer_(kCheapPrepend + initialSize)
        , readerIndex_(kCheapPrepend)
        , writerIndex_(kCheapPrepend)
    { }

    size_t readableBytes() const 
    { 
        return writerIndex_ - readerIndex_; 
    }

    size_t writableBytes() const
    { 
        return buffer_.size() - writerIndex_; 
    }

    size_t prependableBytes() const
    { 
        return readerIndex_; 
    }

    // 返回缓冲区中欧给可读数据的起始地址
    const char* peek() const
    { 
        return begin() + readerIndex_; 
    }

    // onMessage string <- Buffer
    void retrieve(size_t len)
    {
        if(len < readableBytes())
        {
            readerIndex_ += len;    // 应用只读取了可读缓冲区数据的一部分，就是len，还剩下readerIndex += len -> writerIndex_ 
        }
        else    // len == readableBytes()
        {
            retrieveAll();
        }
    }

    void retrieveAll()
    {
        readerIndex_ = writerIndex_ = kCheapPrepend;
    }

    // 把onMessage函数上报的Buffer数据据，转成string类型的数据返回
    std::string retrieveAllAsString()
    {
        return retrieveAsString(readableBytes());   // 应用可读数据的长度
    }

    std::string retrieveAsString(size_t len)
    {
        std::string result(peek(), len);
        retrieve(len);  // 上面一句把缓冲区中可读的数据，已经读取出来了，需要对缓冲区进行复位
        return result;
    }

    // buffer_.size() - writerIndex_    len
    void ensureWriteableBytes(size_t len)
    {
        if(writableBytes() < len)
        {
            makeSpace(len); // 扩容函数
        }
    }

    // 把[data,data+len]内存上的数据，添加到writable缓冲区当中
    void append(const char* data, size_t len)
    {
        ensureWriteableBytes(len);
        std::copy(data, data+len, beginWrite());
        writerIndex_ += len;
    }

    char* beginWrite()
    {
        return begin() + writerIndex_;
    }

    const char* beginWrite() const
    {
        return begin() + writerIndex_;
    }

    ssize_t readFd(int fd, int* saveErrno);
    ssize_t writeFd(int fd, int* saveErrno);

private:
    char* begin()
    {   // it.operator*() => 值 => 再取址
        // vector底层数组首元素的地址，就是数组的起始地址
        return &*buffer_.begin();
    }

    const char* begin() const
    {   
        return &*buffer_.begin();
    }

    void makeSpace(size_t len)
    {
        if(writableBytes() + prependableBytes() < len + kCheapPrepend)
        {
            buffer_.resize(writerIndex_ + len);
        }
        else
        {
            size_t readable = readableBytes();
            std::copy(begin() + readerIndex_,
                      begin() + writerIndex_,
                      begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;
            writerIndex_ = readerIndex_ + readable;
        }
    }

    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
};