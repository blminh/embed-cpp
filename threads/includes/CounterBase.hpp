#ifndef __COUNTER_BASE_H__
#define __COUNTER_BASE_H__

class CounterBase
{
public:
    virtual void increment() = 0;
    virtual void decrement() = 0;
    virtual int getValue() = 0;
};

#endif