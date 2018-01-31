#include "stdafx.h"
#include "Player.h"
#include "Utility.h"
#include "GameWorld.h"

enum PlayerTurnAction
{
    DRAW_CARD,
    REST,
    TRAVEL,
    USE_ITEM,
    USE_ABILITY,
    PLAYER_STATS,
    EXIT_GAME
};

enum PlayerRestAction
{
    TRADE,
    EQUIP_UNEQUIP,
    END_TURN
};

static Dice s_die1D6(1, 6);
static Dice s_die1D6P4(1, 6, 4);

static PlayerTurnAction GetStartTurnAction();
static PlayerRestAction GetRestAction();

static Player* ChooseTradePartner(std::vector<Player*> possibleTraders);

Player::~Player()
{
}

//*****************************************************************************
// DoTurn
//*****************************************************************************
bool Player::DoTurn(GameWorld& gameWorld)
{
    // activate player
    this->SetActive(true);
    bool exitGame = false;
    std::cout << "----------" << this->GetName() << "'s Turn----------\n";

    if (this->hp.IsDead())
    {
        std::cout << "player dead, skip turn\n";
    }
    else
    {
        bool turnDone = false;
        while (!turnDone && !exitGame)
        {
            switch (GetStartTurnAction())
            {
            case PlayerTurnAction::DRAW_CARD:
                this->DrawDungeonCard(gameWorld);
                turnDone = true;
                break;
            case PlayerTurnAction::REST:
                this->Rest(gameWorld);
                turnDone = true;
                break;
            case PlayerTurnAction::TRAVEL:
                turnDone = this->Travel(gameWorld);
                break;
            case PlayerTurnAction::USE_ITEM:
            {
                LootCard* loot = this->inventory.ChooseLoot();
                this->inventory.UseLoot(loot);
            }
            break;
            case PlayerTurnAction::USE_ABILITY:
            {
                Ability* abilityToUse = this->level.ChooseAbility();
                if (abilityToUse != nullptr)
                {
                    std::vector<Player*> potentialTargets;
                    for (size_t i = 0; i < gameWorld.Players().size(); i++)
                    {
                        if (gameWorld.Players().at(i)->branchIdx_ == this->branchIdx_)
                        {
                            potentialTargets.push_back(gameWorld.Players().at(i));
                        }
                    }
                    abilityToUse->Execute(potentialTargets);
                }
            }
            break;
            case PlayerTurnAction::PLAYER_STATS:
            {
                bool done = false;
                std::cout << "Which player stats:\n";
                for (size_t i = 0; i < gameWorld.Players().size(); i++)
                {
                    std::cout << (i + 1) << ". " << gameWorld.Players().at(i)->GetName() << "\n";
                }

                while (!done)
                {
                    size_t playerNum;
                    std::cin >> playerNum;
                    playerNum--;

                    if (playerNum < gameWorld.Players().size())
                    {
                        gameWorld.Players().at(playerNum)->PrintAllStats();
                        done = true;
                    }
                    else
                    {
                        std::cout << "Invalid selection\n";
                    }
                }
            }
                break;
            case PlayerTurnAction::EXIT_GAME:
                exitGame = true;
                break;
            default:
                break;
            }
        }
        
    }

    // deactivate player
    this->SetActive(false);

    return exitGame;
}

//*****************************************************************************
// Rest
//*****************************************************************************
void Player::Rest(GameWorld& gameWorld)
{
    std::string const restStartStr =
"                  (       \n\
                   )       \n\
               )  ( (      \n\
             )  /\\   )    \n\
REST        (  // |\\      \n\
          _ -.;_/ \\\\--.  \n\
         (_;-// | \ \-'. \\ \n\
         ( `.__ _  ___,')  \n\
          `'(_ )_)(_)_)'   \n";

    std::cout << restStartStr;
    bool traded = false;

    // restore player health
    this->hp.Heal(s_die1D6P4.Roll());

    /* regain any abilities used up */


    // Optional choices
    bool endTurn = false;
    do
    {
        switch (GetRestAction())
        {
        case TRADE:
            if (traded)
            {
                std::cout << "Already traded this turn\n";
            }
            else if (this->RestingTrade(gameWorld))
            {
                traded = true;
            }
            break;
        case EQUIP_UNEQUIP:
            this->ChangeEquipment();
            break;
        case END_TURN:
            endTurn = true;
            break;
        default:
            break;
        }
    } while (!endTurn);

    // Roll for ambush
    if (s_die1D6.Roll() == 6)
    {
        std::cout << "AMBUSHED!\n";
        // TODO : battle now
    }
}

//*****************************************************************************
// ChangeEquipment
//*****************************************************************************
void Player::ChangeEquipment()
{
    std::cout << "Which equipment would you like to change?\n";
    LootCard* loot = this->inventory.ChooseLoot();
    int input;
    bool done = false;

    if (loot == nullptr)
    {
        return;
    }

    std::cout <<
"1.Unequip\n\
2.Equip\n";

    while (!done)
    {
        std::cin >> input;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        switch (input)
        {
        case 1:
            this->inventory.UnEquipLoot(loot);
            done = true;
        case 2:
            this->inventory.EquipLoot(loot);
            break;
        default:
            std::cout << "Invalid selection\n";
            break;
        }
    }
}

