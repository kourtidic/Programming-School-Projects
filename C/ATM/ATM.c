#include <stdio.h>
#include <unistd.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#define CLEAR_SCREEN "cls"
#else
#include <stdio.h>
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#endif

struct BankAccount {
    int accountNumber;
    double balance;
};

struct BankAccount account;

void initializeAccount(int accountNumber, double initialBalance) {
    account.accountNumber = accountNumber;
    account.balance = initialBalance;
}

void creditBalance(double amount) {
    account.balance += amount;
}

int debitBalance(double amount) {
    if (account.balance >= amount) {
        account.balance -= amount;
        return 1; // Successful debit
    }
    return 0; // Insufficient balance
}

void printTotalBalance() {
    printf("Total balance: %.2f\n", account.balance);
}

void clearScreen() {
    system(CLEAR_SCREEN);
}

void displayDateTime() {
    time_t t;
    struct tm* tm_info;

    time(&t);
    tm_info = localtime(&t);

    printf("Current Date and Time: %s", asctime(tm_info));
}

void displaySignature() {
    printf("\nMade By Vasileios Kourtidis\n");
}

int main() {
    int accountNumber;
    double initialBalance, amount;
    char continueOption;

    printf("Welcome to the Beautiful ATM!\n");

    printf("Enter a new account number: ");
    scanf("%d", &accountNumber);

    printf("Enter the initial balance: ");
    scanf("%lf", &initialBalance);

    initializeAccount(accountNumber, initialBalance);

    do {
        clearScreen(); // Call the clearScreen function before displaying the menu

        displayDateTime(); // Display the current date and time

        printf("\nMenu of options:\n");
        printf("1. Set initial balance\n");
        printf("2. Credit balance\n");
        printf("3. Debit balance\n");
        printf("4. See total balance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the new initial balance: ");
                scanf("%lf", &initialBalance);
                account.balance = initialBalance;
                printf("Initial balance set successfully!\n");
                break;
            case 2:
                printf("Enter the amount to deposit: ");
                scanf("%lf", &amount);
                creditBalance(amount);
                printf("Amount credited successfully!\n");
                break;
            case 3:
                printf("Enter the amount to withdraw: ");
                scanf("%lf", &amount);
                if (debitBalance(amount)) {
                    printf("Amount debited successfully!\n");
                } else {
                    printf("Insufficient balance!\n");
                }
                break;
            case 4:
                printTotalBalance();
                break;
            case 5:
                printf("Exiting...\n");
                sleep(1); // Delay for 1 second to simulate Ctrl+C effect
                break;
            default:
                printf("Invalid choice!\n");
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &continueOption);
    } while (continueOption == 'y');

    displaySignature(); // Display the signature at the end

    return 0;
}

