#pragma once
#include <array>
#include "card.h"

class Deck {
public:
    void shuffle();
    const Card& get_next_card();

private:
    std::array<Card, 52> cards_{};
    int current_card_{};
};