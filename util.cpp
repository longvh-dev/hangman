#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

int generateRandomNumber(int min, int max) {
    return arc4random() % (max - min) + min;
}

bool isCharInWord(char ch, string word) {
    return (word.find_first_of(ch) != string::npos);
}

vector<string> readWordListFromFile(const string &filePath) {
    vector<string> wordList;
    string word;
    ifstream wordFile(filePath);
    if (wordFile.is_open()) {
        while (wordFile >> word) {
            wordList.push_back(word);
        }
        wordFile.close();
        return wordList;
    } else {
        throw domain_error("Error: Unable to open vocabulary file " + filePath);
    }
}

bool isAllDash(const string &s) {
    for (char c: s)
        if (c != '-')
            return false;
    return true;
}

bool isAllNotDash(const string &s) {
    for (char c: s)
        if (c == '-')
            return false;
    return true;
}
