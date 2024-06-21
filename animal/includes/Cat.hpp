#ifndef __ANIMAL_CAT_H__
#define __ANIMAL_CAT_H__

#include <string_view>
#include "Animal.hpp"

namespace animal
{
    class Cat : public Animal
    {
    public:
        Cat(std::string_view name);

        virtual std::string_view speak() const;
    };
}

#endif