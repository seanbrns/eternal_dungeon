#pragma once
#include "CardObject.h"

class EventCard : public CardObject
{
public:
    EventCard();
    ~EventCard();

    void Draw(GameWorld& gameWorld);
};

