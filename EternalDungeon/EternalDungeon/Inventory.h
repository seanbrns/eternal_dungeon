#pragma once

#include "LootCard.h"

class Inventory
{
public:
    Inventory() :
        weapon_(nullptr),
        armor_(nullptr),
        shield_(nullptr)
    {}
    ~Inventory() {}

    bool IsEmpty() { return lootBag_.empty(); }
    bool IsWeaponEquipped() { return (weapon_ != nullptr); }
    bool IsArmorEquipped() { return (armor_ != nullptr); }
    bool IsShieldEquipped() { return (shield_ != nullptr); }
    bool IsConsumableEquipped() { return !consumables_.empty(); }
    bool IsAccessoryEquipped() { return !accessories_.empty(); }

    bool IsLootEquipped(LootCard* loot);
    void UnEquipLoot(LootCard* loot);
    void EquipLoot(LootCard* loot);

    LootCard* ChooseLoot();
    void AddLoot(LootCard* loot);
    void RemoveLoot(LootCard* loot);
    bool UseLoot(LootCard* loot);
private:
    LootCard* weapon_;
    LootCard* armor_;
    LootCard* shield_;
    std::vector<LootCard*> accessories_;
    std::vector<LootCard*> consumables_;
    std::vector<LootCard*> lootBag_;
};

