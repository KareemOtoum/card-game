#pragma once

#include "card.h"
#include <vector>
#include <iostream>

namespace terminal {
    void clear_screen   ();
    void print_score    (int score);
    void print_cards    (const std::vector<Card>& cards);
    void print_red      (std::string_view str);
    void print_green    (std::string_view str);
    void print_yellow   (std::string_view str);
}