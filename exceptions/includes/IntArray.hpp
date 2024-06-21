#ifndef __INT_ARRAY_H__
#define __INT_ARRAY_H__

#include <string>
#include <string_view>
#include <exception>
#include <utility>
#include <stdexcept>

namespace user_exceptions
{
    class IntArray
    {
    private:
        int mData_[3]{};

    public:
        IntArray();

        int getLength() const;
        int &operator[](const int index);
    };
};

#endif