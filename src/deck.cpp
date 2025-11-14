#include "deck.h"

bool Deck::add_card(Card card) {
    if(cards_.size() >= size_) return false;
    cards_.push_back(card);
    return true;
}

Deck::Deck(int start_shuffles, int size) 
    : random_gen { std::random_device{}() },
    size_ { size }{

    for(int i{}; i <= Card::suit::CLUBS; ++i) {
        auto suit = static_cast<Card::suit>(i);
        add_card({"A", suit});
        add_card({"K", suit});
        add_card({"Q", suit});
        add_card({"J", suit});
        for(int num{ 2 }; num <= 10; ++num) {
            add_card({std::to_string(num), suit});
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
    int idx = next_card_;
    
    if(idx == size_ - 1) {
        GameState::end_game();
    }
    next_card_++;
    next_card_ % size_;
    return cards_[idx];
}

const Card& Deck::check_next_card() const {
    return cards_[next_card_];
}