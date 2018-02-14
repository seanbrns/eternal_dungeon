#include "stdafx.h"
#include "AbilityList.h"
#include "Player.h"
#include "MonsterCard.h"
#include <map>

// Note: Create new abilities here and add to list
static bool DefaultAbility(std::vector<Player*> players, bool inCombat, MonsterCard* monster);

static const std::map<std::string, Ability::AbilityFuncPtr> abilityMap =
{
    { "default", DefaultAbility },

};

//*****************************************************************************
// FindAbility
//*****************************************************************************
Ability::AbilityFuncPtr FindAbility(std::string name)
{
    Ability::AbilityFuncPtr abilityFunc = nullptr;
    auto abilityItr = abilityMap.find(name);
    if (abilityItr != abilityMap.end())
    {
        abilityFunc = abilityItr->second;
        std::cout << "Event FOUND!" << std::endl;
    }
    else
    {
        std::cout << "ERROR - could not find event: " << name << std::endl;
    }

    return abilityFunc;
}

//*****************************************************************************
// event list
//*****************************************************************************
bool DefaultAbility(std::vector<Player*> players, bool inCombat, MonsterCard* monster)
{
    std::cout << "ERROR-default event\n";
    return true;
}

