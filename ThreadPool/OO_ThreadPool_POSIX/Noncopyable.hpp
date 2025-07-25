#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

class Noncopyable{
public:
    Noncopyable(){}
    ~Noncopyable(){}
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable &operator=(const Noncopyable &) = delete;
};

#endif