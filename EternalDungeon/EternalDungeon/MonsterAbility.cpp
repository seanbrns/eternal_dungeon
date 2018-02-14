#include "stdafx.h"
#include "MonsterAbility.h"


MonsterAbility::~MonsterAbility()
{
}

bool MonsterAbility::Execute(std::vector<Player*> players, MonsterCard* monster)
{
    if (abilityFunc_ != nullptr)
    {
        return abilityFunc_(players, monster);
    }
    return false;
}

void MonsterAbility::PrintAbilities()
{
    std::cout << name_ << ":\n" << description_ << "\n";
}