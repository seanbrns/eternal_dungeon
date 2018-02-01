#pragma once
#include "CardObject.h"
#include "Dice.h"
#include "Health.h"
#include "Accuracy.h"
#include "Armor.h"
#include "BasicAttack.h"
#include "MonsterAbility.h"

class MonsterCard : public CardObject
{
public:
    MonsterCard() :
        name_("Goblin"),
        hp(30),
        acc(1),
        armor(5),
        attack(new Dice(1, 6, 1))
    {}
    MonsterCard(std::vector<std::string> csvLine);
    ~MonsterCard();

    void Draw(GameWorld& gameWorld);
    void Reset();
    std::string Name() { return name_; }
    void PrintAllStats();

    Health hp;
    Accuracy acc;
    Armor armor;
    BasicAttack attack;
    MonsterAbility ability;

private:
    std::string name_;
};

