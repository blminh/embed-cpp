#ifndef __STORAGE_TEMPLATES_h__
#define __STORAGE_TEMPLATES_h__

#include <iostream>
#include <memory>
#include <type_traits> // for std::is_pointer_v and std::is_null_pointer_v

namespace storageTemplates
{
    template <typename T>
    class Storage
    {
        static_assert(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>, "Storage<T*> and Storage<nullptr> disallowed");

    private:
        T mValue_{};

    public:
        Storage(T value) : mValue_{value}
        {
        }

        void print()
        {
            std::cout << mValue_ << '\n';
        }
    };

    template <typename T>
    class Storage<T *>
    {
    private:
        std::unique_ptr<T> mValue_{}; // use std::unique_ptr to automatically deallocate when Storage is destroyed

    public:
        Storage(T *value)
            : mValue_{std::make_unique<T>(value ? *value : 0)} // or throw exception when !value
        {
        }

        void print()
        {
            if (mValue_)
                std::cout << *mValue_ << '\n';
        }
    };
}
#endif