//*****************************************************************************
// RestingTrade
//*****************************************************************************
bool Player::RestingTrade(GameWorld& gameWorld)
{
    bool success = false;
    std::vector<Player*> possibleTraders;

    // Get all possible traders
    for (size_t i = 0; i < gameWorld.Players().size(); i++)
    {
        // - must be in same location
        // - must not be same player as player turn
        // - must not be dead
        if ((gameWorld.Players().at(i)->hp.IsDead() == false) &&
            (gameWorld.Players().at(i) != this) &&
            (gameWorld.Players().at(i)->GetBranch() == this->GetBranch()))
        {
            possibleTraders.push_back(gameWorld.Players().at(i));
        }
    }

    // Only possible to trade if:
    // - there are other possible players to trade with
    // - the current player has items to trade
    // TODO: for now randomly decide to trade or not
    if (this->inventory.IsEmpty())
    {
        std::cout << "You don't have any items to trade\n";
    }
    else if (possibleTraders.empty())
    {
        std::cout << "No one to trade with\n";
    }
    else
    {
        Player* tradePartner = ChooseTradePartner(possibleTraders);
        LootCard* loot = this->inventory.ChooseLoot();
        
        this->inventory.RemoveLoot(loot);
        tradePartner->inventory.AddLoot(loot);
        std::cout << this->GetName() << " gave " << tradePartner->GetName() << " " << loot->Name() << "\n";

        success = true;
    }
    return success;
}

//*****************************************************************************
// ChooseTradePartner
//*****************************************************************************
static Player* ChooseTradePartner(std::vector<Player*> possibleTraders)
{
    Player* tradePartner = nullptr;
    int playerNum;

    Print("Which Player would you like to trade with?", color_gray);
    for (size_t i = 0; i < possibleTraders.size(); i++)
    {
        std::cout << (i+1) << ". " << possibleTraders.at(i)->GetName() << "\n";
    }

    while (tradePartner == nullptr)
    {
        std::cin >> playerNum;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        playerNum--;
        if (playerNum < possibleTraders.size())
        {
            tradePartner = possibleTraders.at(playerNum);
        }
        else
        {
            std::cout << "Invalid player selection\n";
        }
    }
    return tradePartner;
}

//*****************************************************************************
// Travel
//*****************************************************************************
bool Player::Travel(GameWorld& gameWorld)
{
    bool traveled = true;

    std::cout << "chose to travel\n";
    return traveled;
    /* do travel things */
}

//*****************************************************************************
// EndTurn
//*****************************************************************************
void Player::EndTurn(GameWorld& gameWorld)
{
    std::cout << "chose to end their turn\n";
    /* do end turn things */
}

//*****************************************************************************
// DrawDungeonCard
//*****************************************************************************
void  Player::DrawDungeonCard(GameWorld& gameWorld)
{
    std::cout << "chose to draw\n";
    gameWorld.DungeonDeck().GetTopCard()->Draw(gameWorld);

    /* do draw card things */
}

//*****************************************************************************
// GetStartTurnAction
//*****************************************************************************
static PlayerTurnAction GetStartTurnAction()
{
    int actionNum;
    bool validAction = true;
    PlayerTurnAction action;

    std::string const actionStr =
"What will the player do?\n\
1. Draw card\n\
2. Rest\n\
3. Travel\n\
4. Item\n\
5. Ability\n\
6. (Player Stats)\n\
7. (Exit Game)\n";

    Print(actionStr, color_gray, false);
    do
    {
        std::cin >> actionNum;

        switch (actionNum)
        {
        case 1:
            action = PlayerTurnAction::DRAW_CARD;
            break;
        case 2:
            action = PlayerTurnAction::REST;
            break;
        case 3:
            action = PlayerTurnAction::TRAVEL;
            break;
        case 4:
            action = PlayerTurnAction::USE_ITEM;
            break;
        case 5:
            action = PlayerTurnAction::USE_ABILITY;
            break;
        case 6:
            action = PlayerTurnAction::PLAYER_STATS;
            break;
        case 7:
            action = PlayerTurnAction::EXIT_GAME;
            break;
        default:
            validAction = false;
            break;
        }

        if (!validAction)
        {
            std::cout << "Invalid choice, choose again\n";
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    } while (!validAction);

    return action;
}

static PlayerRestAction GetRestAction()
{
    int actionNum;
    bool validAction = true;
    PlayerRestAction action;

    std::string const actionStr =
"What will the player do?\n\
1.Trade\n\
2.Equip/Unequip\n\
3.End Turn\n";

    Print(actionStr, color_gray, false);
    do
    {
        std::cin >> actionNum;

        switch (actionNum)
        {
        case 1:
            action = PlayerRestAction::TRADE;
            break;
        case 2:
            action = PlayerRestAction::EQUIP_UNEQUIP;
            break;
        case 3:
            action = PlayerRestAction::END_TURN;
            break;
        default:
            validAction = false;
            break;
        }

        if (!validAction)
        {
            std::cout << "Invalid choice, choose again\n";
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    } while (!validAction);

    return action;
}

void Player::PrintAllStats()
{
    std::cout << "========= " << name_ << "=========\n";
    level.PrintLvl();
    hp.Print();
    acc.Print();
    armor.Print();
    attack.Print();
    stats.PrintStats();
    level.PrintAbilities();
}