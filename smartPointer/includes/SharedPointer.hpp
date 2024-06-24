#ifndef __SHARED_POINTER_H__
#define __SHARED_POINTER_H__

class SharedPointer
{
private:
    int *mPtr_;
    int *mCounter_;

public:
    SharedPointer();
    SharedPointer(int *ptr);
    SharedPointer(const SharedPointer &sPtr);
    ~SharedPointer();

    SharedPointer &operator=(const SharedPointer &sPtr);
    void show();
};

#endif