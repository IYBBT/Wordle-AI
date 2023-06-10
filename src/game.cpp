
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <fstream>
#include <iostream>

struct Wordle {

    Wordle() {
        std::ifstream file("./assets/dict.txt");
        while (!file.eof()) {
            file >> word;
            dictionary.push_back(word);
        } file.close();

        file.open("./assets/words.txt");
        while (!file.eof()) {
            file >> word;
            words.push_back(word);
        } file.close();

        srand(time(NULL));
    }

    int* evaluate(std::string guess, std::map<char, int> chars) {
        int* info = new int[5];
        for (int i = 0; i < 5; ++i)
            info[i] = 0;

        for (int i = 0; i < guess.length(); ++i)
            if (guess[i] == word[i])
                info[i] = 2;
            else if (std::find(word.begin(), word.end(), guess[i]) != word.end())
                info[i] = 1;

        std::map<char, int> guessChars;
        std::deque<int> indices = { 0, 1, 2, 3, 4 };
        for (int i = 0; i < 5; ++i) {
            int f = indices.front();
            indices.pop_front();
            if (info[f] == 2)
                guessChars[guess[f]] = guessChars[guess[f]] + 1;
            else if (info[f] == 1)
                indices.push_back(f);
        }
        
        while (indices.size()) {
            int f = indices.front();
            indices.pop_front();
            if (guessChars[guess[f]] < chars[guess[f]])
                info[f] = 1;
            else
                info[f] = 0;
            guessChars[guess[f]] = guessChars[guess[f]] + 1;
        }

        return info;
    }

    void play() {
        word = words[rand() % words.size()];
        std::map<char, int> chars;
        for (int i = 0; i < word.length(); ++i)
            chars[word[i]] = chars[word[i]] + 1;
        std::cout << word << std::endl;

        std::string guess = "";
        int guesses = 0;
        while (guess != word && guesses < 6) {
            bool valid = false;
            do {
                std::cout << "Guess " << guesses+1 << ": Guess a word:\t";
                std::cin >> guess;
                for (int i = 0; i < guess.length(); i++)
                    guess[i] = tolower(guess[i]);
                valid = std::find(dictionary.begin(), dictionary.end(), guess) != dictionary.end();
                if (!valid)
                    std::cout << "Invalid guess! Try again.\n";
            } while (!valid);

            int* info = evaluate(guess, chars);
            std::cout << "\t\t\t";
            for (int i = 0; i < 5; ++i)
                std::cout << info[i];
            std::cout << '\n';
            guesses++;
        }

        if (guess == word)
            std::cout << "You win!" << std::endl;
        else
            std::cout << "You lose!" << std::endl;
    }

private:
    std::vector<std::string> words;
    std::vector<std::string> dictionary;

    std::string word;
};
