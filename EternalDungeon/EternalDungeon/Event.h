#pragma once

class GameWorld;
class Event
{
public:
    typedef bool(*eventFuncPtr)(GameWorld& gameWorld);

    Event() {}
    ~Event();

    bool Execute(GameWorld& gameWorld);
    std::string Description() { return description_; }
    void SetDescription(std::string description) { description_ = description; }
    void SetEvent(eventFuncPtr eventFunc) { eventFunc_ = eventFunc; }
private:
    eventFuncPtr eventFunc_;
    std::string description_;
};