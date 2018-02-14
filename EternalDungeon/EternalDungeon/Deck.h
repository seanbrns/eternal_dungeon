#pragma once
#include "CardObject.h"

class Deck
{
public:
    Deck();
    Deck(std::vector<CardObject*> cardVec);
    ~Deck();

    void AddCard(CardObject* card);
    void RemoveCard(CardObject* card);
    void RemoveCardAt(size_t idx);
    CardObject* GetTopCard();
    CardObject* GetCardAt(size_t idx);
    size_t GetSize();
    void SwapCards(CardObject* card1, CardObject* card2);
    void Shuffle(size_t start = 0, size_t end = 0);
    void TransferCardToDeck(CardObject* card, Deck &toDeck);
    CardObject* GetBottomCard();
private:
    std::vector<CardObject*> deck_;

};