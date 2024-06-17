#include "includes/animal.hpp"
#include "includes/cat.hpp"
#include "includes/dog.hpp"

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

    Cat::Cat(std::string_view name) : Animal{name} {}

    std::string_view Cat::speak() const
    {
        return "Meow";
    }

    Dog::Dog(std::string_view name) : Animal{name} {}

    std::string_view Dog::speak() const
    {
        return "Woof";
    }

    void report(const Animal &animal)
    {
        std::cout << animal.getName() << " says " << animal.speak() << std::endl;
    }

    void animalAction()
    {
        const Cat cat{"Fred"};
        report(cat);

        const Dog dog{"Garbo"};
        report(dog);

        const Animal *pAnimal{&cat};
        std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

        pAnimal = &dog;
        std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';
    }
};