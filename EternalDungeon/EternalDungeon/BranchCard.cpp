#include "stdafx.h"
#include "BranchCard.h"
#include "csv_read.h"
#include "EventList.h"

enum csvHeaderColumn
{
    AMOUNT = 0,
    NAME,
    EFFECT,
    DESCRIPTION,
};

BranchCard::BranchCard(std::vector<std::string> csvLine)
{
    this->name_ = csvLine.at(NAME);
    this->event_.SetEvent(FindEvent(csvLine.at(EFFECT)));
    this->event_.SetDescription(csvLine.at(DESCRIPTION));
}

void BranchCard::Draw(GameWorld& gameWorld)
{
    std::cout << "Branch Draw!\n";
}