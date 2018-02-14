#pragma once

class Player;
class MonsterCard;

class Ability
{
public:
    typedef bool(*AbilityFuncPtr)(std::vector<Player*> players, bool inCombat, MonsterCard* monster);
    
    Ability() {}
    Ability(AbilityFuncPtr ability) :
        abilityFunc_(ability),
        description_("no description"),
        name_("no Name"),
        used_(false)
    {}
    ~Ability();

    bool Execute(std::vector<Player*> players, bool inCombat = false, MonsterCard* monster = nullptr);
    std::string Description() { return description_; }
    std::string Name() { return name_; }
    bool CanUse(){ return !used_; }
    void Reset() { used_ = false; }
    void PrintAbilities();
private:
    AbilityFuncPtr abilityFunc_;
    std::string description_;
    std::string name_;
    bool used_;
};
