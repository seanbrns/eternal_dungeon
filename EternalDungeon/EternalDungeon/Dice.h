#pragma once

class Dice
{
private:
    size_t amount;
    size_t dieSize;
    int modifier;

public:
    Dice(size_t amountVal = 0, size_t dieSizeVal = 0, int modifierVal = 0);
    ~Dice();

    size_t Roll();
    void SetAmount(size_t val);
    void SetDieSize(size_t val);
    void SetModifier(int val);
    size_t GetAmount();
    size_t GetDieSize();
    int GetModifier();
};

Dice GetDieFromString(std::string str);

