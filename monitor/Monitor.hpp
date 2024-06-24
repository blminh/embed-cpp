#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <ostream>
#include <functional>

class Monitor
{
private:
    int mValue_{};
    std::function<int(int, int)> cb_;

public:
    Monitor();
    Monitor(int value, std::function<int(int, int)> cb);
    ~Monitor();

    Monitor &operator=(const int &value);
    friend std::ostream &operator<<(std::ostream &out, const Monitor &monitor);
};

#endif