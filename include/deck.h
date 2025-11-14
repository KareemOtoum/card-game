#pragma once
#include <array>
#include <vector>
#include <algorithm>
#include <random>

#include "card.h"
#include "game_state.h"

class Deck {
public:
    Deck(int start_shuffles, int size);

    const Card& check_next_card() const;
    const Card& get_next_card();
    void        shuffle();
    bool        add_card(Card);
private:

    std::vector<Card> cards_;
    int size_{};
    int next_card_{};
    std::mt19937 random_gen;
};