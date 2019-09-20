#include "stdafx.h"
#include "Battle.h"
#include "Dice.h"
#include "Utility.h"
#include <sstream>

enum PlayerBattleAction
{
    ATTACK,
    ABILITY,
    ITEM,
    DEFEND,
    CHECK_CHAR,
    CHECK_MONSTER
};

static bool HitCheck(Accuracy attackerAcc, Armor targetArmor);
static PlayerBattleAction GetPlayerBattleAction();

Dice die_1d6(1, 6);
Dice die_1d12(1, 12);

std::string const battleStart = 
"                   |______________  \n\
BATTLE!     [======|______________> \n\
                   |                \n";

Battle::~Battle()
{
}

void Battle::Execute()
{
    bool battleDone = false;
    bool playerTurn = true;
    int deadNum = 0;

    std::cout << battleStart;

    for (size_t i = 0; i < fighters_.size(); i++)
    {
        if (fighters_.at(i)->IsActive())
        {
            currFighter_ = fighters_.at(i);
            currFighterIdx_ = i;
            break;
        }
    }

    while (!battleDone)
    {
        if (playerTurn)
        {
            if (currFighter_->IsActive())
            {
                playerTurn = false;
            }
            PlayerTurn();
        }
        else // monster turn
        {
            MonsterTurn();
            playerTurn = true;
        }

        // check for end of battle
        for (int i = 0; i < fighters_.size(); i++)
        {
            if (fighters_.at(i)->hp.IsDead())
            {
                deadNum++;
            }
        }

        if (monster_->hp.IsDead())
        {
            battleDone = true;
            Print("Monster Defeated!");
        }
        else if (deadNum == fighters_.size())
        {
            battleDone = true;
            Print("All fighters are dead...", color_red);
        }
        else
        {
            deadNum = 0; // reset
        }
    }

    WaitForUser();
    std::cout << "---BATTLE END---\n\n";
    monster_->Reset();
}

static bool HitCheck(Accuracy attackerAcc, Armor targetArmor)
{
    bool hit = false;
    Print("Accuracy roll...", color_yellow, false);
    size_t roll = die_1d12.Roll();
    size_t totalVal = roll + attackerAcc.GetAcc();
    std::cout << roll << "+" << attackerAcc.GetAcc()
              << "=" << totalVal << " checked against " << targetArmor.GetArmor() << "\n";
    if (totalVal >= targetArmor.GetArmor())
    {
        hit = true;
        Print("Hit!", color_green);
    }
    else
    {
        Print("Miss...", color_yellow);
    }
    WaitForUser();
    return hit;
}

static PlayerBattleAction GetPlayerBattleAction()
{
    size_t actionNum;
    bool validAction = true;
    PlayerBattleAction action;
std::string const battleActionStr =
"What will the player do?\n\
1. Basic Attack\n\
2. Ability\n\
3. Item\n\
4. Defend\n\
5. (Look at fighter sheets)\n\
6. (Look at monster card)\n";

    Print(battleActionStr, color_gray, false);

    do
    {
        std::cin >> actionNum;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        switch (actionNum)
        {
        case 1:
            action = PlayerBattleAction::ATTACK;
            break;
        case 2:
            action = PlayerBattleAction::ABILITY;
            break;
        case 3:
            action = PlayerBattleAction::ITEM;
            break;
        case 4:
            action = PlayerBattleAction::DEFEND;
            break;
        case 5:
            action = PlayerBattleAction::CHECK_CHAR;
            break;
        case 6:
            action = PlayerBattleAction::CHECK_MONSTER;
            break;
        default:
            validAction = false;
            break;
        }

        if (!validAction)
        {
            std::cout << "Invalid choice, choose again\n";
        }
    } while (!validAction);

    return action;
}

void Battle::PlayerTurn()
{
    bool playerTurnDone = false;

    Print("***" + currFighter_->GetName() + "'s turn***", color_lightBlue, true);
    currFighter_->armor.Defend(false);

    while (!playerTurnDone)
    {
        switch (GetPlayerBattleAction())
        {
        case ATTACK:
            if (HitCheck(currFighter_->acc, monster_->armor))
            {
                Print("Damage roll...", color_yellow, false);
                size_t damage = currFighter_->attack.Damage();
                std::cout << currFighter_->GetName() << " Attacks monster for " << damage << " damage\n";
                monster_->hp.Damage(damage);
                WaitForUser();
            }
            playerTurnDone = true;
            break;
        case ABILITY:
        {
            Ability* abilityToUse = currFighter_->level.ChooseAbility();
            if (abilityToUse != nullptr)
            {
                abilityToUse->Execute(fighters_, true, monster_);
                playerTurnDone = true;
            }
        }
        break;
        case ITEM:
            playerTurnDone = true;
            break;
        case DEFEND:
            currFighter_->armor.Defend(true);
            playerTurnDone = true;
            break;
        case CHECK_CHAR:
            for (size_t i = 0; i < fighters_.size(); i++)
            {
                fighters_.at(i)->PrintAllStats();
                WaitForUser();
            }
            break;
        case CHECK_MONSTER:
            monster_->PrintAllStats();
            WaitForUser();
            break;
        default:
            break;
        }
    }

    // setup for next player turn
    if (fighters_.size() != 1)
    {
        currFighterIdx_++;
        if (currFighterIdx_ >= fighters_.size())
        {
            currFighterIdx_ = 0;
        }
        currFighter_ = fighters_.at(currFighterIdx_);
    }
}

void Battle::MonsterTurn()
{
    Player* target = nullptr;
    Print("***"+monster_->Name()+" Turn***", color_lightRed);

    // Check if we need to do the ability:
    if (!monster_->ability.Execute(fighters_, monster_))
    {
        // Didn't do ability, do basic attack
        // Figure out which target to attack
        Print("Basic Attack:");
        do
        {
            if (fighters_.size() == 1)
            {
                target = fighters_.at(0);
            }
            else
            {
                Print("Target roll...", color_yellow, false);
                size_t playerNum = die_1d6.Roll() - 1;
                if ((playerNum < fighters_.size()) && !fighters_.at(playerNum)->hp.IsDead())
                {
                    target = fighters_.at(playerNum);
                }
            }
        } while (!target);

        Print("Targeting: " + target->GetName());
        WaitForUser();

        if (HitCheck(monster_->acc, target->armor))
        {
            Print("Damage roll...", color_yellow, false);
            size_t damage = monster_->attack.Damage();
            std::cout << "does " << damage << " damage to " << target->GetName() << "\n";
            target->hp.Damage(damage);
            WaitForUser();
        }
    }
}