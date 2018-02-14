#include "stdafx.h"
#include "Ability.h"


Ability::~Ability()
{
}

bool Ability::Execute(std::vector<Player*> targetPlayers, bool inCombat, MonsterCard* targetMonster)
{
    if (abilityFunc_ != nullptr)
    {
        return abilityFunc_(targetPlayers, inCombat, targetMonster);
    }
    return false;
}

void Ability::PrintAbilities()
{
    std::cout << name_ << ":\n" << description_ << "\n";
}