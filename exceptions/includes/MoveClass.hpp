#ifndef __MOVE_CLASS_H__
#define __MOVE_CLASS_H__

#include <iostream>

namespace user_exceptions
{
    class MoveClass
    {
    private:
    private:
        int *mResource_{};

    public:
        MoveClass() = default;
        MoveClass(int resource);
        // Copy constructor
        MoveClass(const MoveClass &that);
        // Move constructor
        MoveClass(MoveClass &&that) noexcept;
        ~MoveClass();

        friend std::ostream &operator<<(std::ostream &out, const MoveClass &moveClass);
        void moveClassAction();
    };
};

#endif