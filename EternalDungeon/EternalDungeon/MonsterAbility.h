#pragma once

class Player;
class MonsterCard;

class MonsterAbility
{
public:
    MonsterAbility() {}
    MonsterAbility(bool(*ability)(std::vector<Player*> players, MonsterCard* monster)) :
        ability_(ability),
        description_("no description"),
        name_("no Name")
    {}
    ~MonsterAbility();

    bool Execute(std::vector<Player*> players, MonsterCard* monster);
    std::string Description() { return description_; }
    std::string Name() { return name_; }
    void PrintAbilities();

private:
    bool(*ability_)(std::vector<Player*> players, MonsterCard* monster);
    std::string description_;
    std::string name_;
};