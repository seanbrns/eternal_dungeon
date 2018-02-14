#pragma once
#include "CardObject.h"
#include "Event.h"

class EventCard : 
    public CardObject
{
public:
    EventCard() {}
    EventCard(std::vector<std::string> csvLine);
    ~EventCard() {}

    void Draw(GameWorld& gameWorld);
    std::string Name() { return name_; }
private:
    std::string name_;
    Event event_;
};

