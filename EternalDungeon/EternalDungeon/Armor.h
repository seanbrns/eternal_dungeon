#pragma once
class Armor
{
public:
    Armor(short armor) :
        armor_(armor),
        armorMod_(0),
        defending_(false)
    {};
    Armor() {};
    ~Armor();

    short GetArmor(void) { return armor_; }
    void ArmorMod(short val) { armorMod_ += val; }
    void Defend(bool defend) 
    { 
        // print if different
        if (defend != defending_)
        {
            if (defend)
            {
                std::cout << "Defending -> ";
                ArmorMod(2);
            }
            else
            {
                std::cout << "Stopped Defending -> ";
                ArmorMod(-2);
            }
            Print();
        }

        defending_ = defend; 
    }
    bool IsDefending() { return defending_; }
    void Print() { std::cout << "ARMOR:" << armor_ << "(" << armorMod_ << ")\n"; }
private:
    short armor_;
    short armorMod_;
    bool defending_;
};

