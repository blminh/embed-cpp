#ifndef __ANIMAL_DOG_H__
#define __ANIMAL_DOG_H__

#include <string_view>
#include "animal.hpp"

namespace animal
{
    class Dog : public Animal
    {
    public:
        Dog(std::string_view name);

        virtual std::string_view speak() const;
    };
}

#endif