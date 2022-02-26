#pragma once
/*
 * noncopyable的派生类对象可以正常构造和析构，但是不能进行
 * 拷贝构造或赋值操作
 * 原理:派生类进行拷贝构造或赋值操作，首先调用基类的拷贝构造/赋值
 * 基类中的已经被delete掉，因此无法进行操作
 */
class noncopyable
{
public:
    noncopyable(const noncopyable &) = delete;
    noncopyable &operator=(const noncopyable &) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};