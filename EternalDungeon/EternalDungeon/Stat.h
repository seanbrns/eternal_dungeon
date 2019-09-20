#pragma once
class Stat
{
public:
    Stat();
    ~Stat();
    bool AgilityCheck(size_t val);
    bool MightCheck(size_t val);
    bool KnowledgeCheck(size_t val);
    bool WillpowerCheck(size_t val);

    void AgilityMod(short val);
    void MightMod(short val);
    void KnowledgeMod(short val);
    void WillpowerMod(short val);
    void PrintStats();
private:
    short agility_;
    short agilityMod_;
    short might_;
    short mightMod_;
    short knowledge_;
    short knowledgeMod_;
    short willpower_;
    short willpowerMod_;
};