#include "stdafx.h"
#include "MonsterCard.h"
#include "GameWorld.h"
#include "Player.h"
#include "Battle.h"
#include "Utility.h"

MonsterCard::~MonsterCard()
{
}

void MonsterCard::Draw(GameWorld& gameWorld)
{
    std::cout << "Monster Draw!\n";

    std::vector<Player*> fighters;
    int currentBranchIdx = 0;

    // Active players always engages
    for (size_t i = 0; i < gameWorld.Players().size(); i++)
    {
        if (gameWorld.Players().at(i)->IsActive())
        {
            fighters.push_back(gameWorld.Players().at(i));
            currentBranchIdx = gameWorld.Players().at(i)->GetBranch();
            break;
        }
    }

    // Players decide who else wants to battle
    for (size_t i = 0; i < gameWorld.Players().size(); i++)
    {
        // - must not be same active player
        // - must be in same area as active player
        if ((!gameWorld.Players().at(i)->IsActive()) &&
            (gameWorld.Players().at(i)->GetBranch() == currentBranchIdx) &&
             randomFrom(0, 1))
        {
            fighters.push_back(gameWorld.Players().at(i));
        }
    }

    Battle battle(fighters, this);
    battle.Execute();
}

void MonsterCard::Reset()
{
    hp.Reset();
}

void MonsterCard::PrintAllStats()
{
    std::cout << "========= " << name_ << "=========\n";
    hp.Print();
    acc.Print();
    armor.Print();
    attack.Print();
    ability.PrintAbilities();
}