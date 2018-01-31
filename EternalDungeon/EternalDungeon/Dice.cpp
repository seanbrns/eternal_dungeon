#include "stdafx.h"
#include "Dice.h"
#include <random>
#include <algorithm>
#include <sstream>
#include "Utility.h"

Dice::Dice(size_t amountVal, size_t dieSizeVal, int modifierVal)
{
    amount = amountVal;
    dieSize = dieSizeVal;
    modifier = modifierVal;
}

Dice::~Dice()
{

}

size_t Dice::Roll()
{
    size_t value = 0;

    std::random_device rdev;
    std::default_random_engine re(rdev());
    std::uniform_int_distribution<> dis{ 1, (int)dieSize };

    for (size_t i = 0; i < amount; i++)
    {
        value += dis(re);  // generates number in the range 1..dieSize
    }

    // make sure we don't wrap around on subtraction
    // note: don't care about wrap around on addition right now
    if ((modifier < 0) && value < abs(modifier))
    {
        value = 0;
    }
    else
    {
        value += modifier;
    }

    std::cout << "Rolled " << this->amount << "D" << this->dieSize;
    if (this->modifier < 0)
    {
        std::cout << "-" << modifier;
    }
    else if (modifier > 0)
    {
        std::cout << "+" << modifier;
    }
    std::cout << " for " << value << "\n";

    return value;
}

void Dice::SetAmount(size_t val)
{
    amount = val;
}

void Dice::SetDieSize(size_t val)
{
    dieSize = val;
}

void Dice::SetModifier(int val)
{
    modifier = val;
}

size_t Dice::GetAmount()
{
    return amount;
}

size_t Dice::GetDieSize()
{
    return dieSize;
}

int Dice::GetModifier()
{
    return modifier;
}

Dice GetDieFromString(std::string str)
{
    // String Format is:
    // "XdY+Z" or "XdY-Z"
    // X = number of dice
    // Y = number of face on die
    // Z = addition modifier
    bool posModifier = true;
    size_t xDelIdx = str.find("d");
    size_t yDelIdx = str.find("+");

    if (yDelIdx == std::string::npos)
    {
        yDelIdx = str.find("-");
        posModifier = false;
    }

    Dice retval;
    std::string x = str.substr(0, xDelIdx);
    std::string y = str.substr(xDelIdx + 1, yDelIdx);
    std::string z = str.substr(yDelIdx + 1);

    std::stringstream X(x);
    std::stringstream Y(y);
    std::stringstream Z(z);
    int val;
    X >> val;
    retval.SetAmount(val);
    Y >> val;
    retval.SetDieSize(val);

    std::string temp = str.substr(4, 1);

    if (posModifier)
    {
        Z >> val;
        retval.SetModifier(val);
    }
    else
    {
        Z >> val;
        retval.SetModifier(-val);
    }

    return retval;
}
