#include "stdafx.h"
#include "Stat.h"
#include "Dice.h"
#include "Utility.h"

static Dice s_die1D12(1, 12);

Stat::Stat()
{
}


Stat::~Stat()
{
}

bool Stat::AgilityCheck(size_t val)
{
    Print("Agility Check:", color_lightYellow);
    size_t roll = s_die1D12.Roll();
    short totalVal = static_cast<short>(roll) + agility_ + agilityMod_;
    std::cout << roll << "+" << agility_ << "+" << agilityMod_
        << "=" << totalVal << " checked against " << val << "\n";

    if (totalVal >= val)
    {
        Print("Pass!", color_green);
        return true;
    }
    Print("Fail...", color_lightRed);
    return false;
}
bool Stat::MightCheck(size_t val)
{
    Print("Might Check:", color_lightYellow);
    size_t roll = s_die1D12.Roll();
    short totalVal = static_cast<short>(roll) + might_ + mightMod_;
    std::cout << roll << "+" << might_ << "+" << mightMod_
        << "=" << totalVal << " checked against " << val << "\n";

    if (totalVal >= val)
    {
        Print("Pass!", color_green);
        return true;
    }
    Print("Fail...", color_lightRed);
    return false;
}
bool Stat::KnowledgeCheck(size_t val)
{
    Print("Knowledge Check:", color_lightYellow);
    size_t roll = s_die1D12.Roll();
    short totalVal = static_cast<short>(roll) + knowledge_ + knowledgeMod_;
    std::cout << roll << "+" << knowledge_ << "+" << knowledgeMod_
        << "=" << totalVal << " checked against " << val << "\n";

    if (totalVal >= val)
    {
        Print("Pass!", color_green);
        return true;
    }
    Print("Fail...", color_lightRed);
    return false;
}
bool Stat::WillpowerCheck(size_t val)
{
    Print("Willpower Check:", color_lightYellow, false);
    size_t roll = s_die1D12.Roll();
    short totalVal = static_cast<short>(roll) + willpower_ + willpowerMod_;
    std::cout << roll << "+" << willpower_ << "+" << willpowerMod_ 
              << "=" << totalVal << " checked against " << val << "\n";

    if (totalVal >= val)
    {
        Print("Pass!", color_green);
        return true;
    }
    Print("Fail...", color_lightRed);
    return false;
}

void Stat::AgilityMod(short val)
{
    agilityMod_ += val;
}
void Stat::MightMod(short val)
{
    mightMod_ += val;
}
void Stat::KnowledgeMod(short val)
{
    knowledgeMod_ += val;
}
void Stat::WillpowerMod(short val)
{
    willpowerMod_ += val;
}

void Stat::PrintStats()
{
    std::cout << "Agility:" << agility_ << "(" << agilityMod_ << ")\n";
    std::cout << "Might:" << might_ << "(" << mightMod_ << ")\n";
    std::cout << "Knowledge:" << knowledge_ << "(" << knowledgeMod_ << ")\n";
    std::cout << "Willpower:" << willpower_ << "(" << willpowerMod_ << ")\n";
}