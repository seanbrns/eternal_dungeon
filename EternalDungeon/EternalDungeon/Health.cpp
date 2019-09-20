#include "stdafx.h"
#include "Health.h"


Health::~Health()
{
}

void Health::Heal(size_t val)
{
    health_ += val;
    if (health_ > (maxHealth_ + maxHealthMod_))
    {
        health_ = (maxHealth_ + maxHealthMod_);
    }
    this->Print();
}

void Health::Damage(size_t val)
{
    health_ -= val;
    if (health_ < 0)
    {
        health_ = 0;
    }
    this->Print();
}