#include "card.h"

int Card::get_value_int() const {
    if(value_ == "A") return 1;
    if(value_ == "K") return 13;
    if(value_ == "Q") return 12;
    if(value_ == "J") return 11;

    // should be a number
    try {
        return std::stoi(value_);
    }
    catch(const std::exception& e) {
        return -1;
    }
    
    return -1;
}