#pragma once
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
        std::string m_name;

        Animal(std::string_view name);
        Animal(const Animal &) = default;
        Animal &operator=(const Animal &) = default;

    public:
        std::string_view getName() const;

        virtual std::string_view speak() const;
    };

    class Cat : public Animal
    {
    public:
        Cat(std::string_view name);

        virtual std::string_view speak() const;
    };

    class Dog : public Animal
    {
    public:
        Dog(std::string_view name);

        virtual std::string_view speak() const;
    };

    void report(const Animal &animal);

    void animalAction();
}

#endif