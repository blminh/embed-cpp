#include "../includes/animal.hpp"
#include "../includes/dog.hpp"

namespace animal
{
    Dog::Dog(std::string_view name) : Animal{name} {}

    std::string_view Dog::speak() const
    {
        return "Woof";
    }
};