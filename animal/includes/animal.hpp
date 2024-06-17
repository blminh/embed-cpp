#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include <iostream>
#include <string>
#include <string_view>

namespace animal
{
    class Animal
    {
    protected:
        std::string mName_;

        Animal(std::string_view name);
        Animal(const Animal &) = default;
        Animal &operator=(const Animal &) = default;

    public:
        std::string_view getName() const;

        virtual std::string_view speak() const;
    };

    void report(const Animal &animal);
}

#endif