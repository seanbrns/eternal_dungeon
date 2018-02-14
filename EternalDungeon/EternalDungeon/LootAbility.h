#pragma once

class LootAbility
{
public:
    typedef bool(*lootAbilityFuncPtr)(std::vector<Player*> players, bool inCombat, MonsterCard* monster);

    LootAbility() {}
    LootAbility(lootAbilityFuncPtr ability) :
        abilityFunc_(ability),
        description_("no description"),
        name_("no Name"),
        used_(false)
    {}
    ~LootAbility() {}

    void Execute(std::vector<Player*> players, bool inCombat = false, MonsterCard* monster = nullptr);
    std::string Description() { return description_; }
    std::string Name() { return name_; }
    bool CanUse() { return !used_; }
    void Reset() { used_ = false; }
private:
    lootAbilityFuncPtr abilityFunc_;
    std::string description_;
    std::string name_;
    bool used_;
};