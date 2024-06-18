#include <sstream>
#include "../../includes/Random.hpp"
#include "../includes/potion.hpp"

namespace Game
{
    Potion::Potion() {}
    Potion::~Potion() {}
    Potion::Potion(Potion::Type type, Potion::Size size) : mType_{type}, mSize_{size} {}

    Potion::Type Potion::getType() const
    {
        return mType_;
    }

    Potion::Size Potion::getSize() const
    {
        return mSize_;
    }

    std::string_view Potion::getPotionTypeName(Potion::Type type)
    {
        static constexpr std::string_view names[]{
            "Health",
            "Strength",
            "Poison",
        };
        return names[type];
    }

    std::string_view Potion::getPotionSizeName(Potion::Size size)
    {
        static constexpr std::string_view names[]{
            "Small",
            "Medium",
            "Large",
        };

        return names[size];
    }

    std::string Potion::getName() const
    {
        std::stringstream result{};
        result << Potion::getPotionSizeName(getSize()) << " potion of " << Potion::getPotionTypeName(getType());
        return result.str();
    }

    Potion Potion::getRandomPotion()
    {
        return Potion{
            static_cast<Potion::Type>(Random::get(0, max_type - 1)),
            static_cast<Potion::Size>(Random::get(0, max_size - 1)),
        };
    }
};
