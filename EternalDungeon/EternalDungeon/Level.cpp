#include "stdafx.h"
#include "Level.h"
#include "Player.h"
#include "Utility.h"

static const short MAX_LEVEL = 5;
static const short abilityExpReq[MAX_LEVEL] = { 0, 5, 15, 30, 50 };

Level::~Level()
{
}

void Level::GainExp(size_t val, Player* player)
{ 
    size_t previousLevel = level_;
    expPts_ += val; 
    for (size_t i= 0; i < MAX_LEVEL; i++)
    {
        if (expPts_ >= abilityExpReq[i])
        {
            level_ = i + 1;
        }
        else
        {
            break;
        }
    }

    if (level_ != previousLevel)
    {
        Print(player->GetName(), color_default, false);
        Print("-Level UP!", color_green);
        size_t levelModIdx = level_ - 1;
        player->hp.HealthMod(levelMods_.at(levelModIdx).healthMod_);
        player->armor.ArmorMod(levelMods_.at(levelModIdx).ArmorMod_);
        player->acc.AccMod(levelMods_.at(levelModIdx).AccuracyMod_);
        player->stats.AgilityMod(levelMods_.at(levelModIdx).AgilityMod_);
        player->stats.MightMod(levelMods_.at(levelModIdx).MightMod_);
        player->stats.KnowledgeMod(levelMods_.at(levelModIdx).KnowledgeMod_);
        player->stats.WillpowerMod(levelMods_.at(levelModIdx).WillPowerMod_);
        player->hp.Print();
        player->armor.Print();
        player->acc.Print();
        player->stats.PrintStats();
    }
}

Ability* Level::ChooseAbility()
{
    Ability* chosenAbility = nullptr;
    int abilityNum;
    bool done = false;
    std::cout << "Choose an ability\n";
    std::cout << "Player Lvl: " << level_ << "(xp: " << expPts_ << ")\n";
    for (size_t i = 0; i < abilities_.size(); i++)
    {
        std::cout << (i + 1) << ". [lvl " << (i + 1) << "]" << abilities_.at(i)->Name();
        if (!abilities_.at(i)->CanUse())
        {
            std::cout << " (Used)";
        }
        if (expPts_ < abilityExpReq[i])
        {
            std::cout << " (Requires higher level to use)";
        }

        std::cout << "\n";
    }
    std::cout << abilities_.size() + 1 << ". (Descriptions)\n";
    std::cout << abilities_.size() + 2 << ". (Back)\n";

    while (!done)
    {
        std::cin >> abilityNum;
        abilityNum--;

        if (abilityNum == abilities_.size() + 1)
        {
            done = true;
        }
        else if (abilityNum == abilities_.size())
        {
            for (size_t i = 0; i < abilities_.size(); i++)
            {
                std::cout << abilities_.at(i)->Name() << ": " << abilities_.at(i)->Description() << "\n";
            }
        }
        else if (abilityNum < abilities_.size() &&
                 expPts_ >= abilityExpReq[abilityNum])
        {
            chosenAbility = abilities_.at(abilityNum);
            done = true;
        }
        else
        {
            std::cout << "Invalid selection\n";
        }
    }

    return chosenAbility;
}

void Level::PrintAbilities()
{
    for (size_t i = 0; i < abilities_.size(); i++)
    {
        std::cout << "[lvl " << (i + 1) << "]" << abilities_.at(i)->Name();
        if (!abilities_.at(i)->CanUse())
        {
            std::cout << " (Used)";
        }
        if (expPts_ < abilityExpReq[i])
        {
            std::cout << " (Requires higher level to use)";
        }

        std::cout << "\n" << abilities_.at(i)->Description();

    }
}