#pragma once
#include "Dice.h"

class BasicAttack
{
public:
    BasicAttack(Dice* attackDie):
        basicAttackDie_(attackDie)
    {}
    BasicAttack() {}
    ~BasicAttack() {}

    size_t Damage() { return basicAttackDie_->Roll() + damageMod_; }
    void Print() 
    { 
        std::cout << "BASIC ATTACK: " << basicAttackDie_->GetAmount() << "D" << basicAttackDie_->GetDieSize();
        if (basicAttackDie_->GetModifier() < 0)
        {
            std::cout << "-" << basicAttackDie_->GetModifier();
        }
        else if (basicAttackDie_->GetModifier() > 0)
        {
            std::cout << "+" << basicAttackDie_->GetModifier();
        }
        std::cout << "(" << damageMod_ << ")\n";
    }
private:
    Dice* basicAttackDie_;
    int damageMod_;
};

