#pragma once
#include "CardObject.h"

class StairCard :
    public CardObject
{
public:
    StairCard();
    StairCard(std::vector<std::string> csvLine);
    ~StairCard();

    void Draw(GameWorld& gameWorld);
};

