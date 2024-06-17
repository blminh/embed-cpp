#include "includes/counter.hpp"
#include "includes/atomicCounter.hpp"
#include "includes/futureThread.hpp"
#include "includes/safeCounter.hpp"

int main()
{
    threads::Counter count;
    count.counter();

    // threads::SafeCounter sCount;
    // sCount.safeCounter();

    // threads::AtomicCounter aCounter;
    // aCounter.atomicCounter();

    // threads::FutureThread fThread;
    // fThread.futureThread();
    // fThread.futureWaitFor();
    // fThread.futureRet();

    return 0;
}
