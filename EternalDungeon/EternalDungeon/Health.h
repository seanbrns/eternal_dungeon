#pragma once

class Health
{
public:
    Health(short maxHealth) : 
        health_(maxHealth), 
        maxHealth_(maxHealth),
        maxHealthMod_(0)
    {};
    Health() {}
    ~Health();

    bool IsDead() { return (health_ <= 0); }
    void Damage(short val);
    void Heal(short val);
    void Reset() { health_ = maxHealth_; }
    void HealthMod(short val) 
    {
        maxHealthMod_ += val; 
        if (health_ > maxHealthMod_)
        {
            health_ = maxHealthMod_;
        }
        this->Print();
    }
    void Print() { std::cout << "HP:" << health_ << "/" << maxHealth_ << "(" << maxHealthMod_ << ")\n"; }
private:
    short health_;
    short maxHealth_;
    short maxHealthMod_;
};