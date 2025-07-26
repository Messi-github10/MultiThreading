#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

// 抽象类
class Noncopyable{
protected:
    Noncopyable(){}
    ~Noncopyable(){}
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable &operator=(const Noncopyable &) = delete;
};

#endif