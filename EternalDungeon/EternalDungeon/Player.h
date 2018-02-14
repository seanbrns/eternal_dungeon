#pragma once

#include "Dice.h"
#include "Health.h"
#include "Accuracy.h"
#include "Armor.h"
#include "BasicAttack.h"
#include "Inventory.h"
#include "Abilities.h"
#include "Level.h"
#include "Stat.h"

class CardObject;
class Player
{
public:
    Player(std::string name) : 
            name_(name), 
            active_(false), 
            branchIdx_(0),
            hp(30),
            acc(2),
            armor(7),
            attack(new Dice(1, 6, 3))
    {}
    Player(std::vector<std::string> csvLine);
    ~Player();

    std::string GetName() { return name_; }
    bool IsActive() { return active_; }
    void SetActive(bool val) { active_ = val; }
    int GetBranch() { return branchIdx_; };
    bool DoTurn(GameWorld& gameWorld);
    void PrintAllStats();
    Health hp;
    Accuracy acc;
    Armor armor;
    BasicAttack attack;
    Inventory inventory;
    Level level;
    Stat stats;
private:
    std::string name_;
    bool active_;
    int branchIdx_;

    void Rest(GameWorld& gameWorld);
    bool RestingTrade(GameWorld& gameWorld);
    void ChangeEquipment();
    bool Travel(GameWorld& gameWorld);
    void EndTurn(GameWorld& gameWorld);
    void DrawDungeonCard(GameWorld& gameWorld);
};

