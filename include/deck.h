#pragma once
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include "card.h"

class Deck {
public:
    Deck(int start_shuffles);

    const Card& check_next_card() const;
    const Card& get_next_card();
    void        shuffle();

private:
    std::array<Card, 52> cards_{};
    int next_card_{};
    std::mt19937 random_gen;
};