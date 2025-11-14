
#include "terminal.h"
#include "deck.h"
#include "game_state.h"
#include <sstream>
#include <thread>
#include <chrono>

void handle_guess(const Card& curr, const Card& next, bool higher);
void handle_unkown();

int main() {
    using namespace std::chrono_literals;

    const int shuffles { 10 };
    const int deck_size { 52 };
    Deck deck{ shuffles, deck_size };
    Card mystery_card {"?", Card::suit::UNKOWN};

    std::string input;

    while(GameState::in_play_) {
        terminal::clear_screen();
        terminal::print_score(GameState::get_score());

        auto& current_card = deck.get_next_card();
        if(!GameState::in_play_) break;

        std::vector<Card> display_cards { 
            current_card, mystery_card };

        terminal::print_cards(display_cards);
        std::cout << "Higer or lower? (h/l): ";

        std::getline(std::cin, input);
        
        terminal::clear_screen();
        auto& next_card { deck.check_next_card() };

        if(input == "q") {
            GameState::in_play_ = false;
            break;
        } else if(input == "h") {
            handle_guess(current_card, next_card, true);
        } else if(input == "l") {
            handle_guess(current_card, next_card, false);
        } else {
            handle_unkown();
        }
        std::this_thread::sleep_for(2s);
    }

    return 0;
}

void correct_guess() {
    GameState::correct_guess();

    if(GameState::get_streak() > 1) {
        std::string streak_str = 
        std::to_string(GameState::get_streak()) + "x Streak!\n";
        terminal::print_yellow(streak_str);
    }

    std::string score_add_str = "+" + 
            std::to_string(
                GameState::correct_guess_pts * GameState::get_streak()
            ) + " Correct!\n"; 
    terminal::print_green(score_add_str);
}

void incorrect_guess() {
    terminal::print_red("-2 Wrong...\n");
    GameState::incorrect_guess();
}

void handle_guess
    (const Card& curr, const Card& next, bool higher) {
    auto curr_val = curr.get_value_int();
    auto next_val = next.get_value_int();

    // invalid card in the deck
    if(curr_val == -1 || next_val == -1) {
        std::cerr << "Detected invalid card... exiting game\n";
        GameState::in_play_ = false;
        return;
    }

    if(higher && curr_val <= next_val) correct_guess();
    else if(!higher && curr_val >= next_val) correct_guess();
    else incorrect_guess();

    std::vector<Card> display_next { next };
    terminal::print_cards(display_next);
}

void handle_unkown() {
    std::cout << "Unkown input, enter (q) to quit\n";
}