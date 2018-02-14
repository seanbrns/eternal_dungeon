#pragma once

class Player;
class MonsterCard;

class MonsterAbility
{
public:
    typedef bool(*MonsterAbilityFuncPtr)(std::vector<Player*> players, MonsterCard* monster);

    MonsterAbility() {}
    MonsterAbility(MonsterAbilityFuncPtr ability) :
        abilityFunc_(ability),
        description_("no description"),
        name_("no Name")
    {}
    ~MonsterAbility();

    bool Execute(std::vector<Player*> players, MonsterCard* monster);
    std::string Description() { return description_; }
    std::string Name() { return name_; }
    void PrintAbilities();

private:
    MonsterAbilityFuncPtr abilityFunc_;
    std::string description_;
    std::string name_;
};