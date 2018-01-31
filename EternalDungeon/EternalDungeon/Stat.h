#pragma once
class Stat
{
public:
    Stat();
    ~Stat();
    bool AgilityCheck(short val);
    bool MightCheck(short val);
    bool KnowledgeCheck(short val);
    bool WillpowerCheck(short val);

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