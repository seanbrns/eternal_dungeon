#pragma once
#include "Deck.h"

class Player;

class GameWorld
{
public:
    GameWorld(std::vector<Player*> players,
                Deck dungeon,
                Deck loot,
                Deck treasure,
                Deck discard)
    : players_(players),
      dungeon_(dungeon),
      loot_(loot),
      treasure_(treasure),
      discard_(discard)
    {}
    ~GameWorld();

    std::vector<Player*> Players() { return players_; }
    Deck DungeonDeck() { return dungeon_; }
    Deck LootDeck() { return loot_; }
    Deck TreasureDeck() { return treasure_; }
    Deck DiscardDeck() { return discard_; }

private:
    std::vector<Player*> players_;
    Deck dungeon_;
    Deck loot_;
    Deck treasure_;
    Deck discard_;
};

