#pragma once
#include "CardObject.h"
class TreasureCard :
    public CardObject
{
public:
    TreasureCard();
    TreasureCard(std::vector<std::string> csvLine);
    ~TreasureCard();

    void Draw(GameWorld& gameWorld);
};

