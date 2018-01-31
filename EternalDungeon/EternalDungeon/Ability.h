#pragma once

class Player;
class MonsterCard;

class Ability
{
public:
    Ability() {}
    Ability(void(*ability)(std::vector<Player*> players, bool inCombat, MonsterCard* monster)) : 
        ability_(ability),
        description_("no description"),
        name_("no Name"),
        used_(false)
    {}
    ~Ability();

    void Execute(std::vector<Player*> players, bool inCombat = false, MonsterCard* monster = nullptr);
    std::string Description() { return description_; }
    std::string Name() { return name_; }
    bool CanUse(){ return !used_; }
private:
    void(*ability_)(std::vector<Player*> players, bool inCombat, MonsterCard* monster);
    std::string description_;
    std::string name_;
    bool used_;
};
