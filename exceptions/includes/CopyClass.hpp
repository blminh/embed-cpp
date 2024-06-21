#ifndef __COPY_CLASS_H__
#define __COPY_CLASS_H__

#include <string>
#include <string_view>
#include <exception>
#include <utility>
#include <stdexcept>

namespace user_exceptions
{
    class CopyClass
    {
    public:
        bool pubThrow_{};
        CopyClass() = default;
        CopyClass(const CopyClass &that);
    };
};

#endif