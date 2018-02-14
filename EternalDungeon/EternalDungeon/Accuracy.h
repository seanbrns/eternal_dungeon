#pragma once
class Accuracy
{
public:
    Accuracy(short accuracy) :
        accuracy_(accuracy),
        accuracyMod_(0)
    {};
    Accuracy() {}
    ~Accuracy();

    short GetAcc(void) { return (accuracy_ + accuracyMod_); }
    void AccMod(short val) { accuracyMod_ += val; }
    void Print() { std::cout << "ACC:" << accuracy_ << "(" << accuracyMod_ << ")\n"; }
private:
    short accuracy_;
    short accuracyMod_;
};
