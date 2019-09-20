#pragma once
#include "CardObject.h"
#include "Ability.h"

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
    void ApplyPassive(Player* player);
    void RemovePassive(Player* player);
    
    LootCard::LootType Type() { return type_; };
    std::string Description() { return description_; }
    std::string Name() { return name_; }

private:
    std::string name_;
    std::string description_;
    LootType type_;
    Ability lootPassive_;
    Ability lootActive_;
};