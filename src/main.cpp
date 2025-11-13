
#include "terminal.h"
#include "deck.h"
#include <sstream>
#include <thread>
#include <chrono>

static bool stop_game { false };
static int score;
static int streak;

void handle_guess(const Card& curr, const Card& next, bool higher);
void handle_unkown();

int main() {
    using namespace std::chrono_literals;

    Deck deck{ 10 };
    Card mystery_card {"?", Card::suit::UNKOWN};

    std::string input;

    while(!stop_game) {
        terminal::clear_screen();
        terminal::print_score(score);

        auto& current_card = deck.get_next_card();

        std::vector<Card> display_cards { 
            current_card, mystery_card };

        terminal::print_cards(display_cards);
        std::cout << "Higer or lower? (h/l): ";

        std::getline(std::cin, input);
        
        terminal::clear_screen();
        auto& next_card { deck.check_next_card() };

        if(input == "q") {
            stop_game = true;
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
    ++streak;
    if(streak >= 2) {
        std::string streak_str = std::to_string(streak) + "x Streak!\n";
        terminal::print_yellow(streak_str);
        score += 2 * streak;
        std::string score_add_str = "+" + 
            std::to_string(2 * streak) + " Correct!\n"; 
        terminal::print_green(score_add_str);
    } else {
        score += 2;
        terminal::print_green("+2 Correct!\n");
    }
}

void incorrect_guess() {
    terminal::print_red("-2 Wrong...\n");
    streak = 0;
    score -= 2;
    score = std::max(score, 0);
}

void handle_guess
    (const Card& curr, const Card& next, bool higher) {
    auto curr_val = curr.get_value_int();
    auto next_val = next.get_value_int();
    // invalid card in the deck
    if(curr_val == -1 || next_val == -1) {
        stop_game = true;
        return;
    }

    if(higher && curr_val < next_val) correct_guess();
    else if(!higher && curr_val > next_val) correct_guess();
    else incorrect_guess();

    std::vector<Card> display_next { next };
    terminal::print_cards(display_next);
}

void handle_unkown() {
    std::cout << "Unkown input, enter (q) to quit\n";
}