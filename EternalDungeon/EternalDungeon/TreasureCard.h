#pragma once
#include "CardObject.h"
class TreasureCard :
    public CardObject
{
public:
    TreasureCard();
    ~TreasureCard();

    void Draw(GameWorld& gameWorld);
};

