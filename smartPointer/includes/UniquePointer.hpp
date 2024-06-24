#ifndef __UNIQUE_POINTER_H__
#define __UNIQUE_POINTER_H__

class UniquePointer
{
private:
    int *mPtr_;

public:
    UniquePointer();
    UniquePointer(int val);
    ~UniquePointer();

    UniquePointer &operator=(const UniquePointer &uPtr);
    void show();
};

#endif