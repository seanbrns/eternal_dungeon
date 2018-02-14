#include "stdafx.h"
#include "MonsterAbilityList.h"
#include "Player.h"
#include "MonsterCard.h"
#include <map>

// Note: Create new abilities here and add to list
static bool DefaultAbility(std::vector<Player*> players, MonsterCard* monster);

static const std::map<std::string, MonsterAbility::MonsterAbilityFuncPtr> abilityMap =
{
    { "default", DefaultAbility },
};

//*****************************************************************************
// FindAbility
//*****************************************************************************
MonsterAbility::MonsterAbilityFuncPtr FindMonsterAbility(std::string name)
{
    MonsterAbility::MonsterAbilityFuncPtr abilityFunc = nullptr;
    auto abilityItr = abilityMap.find(name);
    if (abilityItr != abilityMap.end())
    {
        abilityFunc = abilityItr->second;
        std::cout << "Monster Ability FOUND!" << std::endl;
    }
    else
    {
        std::cout << "ERROR - could not find monster ability: " << name << std::endl;
    }

    return abilityFunc;
}

//*****************************************************************************
// event list
//*****************************************************************************
bool DefaultAbility(std::vector<Player*> players, MonsterCard* monster)
{
    std::cout << "ERROR-default monster ability\n";
    return true;
}
