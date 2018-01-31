#include "stdafx.h"
#include "Ability.h"


Ability::~Ability()
{
}

void Ability::Execute(std::vector<Player*> players, bool inCombat, MonsterCard* monster)
{
    ability_(players, inCombat, monster);
}

