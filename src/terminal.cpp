#include "terminal.h"

namespace terminal {
    
    void print_cards(const std::vector<Card>& cards) {
        for(auto& card : cards) {
            std::cout << "┌─────┐";
        }
        std::cout << "\n";
        
        // print value
        for(auto& card : cards) {
            std::string_view value { card.get_value_str() };
            std::cout << "|";
            if(value.size() == 1) std::cout << " ";
            std::cout << value << "   |";
        }
        std::cout << "\n";

        for(auto& card : cards) {
            std::cout << "|     |";
        }
        std::cout << "\n";

        // print suit
        for(auto& card : cards) {
            std::string_view graphic { card.get_graphic() };
            std::cout << "|   ";
            std::cout << graphic << " |";
        }

        std::cout << "\n";
        for(auto& card : cards) {
            std::cout << "└─────┘";
        }
        std::cout << "\n";
    }
    
    void clear_screen() {
        std::cout << "\033[2J\033[1;1H";
    }

    void print_red(std::string_view str) {
        std::cout << "\033[31m" << str << "\033[0m"; 
    }

    void print_green(std::string_view str) {
        std::cout << "\033[32m" << str << "\033[0m";
    }

    void print_yellow(std::string_view str) {
        std::cout << "\033[33m" << str << "\033[0m";
    }

    void print_score(int score, bool final) {
        std::cout << "=====================\n";
        if(!final) {
            std::cout << "      \033[1;4;32mScore:\033[0m " 
                << score << "\n";
        } else {
            std::cout << "\033[1;4;32mFinal Score:\033[0m " 
                << score << "\n";
        }
        std::cout << "=====================\n";
    }
}