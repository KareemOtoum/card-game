#include "deck.h"

Deck::Deck(int start_shuffles) 
    : random_gen { std::random_device{}() } {
    int idx{};
    for(int i{}; i <= Card::suit::CLUBS; ++i) {
        auto suit = static_cast<Card::suit>(i);
        cards_[idx++] = Card("A", suit);
        cards_[idx++] = Card("K", suit);
        cards_[idx++] = Card("Q", suit);
        cards_[idx++] = Card("J", suit);
        for(int num{ 2 }; num <= 10; ++num) {
            cards_[idx++] = Card(std::to_string(num), suit);
        }
    }

    for(int i{}; i < start_shuffles; ++i) {
        shuffle();
    }
}

void Deck::shuffle() {
    int n = cards_.size();
    for(int i{ n - 1 }; i >= 1; --i) {
        std::uniform_int_distribution<> dis(0, i);
        std::swap(cards_[dis(random_gen)], cards_[i]);
    }
}

const Card& Deck::get_next_card() {
    return cards_[next_card_++];
}

const Card& Deck::check_next_card() const {
    return cards_[next_card_];
}