#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

// 抽象类（禁止复制控制操作）
class Noncopyable
{
protected:
    Noncopyable() = default;
    ~Noncopyable() = default;
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable &operator=(const Noncopyable &) = delete;
};

#endif