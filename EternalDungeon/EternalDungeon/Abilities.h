#pragma once

#include "Ability.h"
class Abilities
{
public:
    Abilities();
    ~Abilities();

    Ability* ChooseAbility();
    void ListAbilities();
private:
    std::vector<Ability*> abilities_;
};

