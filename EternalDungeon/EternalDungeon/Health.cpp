#include "stdafx.h"
#include "Health.h"


Health::~Health()
{
}

void Health::Heal(short val)
{
    health_ += val;
    if (health_ > (maxHealth_ + maxHealthMod_))
    {
        health_ = (maxHealth_ + maxHealthMod_);
    }
    this->Print();
}

void Health::Damage(short val)
{
    health_ -= val;
    if (health_ < 0)
    {
        health_ = 0;
    }
    this->Print();
}