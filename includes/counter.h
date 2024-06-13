#pragma once
#ifndef __COUNTER_H__
#define __COUNTER_H__

class Counter
{
private:
    int m_value{};

public:
    Counter();
    Counter(int value);
    ~Counter();

    void increment();
    void decrement();
    int getValue();
    void counter();
};

#endif