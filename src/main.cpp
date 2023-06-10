
#include <iostream>

#include "game.cpp"
#include "wordle_ai.cpp"

int main() {
    std::cout << "Welcome to Wordle!" << std::endl;
    Wordle_Ai ai;
    double wins = 0;
    for (int i = 0; i < 100000; ++i) {
        ai.reset();
        std::pair<bool, int> p = ai.play();
        std::cout << (p.first ? "Win\t\t" : "Loss\t") << p.second << " Words Left" << std::endl;
        wins += p.first * 1;
    }

    std::cout << "Win Rate: " << wins / 1000 << std::endl;
    return 0;
}
