#include "stdafx.h"
#include <algorithm>
#include "Inventory.h"
#include "LootCard.h"

static const size_t MAX_ACCESSORY_EQUIP = 2;
static const size_t MAX_CONSUMABLE_EQUIP = 2;

LootCard* Inventory::ChooseLoot()
{
    LootCard* item = nullptr;
    int itemNum;

    if (IsEmpty())
    {
        std::cout << "NO ITEMS!\n";
        return item;
    }

    std::cout << "pick an item\n";

    for (size_t i = 0; i < lootBag_.size(); i++)
    {
        std::cout << (i + 1) << ". " << lootBag_.at(i)->Name();
        if (IsLootEquipped(lootBag_.at(i)))
        {
            std::cout << " (Equipped)";
        }
        
        std::cout << "\n";
    }

    while (item == nullptr)
    {
        std::cin >> itemNum;
        itemNum--;
        if (itemNum < lootBag_.size())
        {
            item = lootBag_.at(itemNum);
        }
        else
        {
            std::cout << "Invalid item selection\n";
        }
    }
    return item;
}

void Inventory::AddLoot(LootCard* loot)
{
    lootBag_.push_back(loot);
}

void Inventory::RemoveLoot(LootCard* loot)
{
    lootBag_.erase(std::remove(lootBag_.begin(), lootBag_.end(), loot), lootBag_.end());
    lootBag_.shrink_to_fit();
}

void Inventory::UnEquipLoot(LootCard* loot)
{
    bool unequipped = false;

    if (loot == weapon_)
    {
        weapon_ = nullptr;
        unequipped = true;
    }
    else if (loot == armor_)
    {
        armor_ = nullptr;
        unequipped = true;
    }
    else if (loot == shield_)
    {
        shield_ = nullptr;
        unequipped = true;
    }
    else
    {
        for (size_t i = 0; i < accessories_.size(); i++)
        {
            if (loot == accessories_.at(i))
                unequipped = true;
            if (unequipped)
                break;
        }
        if (!unequipped)
        {
            for (size_t i = 0; i < consumables_.size(); i++)
            {
                if (loot == consumables_.at(i))
                    unequipped = true;
                if (unequipped)
                    break;
            }
        }
    }

    if (!unequipped)
    {
        std::cout << loot->Name() << " is not currently equipped!\n";
    }
}

void Inventory::EquipLoot(LootCard* loot)
{
    LootCard* unequippedLoot = nullptr;
    bool equippedLoot = true;

    switch (loot->Type())
    {
    case LootCard::LootType::WEAPON:
        if (IsWeaponEquipped())
        {
            unequippedLoot = weapon_;
        }
        weapon_ = loot;
        break;
    case LootCard::LootType::ARMOR:
        if (IsArmorEquipped())
        {
            unequippedLoot = armor_;
        }
        armor_ = loot;
        break;
    case LootCard::LootType::SHIELD:
        if (IsShieldEquipped())
        {
            unequippedLoot = shield_;
        }
        shield_ = loot;
        break;
    case LootCard::LootType::ACCESSORY:
        if (accessories_.size() < MAX_ACCESSORY_EQUIP)
        {
            accessories_.push_back(loot);
        }
        else
        {
            bool done = false;
            int accNum;
            std::cout << "Equipped Max accessories, which will you unequip?\n";
            while (!done)
            {
                for (size_t i = 0; i < accessories_.size(); i++)
                {
                    std::cout << (i + 1) << ". " << accessories_.at(i)->Name() << "\n";
                }
                std::cout << accessories_.size() + 1 << ". None\n";

                std::cin >> accNum;
                accNum--;
                if (accNum == accessories_.size())
                {
                    equippedLoot = false;
                    done = true;
                }
                else if (accNum < accessories_.size())
                {
                    unequippedLoot = accessories_.at(accNum);
                    accessories_.erase(accessories_.begin() + accNum);
                    accessories_.shrink_to_fit();

                    accessories_.push_back(loot);
                    done = true;
                }
                else
                {
                    std::cout << "Invalid selection\n";
                }
            }
        }
        break;
    case LootCard::LootType::CONSUMABLE:
        if (consumables_.size() < MAX_CONSUMABLE_EQUIP)
        {
            consumables_.push_back(loot);
        }
        else
        {
            bool done = false;
            int consNum;
            std::cout << "Equipped Max Consumables, which will you unequip?\n";
            while (!done)
            {
                for (size_t i = 0; i < consumables_.size(); i++)
                {
                    std::cout << (i + 1) << ". " << consumables_.at(i)->Name() << "\n";
                }
                std::cout << consumables_.size() + 1 << ". None\n";

                std::cin >> consNum;
                consNum--;
                if (consNum == consumables_.size())
                {
                    equippedLoot = false;
                    done = true;
                }
                else if (consNum < consumables_.size())
                {
                    unequippedLoot = consumables_.at(consNum);
                    consumables_.erase(consumables_.begin() + consNum);
                    consumables_.shrink_to_fit();

                    accessories_.push_back(loot);
                    done = true;
                }
                else
                {
                    std::cout << "Invalid selection\n";
                }
            }
        }
        break;
    default:
        equippedLoot = false;
        break;
    }

    if (unequippedLoot != nullptr)
    {
        std::cout << "Unequipped " << unequippedLoot->Name() << "\n";
    }

    if (equippedLoot)
    {
        std::cout << "Equipped " << loot->Name() << "\n";
    }
}

bool Inventory::IsLootEquipped(LootCard* loot)
{
    bool retval = false;

    if ((loot == weapon_) ||
        (loot == armor_) ||
        (loot == shield_))
    {
        retval = true;
    }
    else
    {
        for (size_t i = 0; i < accessories_.size(); i++)
        {
            if (loot == accessories_.at(i))
            {
                retval = true;
            }
        }
        for (size_t i = 0; i < consumables_.size(); i++)
        {
            if (loot == consumables_.at(i))
            {
                retval = true;
            }
        }
    }
    return retval;
}

bool Inventory::UseLoot(LootCard* loot)
{
    bool lootUsed = false;
    return lootUsed;
}