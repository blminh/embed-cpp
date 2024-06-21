#include "../includes/Animal.hpp"

namespace animal
{
    Animal::Animal(std::string_view name) : mName_{name} {}
    std::string_view Animal::getName() const
    {
        return mName_;
    }

    std::string_view Animal::speak() const
    {
        return "???";
    }

    void report(const Animal &animal)
    {
        std::cout << animal.getName() << " says " << animal.speak() << std::endl;
    }
};