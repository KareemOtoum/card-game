#include "game_state.h"

int GameState::score_ {};
int GameState::streak_ {};
bool GameState::in_play_ { true };

void GameState::correct_guess() {
    ++streak_;
    score_ += correct_guess_pts * streak_;
}

void GameState::incorrect_guess() {
    streak_ = 0;
    score_ += incorrect_guess_pts;
    score_ = std::max(score_, 0);
}
