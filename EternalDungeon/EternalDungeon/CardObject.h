#pragma once
#include "stdafx.h"

class GameWorld;

class CardObject
{
public:
    CardObject();
    ~CardObject();
    virtual void Draw(GameWorld& gameWorld) { std::cout << "ERROR-no draw\n"; }
    virtual void Reset() { std::cout << "ERROR-no reset\n"; }
    virtual std::string Name() { std::cout << "ERROR-no name\n"; return "ERROR"; }
};

