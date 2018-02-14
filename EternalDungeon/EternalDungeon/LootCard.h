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
    LootCard() {}
    LootCard(std::vector<std::string> csvLine);
    ~LootCard() {}

    void Draw(GameWorld& gameWorld);
    LootCard::LootType Type() { return type_; };
    std::string Description() { return description_; }
    std::string Name() { return name_; }

private:
    std::string name_;
    std::string description_;
    LootType type_;
    Passive lootPassive_;
    Ability lootActive_;
};

class Passive
{
public:
    Passive();
    ~Passive();
    void Apply(Player* player);
    void Remove(Player* player);
    std::string Description() { return description_; }
    std::string Name() { return name_; }
private:
    std::string name_;
    std::string description_;
};