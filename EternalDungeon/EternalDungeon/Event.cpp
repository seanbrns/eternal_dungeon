#include "stdafx.h"
#include "Event.h"


Event::~Event()
{
}

bool Event::Execute(GameWorld& gameWorld)
{
    if (eventFunc_ != nullptr)
    {
        return eventFunc_(gameWorld);
    }
    return false;
}