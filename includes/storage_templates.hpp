#pragma once
#ifndef __STORAGE_TEMPLATES_h__
#define __STORAGE_TEMPLATES_h__

#include <iostream>
#include <memory>
#include <type_traits> // for std::is_pointer_v and std::is_null_pointer_v

namespace storage_templates
{
    template <typename T>
    class Storage
    {
        static_assert(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>, "Storage<T*> and Storage<nullptr> disallowed");

    private:
        T m_value{};

    public:
        Storage(T value) : m_value{value}
        {
        }

        void print()
        {
            std::cout << m_value << '\n';
        }
    };

    template <typename T>
    class Storage<T *>
    {
    private:
        std::unique_ptr<T> m_value{}; // use std::unique_ptr to automatically deallocate when Storage is destroyed

    public:
        Storage(T *value)
            : m_value{std::make_unique<T>(value ? *value : 0)} // or throw exception when !value
        {
        }

        void print()
        {
            if (m_value)
                std::cout << *m_value << '\n';
        }
    };

    void templates();
}
#endif