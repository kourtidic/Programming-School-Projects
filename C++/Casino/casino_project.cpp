#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
#ifdef _WIN32
    #include <windows.h> // For Windows
#else
    #include <unistd.h> // For Linux/MacOS
#endif

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to print colorful casino welcome banner
void printBanner() {
    cout << "\033[1;32m" << R"(
===========$ WELCOME TO CASINO WORLD $==========
============= BY VASILHS KOURTIDHS =============
)" << "\033[0m";
}

void waitForSeconds(int seconds) {
    #ifdef _WIN32
        Sleep(seconds * 1000);
    #else
        usleep(seconds * 1000000);
    #endif
}

int main() {
    string playerName;
    int balance = 0;
    int betAmount;
    int guess;
    int winningNumber;
    char playAgain;
    char addBalance;
    bool firstTime = true;

    // Display welcome banner
    clearScreen();
    printBanner();

    // Welcome and get player's name
    cout << "\033[1;33mWelcome to the Lucky Draw Game!\033[0m" << endl;
    cout << "Please enter your name: ";
    getline(cin, playerName);
    cout << "\nHello, \033[1;36m" << playerName << "\033[0m!" << endl;

    // Get initial balance
    while (true) {
        cout << "\nPlease enter the amount to enter the game: $";
        cin >> balance;
        if (cin.fail() || balance <= 0) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            cout << "\033[1;31mInvalid input. Please enter a positive number.\033[0m" << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            break;
        }
    }

    do {
        if (firstTime) {
            // Display rules
            cout << "\n\033[1;34mRules of the game:\033[0m" << endl;
            cout << "1. Guess a number between 1 and 10." << endl;
            cout << "2. If you guess correctly, your bet amount will be credited to your account." << endl;
            cout << "3. If you do not guess correctly, your bet amount will be deducted from your account." << endl;

            // Wait for 5 seconds
            cout << "\nGame will start in: ";
            for (int i = 5; i > 0; i--) {
                cout << "\033[1;31m" << i << "\033[0m seconds";
                cout.flush();
                waitForSeconds(1);
                cout << "\r\033[K"; // Clear the line
            }
            cout << endl;

            firstTime = false;
        }

        // Clear screen
        clearScreen();
        printBanner();

        // Check if balance is 0
        if (balance == 0) {
            cout << "You do not have enough balance. Do you want to add more balance? (y/n): ";
            cin >> addBalance;
            if (addBalance == 'y' || addBalance == 'Y') {
                while (true) {
                    cout << "Enter the amount to add to your balance: $";
                    cin >> balance;
                    if (cin.fail() || balance <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\033[1;31mInvalid input. Please enter a positive number.\033[0m" << endl;
                    } else {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                }
            } else {
                cout << "\n\033[1;32mThanks for playing, " << playerName << "!\033[0m" << endl;
                cout << "Your final balance is: \033[1;33m$" << balance << "\033[0m" << endl;
                return 0;
            }
        }

        // Get bet amount
        while (true) {
            cout << "\nEnter your bet amount: $";
            cin >> betAmount;
            if (cin.fail() || betAmount <= 0 || betAmount > balance) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\033[1;31mInvalid bet amount. Please enter a positive number that is less than or equal to your balance.\033[0m" << endl;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        // Generate winning number
        srand(time(0));
        winningNumber = rand() % 10 + 1;

        // Get player's guess
        cout << "\nGuess a number between 1 and 10: ";
        cin >> guess;

        // Check if player's guess is correct
        if (guess == winningNumber) {
            cout << "\n\033[1;32mCongratulations! You guessed correctly.\033[0m" << endl;
            balance += betAmount;
            cout << "Your new balance is: \033[1;33m$" << balance << "\033[0m" << endl;
        } else {
            cout << "\n\033[1;31mSorry, you did not guess correctly.\033[0m The winning number was \033[1;33m" << winningNumber << "\033[0m." << endl;
            balance -= betAmount;
            cout << "Your new balance is: \033[1;33m$" << balance << "\033[0m" << endl;
        }

        // Ask if player wants to continue
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\n\033[1;32mThanks for playing, " << playerName << "!\033[0m" << endl;
    cout << "Your final balance is: \033[1;33m$" << balance << "\033[0m" << endl;

    return 0;
}
