#ifndef __TIME_SLOT_H__
#define __TIME_SLOT_H__

#include <functional>

class TimeSlot
{
private:
    int mTimeAt_{};
    std::function<void()> mCb_;

public:
    TimeSlot(int timeOn, std::function<void()> cb);
    ~TimeSlot();
};

#endif