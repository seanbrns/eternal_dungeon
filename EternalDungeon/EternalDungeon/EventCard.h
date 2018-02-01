#pragma once
#include "CardObject.h"

class EventCard : public CardObject
{
public:
    EventCard();
    EventCard(std::vector<std::string> csvLine);
    ~EventCard();

    void Draw(GameWorld& gameWorld);
};

