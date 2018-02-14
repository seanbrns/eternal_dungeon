#include "stdafx.h"
#include "EventList.h"
#include "GameWorld.h"
#include <map>

// Note: Create new events here and add to list
static bool DefaultEvent(GameWorld& gameWorld);

static const std::map<std::string, Event::eventFuncPtr> eventMap =
{
    { "default", DefaultEvent },

};

//*****************************************************************************
// FindEvent
//*****************************************************************************
Event::eventFuncPtr FindEvent(std::string name)
{
    Event::eventFuncPtr event_ = nullptr;
    auto eventItr = eventMap.find(name);
    if (eventItr != eventMap.end())
    {
        event_ = eventItr->second;
        std::cout << "Event FOUND!" << std::endl;
    }
    else
    {
        std::cout << "ERROR - could not find event: " << name << std::endl;
    }

    return event_;
}

//*****************************************************************************
// event list
//*****************************************************************************
bool DefaultEvent(GameWorld& gameWorld)
{
    std::cout << "ERROR-default event\n";
    return true;
}

