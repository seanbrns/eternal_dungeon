#pragma once
#include "CardObject.h"
class BranchCard :
    public CardObject
{
public:
    BranchCard();
    BranchCard(std::vector<std::string> csvLine);
    void Draw(GameWorld& gameWorld);
    ~BranchCard();
};

