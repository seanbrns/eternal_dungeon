#pragma once
#include "CardObject.h"
class LootCard :
    public CardObject
{
public:
    enum class LootType
    {
        WEAPON,
        ARMOR,
        SHIELD,
        ACCESSORY,
        CONSUMABLE
    };
    LootCard() : name_("lootName") {}
    ~LootCard();

    void Draw(GameWorld& gameWorld);
    LootCard::LootType Type() { return type_; };
    std::string Name() { return name_; }

private:
    std::string name_;
    LootType type_;
};

