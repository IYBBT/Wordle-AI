
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <fstream>
#include <iostream>

struct Wordle_Ai {

    Wordle_Ai() {
        reset();
    }

    void reset() {
        dictionary.clear();
        words.clear();

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

    void eliminate(std::string guess, int* info) {
        std::map<char, int> chars;
        std::deque<int> indices;
        for (int i = 0; i < guess.size(); ++i)
            for (int f = 0; f < dictionary.size(); ++f)
                if (info[i] == 2 && guess[i] == dictionary[f][i]) chars[guess[i]] = chars[guess[i]] + 1;
                else if (info[i] == 1 && guess[i] != dictionary[f][i] && std::find(dictionary[f].begin(), dictionary[f].end(), guess[i]) != dictionary[f].end()) chars[guess[i]] = chars[guess[i]] + 1;
                else if (!info[i]) indices.push_back(i);
                else dictionary.erase(dictionary.begin() + f--);

        while (indices.size()) {
            int i = indices.front();
            indices.pop_front();
            for (int f = 0; f < dictionary.size(); ++f)
                if (chars[guess[i]] || std::find(dictionary[f].begin(), dictionary[f].end(), guess[i]) == dictionary[f].end());
                else dictionary.erase(dictionary.begin() + f--);
        }
    }

    std::pair<bool, int> play() {
        word = words[rand() % words.size()];
        std::map<char, int> chars;
        for (int i = 0; i < word.length(); ++i)
            chars[word[i]] = chars[word[i]] + 1;

        std::string guess = "";
        int guesses = 0;
        while (guess != word && guesses < 6) {
            guess = dictionary[rand() % dictionary.size()];
            int* info = evaluate(guess, chars);
            eliminate(guess, info);
            guesses++;
        }

        if (guess == word)
            return { true, dictionary.size() };
        else
            return { false, dictionary.size() };
    }

private:
    std::vector<std::string> words;
    std::vector<std::string> dictionary;

    std::string word;
};
