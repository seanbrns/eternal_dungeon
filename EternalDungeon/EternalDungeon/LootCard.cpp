#include "stdafx.h"
#include "LootCard.h"
#include "Player.h"

enum csvHeaderColumn
{
    AMOUNT = 0,
    NAME,
    TYPE,
    ACTIVE_EFFECT,
    PASSIVE_EFFECT
};

LootCard::LootCard(std::vector<std::string> csvLine)
{
    this->name_ = csvLine.at(NAME);
    //this->event_.SetEvent(FindEvent(csvLine.at(EFFECT)));
    //this->event_.SetDescription(csvLine.at(DESCRIPTION));
}

void LootCard::Draw(GameWorld& gameWorld)
{
    std::cout << "Loot Draw!\n";
}

void LootCard::ApplyPassive(Player* player)
{
    std::vector<Player*> equippedPlayer;
    equippedPlayer.push_back(player);

    lootPassive_.Execute(equippedPlayer);
}
