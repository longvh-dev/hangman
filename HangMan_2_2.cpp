#include "draw.h"
#include "guesser.h"
#include "util.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
const int MAX_GUESSES = 7;
const int MAX_BAD_GUESSES = 7;
string DATA_FILE;
int mode = 0;
const int gameMode[] = {0, 1, 2};

string chooseWord(const string &fileName);

char readAGuess();
bool contains(const string &word, char guess);
void updateGuessedWord(string &guessedWord, const string &word, char guess);
void playAgain();
void chooseGameMode();
void chooseTopic();
int getUserWordLength();
void initialize(int &wordLength, string &secretWord, int &incorrectGuess, set<char> &previousGuesses, bool &stop);
string getUserAnswer(char guess);
bool isGoodMask(char guess, const string &mask, const string &secretWord);
void updateSecretWord(const string &mask, string &secretWord);
void update(char guess, const string &mask, int &incorrectGuess, set<char> &previousGuesses, string &secretWord,
            bool &stop);


namespace A
{
    int times = 0;
}
int main()
{
tryAgain:
    srand(static_cast<unsigned int>(time(nullptr)));

    chooseGameMode();

    // AI guess
    if (mode == gameMode[1])
    {
        int wordLength;
        string secretWord;
        int incorrectGuess;
        set<char> previousGuesses;
        bool stop;

        initialize(wordLength, secretWord, incorrectGuess, previousGuesses, stop);

        render(incorrectGuess, previousGuesses, secretWord);
        do
        {
            char guess = getNextGuess(previousGuesses, secretWord);
            if (guess == 0)
            {
                cout << "I give up, hang me" << endl;
                return 0;
            }

            do
            {
                try
                {
                    string mask = getUserAnswer(guess);
                    update(guess, mask, incorrectGuess, previousGuesses, secretWord, stop);
                    break;
                }
                catch (invalid_argument e)
                {
                    cout << "Invalid mask, try again" << endl;
                }
            } while (true);
            render(incorrectGuess, previousGuesses, secretWord);
        } while (!stop);
        playAnimation(incorrectGuess == MAX_GUESSES, secretWord);
    }

    // human guess
    if (mode == gameMode[2])
    {
        string word = chooseWord(DATA_FILE);
        if (word.length() < 1)
        {
            cout << "Error reading vocabulary file " << DATA_FILE;
            return -1;
        }
        string guessedWord = string(word.length(), '-');
        string badGuesses = "";

        do
        {
            renderGame(guessedWord, badGuesses);
            char guess = readAGuess();
            if (contains(word, guess))
                updateGuessedWord(guessedWord, word, guess);
            else
            {
                badGuesses += guess;
            }
        } while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord);
        displayFinalResult(badGuesses.length() < MAX_BAD_GUESSES, word);
    }
    // play again
    cout << "Do you want to play again? (y/n)" << endl;
    char c;
    cin >> c;
    if (c == 'y')
        goto tryAgain;
    return 0;
}

string getLowerCaseString(const string &s)
{
    string res = s;
    transform(s.begin(), s.end(), res.begin(), ::tolower);
    return res;
}

string chooseWord(const string &fileName)
{
    vector<string> wordList;
    ifstream file(fileName);
    if (file.is_open())
    {
        string word;
        while (file >> word)
        {
            wordList.push_back(word);
        }
        file.close();
    }
    if (wordList.size() > 0)
    {
        int randomIndex = arc4random() % wordList.size();
        return getLowerCaseString(wordList[randomIndex]);
    }
    else
        return "";
}

char readAGuess()
{
    char input;
    cout << "Your guess: ";
    cin >> input;
    return tolower(input);
}

bool contains(const string &word, char c)
{
    return (word.find_first_of(c) != string::npos);
}

void updateGuessedWord(string &guessedWord, const string &word, char guess)
{
    for (int64_t i = word.length() - 1; i >= 0; i--)
    {
        if (word[i] == guess)
        {
            guessedWord[i] = guess;
        }
    }
}

void chooseGameMode()
{
    do
    {
        clearScreen();
        cout << endl << "=====Menu=====" << endl << "Choose game mode: " << endl;
        cout << "1. AI guess" << endl;
        cout << "2. Human guess" << endl;
        cin >> mode;
        cout << "---------------" << endl;
        if (mode == gameMode[1])
        {
//            DATA_FILE = "data/All.txt";
        }
        else if (mode == gameMode[2])
        {
            chooseTopic();
        }
        else
        {
            cout << "Please choose again" << endl;
        }
    } while (mode != gameMode[1] && mode != gameMode[2]);
}

void chooseTopic()
{
    cout << "Choose topic: " << endl;
    cout << "1. Plants" << endl;
    cout << "2. Animals" << endl;
    cout << "3. Fruits" << endl;
    cout << "4. All" << endl;
    //    DATA_FILE = "data/Plants.txt";
    int n;
    cin >> n;
    cout << "You choose: ";
    switch (n)
    {
    case 1:
        DATA_FILE = "data/Plants.txt";
        break;
    case 2:
        DATA_FILE = "data/Animals.txt";
        break;
    case 3:
        DATA_FILE = "data/Fruits.txt";
        break;
    case 4:
        DATA_FILE = "data/All.txt";
        break;
    default:
        cout << "Error topic";
        break;
    }
}

int getUserWordLength()
{
    int wordLength;
    cout << endl << "Enter your word length: ";
    cin >> wordLength;
    return wordLength;
}

void initialize(int &wordLength, string &secretWord, int &incorrectGuess, set<char> &previousGuesses, bool &stop)
{
    wordLength = getUserWordLength();
    secretWord = string(wordLength, '-');
    incorrectGuess = 0;
    previousGuesses = set<char>();
    stop = false;
}

string getUserAnswer(char guess)
{
    string answer;
    cout << endl << "I guess " << guess << ", please enter your mask: ";
    cin >> answer;
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    return answer;
}

bool isGoodMask(char guess, const string &mask, const string &secretWord)
{
    if (mask.length() != secretWord.length())
        return false;
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-')
        {
            if (mask[i] != guess)
                return false;
            if (secretWord[i] != '-' && secretWord[i] != mask[i])
                return false;
        }
    return true;
}

void updateSecretWord(const string &mask, string &secretWord)
{
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-')
            secretWord[i] = mask[i];
}

void update(char guess, const string &mask, int &incorrectGuess, set<char> &previousGuesses, string &secretWord,
            bool &stop)
{
    if (!isGoodMask(guess, mask, secretWord))
        throw invalid_argument("mistake entering answer");

    previousGuesses.insert(guess);
    if (isAllDash(mask))
    {
        incorrectGuess++;
        if (incorrectGuess == MAX_GUESSES)
            stop = true;
    }
    else
    {
        updateSecretWord(mask, secretWord);
        if (isAllNotDash(secretWord))
            stop = true;
    }
}