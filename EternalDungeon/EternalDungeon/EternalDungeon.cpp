// EternalDungeon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameWorld.h"
#include "MonsterCard.h"
#include "EventCard.h"
#include "Player.h"
#include "LootCard.h"
#include "TreasureCard.h"
#include "BranchCard.h"
#include "Utility.h"
#include "csv_read.h"
#include <sstream>

std::string eternalDungeon = "\
         ___________ __                              __    ________                                                                 \n\
         \\_   ______/  |_  ___________  ____ _____  |  |   \\______ \\  __ __  ____   ____   ____  ____   ____                     \n\
  ______  |    __)_\\   ___/ __ \\_  __ \\/    \\\\__  \\ |  |    |    |  \\|  |  \\/    \\ / ___\\_/ __ \\/  _ \\ /    \\   ______ \n\
 /_____/  |        \\|  | \\  ___/|  | \\|   |  \\/ __ \\|  |__  |    `   |  |  |   |  / /_/  \\  ___(  <_> |   |  \\ /_____/       \n\
         /_______  /|__|  \\___  |__|  |___|  (____  |____/ /_______  |____/|___|  \\___  / \\___  \\____/|___|  /                  \n\
                 \\/           \\/           \\/     \\/               \\/           \\/_____/      \\/           \\/               \n";

double version = 0.1;

//**********************************************************
// Static function definitions
//**********************************************************
template <typename T>
static Deck BuildDeckFromCsv(std::string csvPath);

static std::vector<Player*> ImportPlayers(std::string csvPath);

//**********************************************************
// local variables/constants
//**********************************************************
static const std::string csvPathMonsters = "C:/Users/seanby/Desktop/Eternal Dungeon/cards/Monsters.csv";
static const std::string csvPathBranches = "C:/Users/seanby/Desktop/Eternal Dungeon/cards/Branches.csv";
static const std::string csvPathLoot = "C:/Users/seanby/Desktop/Eternal Dungeon/cards/Loot.csv";
static const std::string csvPathStairs = "C:/Users/seanby/Desktop/Eternal Dungeon/cards/Stairs.csv";
static const std::string csvPathEvents = "C:/Users/seanby/Desktop/Eternal Dungeon/cards/Events.csv";
static const std::string csvPathTreasure = "C:/Users/seanby/Desktop/Eternal Dungeon/cards/Treasure.csv";
static const std::string csvPathPlayers = "C:/Users/seanby/Desktop/Eternal Dungeon/cards/Players.csv";

static const size_t TABLE_HEADER_IDX = 0;
static const size_t HEADER_CARD_AMOUNT = 0;

#define PRINT_IMPORT_STATS

//*****************************************************************************
// main
//*****************************************************************************
int main()
{
    // setup some cards/players
    Deck branches = BuildDeckFromCsv<BranchCard>(csvPathBranches);
    Deck events = BuildDeckFromCsv<EventCard>(csvPathEvents);

    Player player1("p1"), player2("p2"), player3("p3");
    LootCard l1, l2, l3;
    TreasureCard t1, t2, t3;
    MonsterCard m1, m2, m3;
    EventCard e1, e2, e3;
    //populate some vectors of those and the game world
    std::vector<Player*> players = { &player1, &player2, &player3 };
    std::vector<CardObject*> dungeonCards = { &m1, &m2, &m3, &e1, &e2, &e3 };
    std::vector<CardObject*> lootCards = { &l1, &l2, &l3 };
    std::vector<CardObject*> treasureCards = {&t1, &t2, &t3};

    Deck dungeon(dungeonCards), loot(lootCards), treasure(treasureCards), discard;
    GameWorld gameWorld(players, dungeon, loot, treasure, discard);

    bool done = false;
    size_t activePlayerNum = 0;

    Print(eternalDungeon, color_red);
    Print("version:", color_red, false);
    std::cout << version << "\n";

    size_t deadNum = 0;

    // game loop
    while (!done)
    {
        done = gameWorld.Players().at(activePlayerNum)->DoTurn(gameWorld);

        activePlayerNum++;
        if (activePlayerNum >= gameWorld.Players().size())
        {
            activePlayerNum = 0;
        }

        // check whether all players are dead
        for (int i = 0; i < gameWorld.Players().size(); i++)
        {
            if (gameWorld.Players().at(i)->hp.IsDead())
            {
                deadNum++;
            }
        }

        if (deadNum == gameWorld.Players().size())
        {
            Print("All Players are DEAD...", color_red);
            done = true;
        }
        else
        {
            deadNum = 0; //reset
        }
    }

    std::cout << "END\n\n";
    std::system("pause");

    return 0;
}

//*****************************************************************************
// BuildDeckFromCsv
//
//*****************************************************************************
template <typename T>
static Deck BuildDeckFromCsv(std::string csvPath)
{
    csv_read csv;
    Deck deck;
    std::vector<std::vector<std::string>> stringTable;

    stringTable = csv.read_table(csvPath);

    // Grab data starting after header
    for (size_t idx = (TABLE_HEADER_IDX + 1); idx < stringTable.size(); idx++)
    {
        std::stringstream ss(stringTable.at(idx).at(HEADER_CARD_AMOUNT));
        size_t tempVal;
        size_t amount;

        ss >> tempVal;
        amount = tempVal;

        if (amount > 0)
        {
            for (size_t i = 0; i < amount; i++)
            {
                deck.AddCard(new T(stringTable.at(idx)));
#ifdef PRINT_IMPORT_STATS
                std::cout << "Imported: "<< deck.GetBottomCard()->Name() << "\n";
#endif
            }
        }
    }

    std::cout << "DONE\n";
    return deck;
}

static std::vector<Player*> ImportPlayers(std::string csvPath)
{
    csv_read csv;
    std::vector<Player*> players;
    std::vector<std::vector<std::string>> stringTable;

    stringTable = csv.read_table(csvPath);

    // Grab data starting after header
    for (size_t idx = (TABLE_HEADER_IDX + 1); idx < stringTable.size(); idx++)
    {
        players.push_back(new Player(stringTable.at(idx)));

#ifdef PRINT_IMPORT_STATS
        players.back()->GetName();
#endif
    }

    std::cout << "DONE\n";
    return players;
}