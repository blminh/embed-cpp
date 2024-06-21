#ifndef __GAME_POTION_H__
#define __GAME_POTION_H__

#include <string>
#include <string_view>

namespace Game
{
    class Potion
    {
    public:
        enum Type
        {
            health,
            strength,
            poison,
            max_type
        };
        enum Size
        {
            small,
            medium,
            large,
            max_size
        };
        Potion();
        Potion(Type type, Size size);
        ~Potion();

        Type getType() const;
        Size getSize() const;
        static std::string_view getPotionTypeName(Type type);
        static std::string_view getPotionSizeName(Size size);
        std::string getName() const;
        static Potion getRandomPotion();

    private:
        Type mType_{};
        Size mSize_{};
    };
};

#endif