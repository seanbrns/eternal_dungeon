#pragma once
#include "Ability.h"

struct levelMods
{
    short healthMod_;
    short ArmorMod_;
    short AccuracyMod_;
    short MightMod_;
    short KnowledgeMod_;
    short AgilityMod_;
    short WillPowerMod_;
};

class Level
{
public:
    Level() : 
        expPts_(0),
        level_(1)
    {}
    ~Level();

    void GainExp(size_t val, Player* player);
    Ability* ChooseAbility();
    void PrintAbilities();
    void PrintLvl()
    {
        std::cout << "Player Lvl: " << level_ << "(xp: " << expPts_ << ")\n";
    }
private:
    std::vector<Ability*> abilities_;
    std::vector<levelMods> levelMods_;
    size_t expPts_;
    size_t level_;
};

