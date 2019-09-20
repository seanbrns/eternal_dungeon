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
    void Damage(size_t val);
    void Heal(size_t val);
    void Reset() { health_ = maxHealth_; }
    void HealthMod(size_t val)
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
    size_t health_;
    size_t maxHealth_;
    size_t maxHealthMod_;
};