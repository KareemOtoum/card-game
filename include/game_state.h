#pragma once

#include <iostream>

class GameState {
public:
    static void    correct_guess();
    static void    incorrect_guess();
    
    static int     get_score() { return score_; }
    static int     get_streak() { return streak_; }

    static bool in_play_;

    static inline constexpr int correct_guess_pts { 2 };
    static inline constexpr int incorrect_guess_pts { -2 };
private:
    static int score_;
    static int streak_;

    GameState() = delete;
};