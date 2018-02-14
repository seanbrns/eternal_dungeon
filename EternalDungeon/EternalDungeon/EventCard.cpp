#include "stdafx.h"
#include "EventCard.h"
#include "csv_read.h"
#include "EventList.h"

enum csvHeaderColumn
{
    AMOUNT = 0,
    NAME,
    EFFECT,
    DESCRIPTION,
};

EventCard::EventCard(std::vector<std::string> csvLine)
{
    this->name_ = csvLine.at(NAME);
    this->event_.SetEvent(FindEvent(csvLine.at(EFFECT)));
    this->event_.SetDescription(csvLine.at(DESCRIPTION));
}

void EventCard::Draw(GameWorld& gameWorld)
{
    std::cout << "Event Draw!\n";
}