#pragma once

#include <array>
#include <string>
#include <cstdint>

class Card {
public:
    enum suit : uint8_t;

    Card() { }
    Card(std::string_view value, suit suit) 
        : value_{ value }, suit_{ suit } { }

    std::string_view get_graphic() const { return Card::suit_graphics[suit_]; }
    std::string_view get_value_str() const { return value_; }
    int              get_value_int() const;

    static const std::array<std::string, 5> suit_graphics; 

private:
    std::string value_;
    suit suit_;
};

enum Card::suit : uint8_t {
    SPADES, 
    HEARTS, 
    DIAMONDS, 
    CLUBS,
    UNKOWN
};

inline const std::array<std::string, 5> Card::suit_graphics {
    "♠", 
    "♥", 
    "♦", 
    "♣",
    "?"
};