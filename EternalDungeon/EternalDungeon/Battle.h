#pragma once
#include "MonsterCard.h"
#include "Player.h"

class Battle
{
public:
    Battle(std::vector<Player*> fighters, MonsterCard* monster) :
        fighters_(fighters),
        monster_(monster)
    {}
    ~Battle();

    void Execute();

private:
    std::vector<Player*> fighters_;
    MonsterCard* monster_;
    Player* currFighter_;
    size_t currFighterIdx_;
    void MonsterTurn();
    void PlayerTurn();

    //Logging data?
};

