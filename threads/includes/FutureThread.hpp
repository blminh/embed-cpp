#ifndef __FUTURE_THREAD_H__
#define __FUTURE_THREAD_H__

namespace threads
{
    class FutureThread
    {
    public:
        FutureThread();
        ~FutureThread();

        void futureThread();
        void futureWaitFor();
        void futureRet();
    };
};

#endif