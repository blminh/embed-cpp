#include "includes/animal.hpp"
#include "includes/cat.hpp"
#include "includes/dog.hpp"

int main()
{
    const animal::Cat cat{"Fred"};
    animal::report(cat);

    const animal::Dog dog{"Garbo"};
    animal::report(dog);

    const animal::Animal *pAnimal{&cat};
    std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

    pAnimal = &dog;
    std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

    return 0;
}