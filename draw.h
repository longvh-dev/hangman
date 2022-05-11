#pragma once
#include <iostream>
#include <set>
// #include <string>

using namespace std;

void renderGame(const string &guessedWord, const string &badGuesses);
void displayFinalResult(bool won, const string &word);
void playAnimation(bool isLosing, const string &word);
void render(int incorrectGuess, std::__1::set<char> previousGuesses, const string &secretWord);

std::string getDrawing(int incorrectGuess);
std::string getNextHangman();
std::string getNextStandingman();
void clearScreen();
