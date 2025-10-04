#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to determine the winner of a round
int determineWinner(char choice1[], char choice2[]) {
    if (strcmp(choice1, choice2) == 0) {
        // Tie
        return 0;
    } else if ((strcmp(choice1, "ROCK") == 0 && strcmp(choice2, "SCISSORS") == 0) ||
               (strcmp(choice1, "SCISSORS") == 0 && strcmp(choice2, "PAPER") == 0) ||
               (strcmp(choice1, "PAPER") == 0 && strcmp(choice2, "ROCK") == 0)) {
        // Player 1 wins
        return 1;
    } else {
        // Player 2 wins
        return 2;
    }
}

// Function to generate computer's choice
char* generateComputerChoice() {
    srand(time(NULL)); // Seed the random number generator
    int randomNum = rand() % 3; // Generate a random number between 0 and 2
    char* choices[] = {"ROCK", "PAPER", "SCISSORS"};
    return choices[randomNum];
}

int main() {
    printf("Welcome To The Rock Paper Scissors Game by Vasileios Kourtidis!!!\n\n");

    int playAgain = 1;
    while (playAgain) {
        int rounds;
        printf("How many rounds do you want to play? ");
        scanf("%d", &rounds);

        int gameMode;
        printf("\nSelect Game Mode:\n");
        printf("1. Player vs Player\n");
        printf("2. Player vs Computer\n");
        printf("Enter your choice: ");
        scanf("%d", &gameMode);

        if (gameMode != 1 && gameMode != 2) {
            printf("Invalid game mode selected. Exiting...\n");
            return 1;
        }

        char player1[20], player2[20];
        char choice1[10], choice2[10];
        int round, scorePlayer1 = 0, scorePlayer2 = 0;

        if (gameMode == 1) {
            // Input player names
            printf("\nEnter name for Player 1: ");
            scanf("%s", player1);
            printf("Enter name for Player 2: ");
            scanf("%s", player2);
        } else {
            // Input player name
            printf("\nEnter your name: ");
            scanf("%s", player1);
            strcpy(player2, "Computer");
        }

        // Play rounds
        for (round = 1; round <= rounds; round++) {
            // Display round number
            printf("\nROUND %d\n", round);

            // Input choices for players
            printf("%s, enter your choice (ROCK, PAPER, SCISSORS, END): ", player1);
            scanf("%s", choice1);

            // Validity check for player1's choice
            if (strcmp(choice1, "END") == 0) {
                break;
            } else if (!(strcmp(choice1, "ROCK") == 0 || strcmp(choice1, "PAPER") == 0 || strcmp(choice1, "SCISSORS") == 0)) {
                printf("Invalid choice. Please enter ROCK, PAPER, SCISSORS, or END.\n");
                round--;
                continue;
            }

            if (gameMode == 1) {
                printf("%s, enter your choice (ROCK, PAPER, SCISSORS, END): ", player2);
                scanf("%s", choice2);

                // Validity check for player2's choice
                if (strcmp(choice2, "END") == 0) {
                    break;
                } else if (!(strcmp(choice2, "ROCK") == 0 || strcmp(choice2, "PAPER") == 0 || strcmp(choice2, "SCISSORS") == 0)) {
                    printf("Invalid choice. Please enter ROCK, PAPER, SCISSORS, or END.\n");
                    round--;
                    continue;
                }
            } else {
                strcpy(choice2, generateComputerChoice());
                printf("Computer chose: %s\n", choice2);
            }

            // Determine the winner of the round
            int winner = determineWinner(choice1, choice2);

            // Display the result of the round
            if (winner == 0) {
                printf("It's a tie!\n");
            } else if (winner == 1) {
                printf("%s wins!\n", player1);
                scorePlayer1++;
            } else {
                if (gameMode == 1)
                    printf("%s wins!\n", player2);
                else
                    printf("Computer wins!\n");
                scorePlayer2++;
            }
        }

        // Display the final result
        printf("\nFINAL SCORE:\n%s: %d\n%s: %d\n", player1, scorePlayer1, player2, scorePlayer2);

        // Determine the overall winner or if it's a tie
        if (scorePlayer1 > scorePlayer2) {
            printf("%s wins the game!\n", player1);
        } else if (scorePlayer2 > scorePlayer1) {
            if (gameMode == 1)
                printf("%s wins the game!\n", player2);
            else
                printf("Computer wins the game!\n");
        } else {
            printf("It's a tie!\n");
        }

        // Ask if the user wants to play again
        printf("\nDo you want to play again? (1 for Yes, 0 for No): ");
        scanf("%d", &playAgain);

        // Clear the screen
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    return 0;
}

