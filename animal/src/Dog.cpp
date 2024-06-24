#include "../includes/Dog.hpp"

namespace animal
{
    Dog::Dog(std::string_view name) : Animal{name} {}

    std::string_view Dog::speak() const
    {
        return "Woof";
    }
};