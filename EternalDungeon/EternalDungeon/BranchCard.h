#pragma once
#include "CardObject.h"
#include "Event.h"

class BranchCard :
    public CardObject
{
public:
    BranchCard() {}
    BranchCard(std::vector<std::string> csvLine);
    ~BranchCard() {}

    void Draw(GameWorld& gameWorld);
    std::string Name() { return name_; }
private:
    std::string name_;
    Event event_;
};

