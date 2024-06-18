#include "../includes/animal.hpp"
#include "../includes/cat.hpp"

namespace animal
{
    Cat::Cat(std::string_view name) : Animal{name} {}

    std::string_view Cat::speak() const
    {
        return "Meow";
    }
};