#include <chrono>
#include <iostream>
#include <thread>
#include <set>
using namespace std;

void clearScreen()
{
    const int PATCH_LINES = 30;
    for (int i = 0; i < PATCH_LINES; i++)
        cout << endl;
}

const string FIGURE[] = {"   -------------    \n"
                         "   |                \n"
                         "   |                \n"
                         "   |                \n"
                         "   |                \n"
                         "   |     \n"
                         " -----   \n",
                         "   -------------    \n"
                         "   |           |    \n"
                         "   |                \n"
                         "   |                \n"
                         "   |                \n"
                         "   |     \n"
                         " -----   \n",
                         "   -------------    \n"
                         "   |           |    \n"
                         "   |           O    \n"
                         "   |                \n"
                         "   |                \n"
                         "   |     \n"
                         " -----   \n",
                         "   -------------    \n"
                         "   |           |    \n"
                         "   |           O    \n"
                         "   |           |    \n"
                         "   |                \n"
                         "   |     \n"
                         " -----   \n",
                         "   -------------    \n"
                         "   |           |    \n"
                         "   |           O    \n"
                         "   |          /|    \n"
                         "   |                \n"
                         "   |     \n"
                         " -----   \n",
                         "   -------------    \n"
                         "   |           |    \n"
                         "   |           O    \n"
                         "   |          /|\\  \n"
                         "   |                \n"
                         "   |     \n"
                         " -----   \n",
                         "   -------------    \n"
                         "   |           |    \n"
                         "   |           O    \n"
                         "   |          /|\\  \n"
                         "   |          /     \n"
                         "   |     \n"
                         " -----   \n",
                         "   -------------    \n"
                         "   |           |    \n"
                         "   |           O    \n"
                         "   |          /|\\  \n"
                         "   |          / \\  \n"
                         "   |     \n"
                         " -----   \n"};

void renderGame(const string &guessedWord, const string &badGuesses)
{
    clearScreen();
    int badGuessCount = badGuesses.length();
    cout << FIGURE[badGuessCount] << endl;
    cout << "Secret word: " << guessedWord << endl;
    if (badGuessCount > 0)
    {
        cout << "You've made " << badGuessCount << " wrong ";
        cout << (badGuessCount == 1 ? "guess" : "guesses");
        cout << ": " << badGuesses << endl;
    }
}

const string &getNextDancingMan()
{
    const static string figure[] = {
        "     O     \n"
        "    /|\\   \n"
        "    | |    \n",
        "     O     \n"
        "    /|\\   \n"
        "    / \\   \n",
        "   __O__   \n"
        "     |     \n"
        "    / \\   \n",
        "    \\O/   \n"
        "     |     \n"
        "    / \\   \n",
        "   __O__   \n"
        "     |     \n"
        "    / \\   \n",
        "     O     \n"
        "    /|\\   \n"
        "    / \\   \n",
        "    O      \n"
        "    /|\\   \n"
        "    / \\   \n",
        "     O     \n"
        "    /|\\   \n"
        "    / \\   \n",
        "      O    \n"
        "    /|\\   \n"
        "    / \\   \n",
        "     O     \n"
        "    /|\\   \n"
        "    / \\   \n",

    };

    const static int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

const string &getNextHangMan()
{
    const static string figure[] = {"   ------------+    \n"
                                    "   |    /           \n"
                                    "   |    O      \n"
                                    "   |   /|\\    \n"
                                    "   |   / \\    \n"
                                    "   |        \n"
                                    " -----      \n",
                                    "   ------------+     \n"
                                    "   |     |           \n"
                                    "   |     O           \n"
                                    "   |    /|\\         \n"
                                    "   |    / \\         \n"
                                    "   |        \n"
                                    " -----      \n",
                                    "   ------------+     \n"
                                    "   |      \\         \n"
                                    "   |      O          \n"
                                    "   |     /|\\        \n"
                                    "   |     / \\        \n"
                                    "   |      \n"
                                    " -----    \n",
                                    "   ------------+     \n"
                                    "   |     |           \n"
                                    "   |     O           \n"
                                    "   |    /|\\         \n"
                                    "   |    / \\         \n"
                                    "   |        \n"
                                    " -----      \n"};
    const static int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

void displayFinalResult(bool won, const string &word)
{
    int delay = 0;
    while (delay++ < 10)
    {
        clearScreen();
        if (won)
            cout << "Congratulations! You win! The word is " << word << endl;
        else
            cout << "You lost. The correct word is " << word << endl;
        cout << (won ? getNextDancingMan() : getNextHangMan());
        this_thread::sleep_for(chrono::milliseconds(400));
    }
}
string getDrawing(int incorrectGuess)
{
    static const string figure[] = {
        "   -------------    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |           |    \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|    \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |          /     \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |          / \\  \n"
        "   |     \n"
        " -----   \n",
    };

    const int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    return figure[incorrectGuess % NUMBER_OF_FIGURES];
}

string getNextHangman()
{
    static string figure[] = {
        "   ------------+    \n"
        "   |          /     \n"
        "   |         O      \n"
        "   |        /|\\    \n"
        "   |        / \\    \n"
        "   |        \n"
        " -----      \n",
        "   ------------+     \n"
        "   |           |     \n"
        "   |           O     \n"
        "   |          /|\\   \n"
        "   |          / \\   \n"
        "   |        \n"
        " -----      \n",
        "   ------------+      \n"
        "   |            \\    \n"
        "   |            O     \n"
        "   |           /|\\   \n"
        "   |           / \\   \n"
        "   |      \n"
        " -----    \n",
        "   ------------+     \n"
        "   |           |     \n"
        "   |           O     \n"
        "   |          /|\\   \n"
        "   |          / \\   \n"
        "   |        \n"
        " -----      \n",
    };
    const int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

string getNextStandingman()
{
    static string figure[] = {
        "     O     \n"
        "    /|\\   \n"
        "    | |    \n",
        "     O     \n"
        "    /|\\   \n"
        "    / \\   \n",
        "   __O__   \n"
        "     |     \n"
        "    / \\   \n",
        "    \\O/   \n"
        "     |     \n"
        "    / \\   \n",
        "   __O__   \n"
        "     |     \n"
        "    / \\   \n",
        "     O     \n"
        "    /|\\   \n"
        "    / \\   \n",
        "    O     \n"
        "    /|\\   \n"
        "    / \\   \n",
        "     O     \n"
        "    /|\\   \n"
        "    / \\   \n",
        "      O     \n"
        "    /|\\   \n"
        "    / \\   \n",
        "     O     \n"
        "    /|\\   \n"
        "    / \\   \n",
    };
    const int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

void playAnimation(bool isLosing, const string &word)
{
    // clearScreen();
    int delay = 0;
    while (delay++ < 10)
    {
        if (isLosing)
            cout << endl << "I lost :(. My best word is: " << word << endl;
        else
            cout << endl << "Haha, I win :D. The word is: " << word << endl;
        cout << (isLosing ? getNextHangman() : getNextStandingman());
        this_thread::sleep_for(chrono::milliseconds(400));
        // clearScreen();
    }
}

void render(int incorrectGuess, set<char> previousGuesses, const string &secretWord)
{
    // clearScreen();
    cout << endl << "Incorrect guess = " << incorrectGuess << "   previous guesses = ";
    for (char c : previousGuesses)
        cout << c;
    cout << "   secretWord = " << secretWord << endl;
    cout << getDrawing(incorrectGuess) << endl;
}