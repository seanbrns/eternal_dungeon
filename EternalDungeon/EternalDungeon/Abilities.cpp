#include "stdafx.h"
#include "Abilities.h"


Abilities::Abilities()
{
}


Abilities::~Abilities()
{
}

Ability* Abilities::ChooseAbility()
{
    Ability* chosenAbility = nullptr;
    int abilityNum;
    bool done = false;
    std::cout << "Choose an ability\n";

    for (size_t i = 0; i < abilities_.size(); i++)
    {
        std::cout << (i + 1) << ". " << abilities_.at(i)->Name();
        if (!abilities_.at(i)->CanUse())
        {
            std::cout << " (Already Used)";
        }

        std::cout << "\n";
    }
    std::cout << abilities_.size() + 1 << ". None\n";

    while (!done)
    {
        std::cin >> abilityNum;
        abilityNum--;

        if (abilityNum == abilities_.size())
        {
            done = true;
        }
        else if (abilityNum < abilities_.size())
        {
            chosenAbility = abilities_.at(abilityNum);
            done = true;
        }
        else
        {
            std::cout << "Invalid item selection\n";
        }
    }

    return chosenAbility;
}