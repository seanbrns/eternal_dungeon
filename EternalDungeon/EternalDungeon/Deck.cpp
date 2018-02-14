#include "stdafx.h"
#include "Deck.h"
#include <algorithm>
#include <random>

Deck::Deck()
{
}

Deck::Deck(std::vector<CardObject*> cardVec)
{
    for (size_t i = 0; i < cardVec.size(); i++)
    {
        this->AddCard(cardVec.at(i));
    }
}

Deck::~Deck()
{
}

void Deck::AddCard(CardObject* card) 
{ 
    deck_.push_back(card); 
}

void Deck::RemoveCard(CardObject* card)
{
    deck_.erase(std::remove(deck_.begin(), deck_.end(), card), deck_.end());
    deck_.shrink_to_fit();
}

void Deck::RemoveCardAt(size_t idx)
{
    deck_.erase(deck_.begin() + idx);
    deck_.shrink_to_fit();
}

CardObject* Deck::GetTopCard()
{
    return deck_.at(0);
}

CardObject* Deck::GetBottomCard()
{
    return deck_.back();
}

CardObject* Deck::GetCardAt(size_t idx)
{
    return deck_.at(idx);
}

size_t Deck::GetSize()
{
    return deck_.size();
}

void Deck::SwapCards(CardObject* card1, CardObject* card2)
{
    std::vector<CardObject*>::iterator card1Idx = std::find(deck_.begin(), deck_.end(), card1);
    std::vector<CardObject*>::iterator card2Idx = std::find(deck_.begin(), deck_.end(), card2);
    std::swap(card1, card2);
}

void Deck::Shuffle(size_t start, size_t end)
{
    std::random_device rdev;
    std::default_random_engine re(rdev());
    std::shuffle(deck_.begin() + start, deck_.begin() + end, re);
}

void Deck::TransferCardToDeck(CardObject* card, Deck &toDeck)
{
    toDeck.AddCard(card);
    deck_.erase(std::remove(deck_.begin(), deck_.end(), card), deck_.end());
    deck_.shrink_to_fit();
}