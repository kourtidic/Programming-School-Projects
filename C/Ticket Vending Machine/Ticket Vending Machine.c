#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // For sleep function

// Define ticket types and prices
float REGULAR_TICKET_PRICE = 1; // Changed to float for flexibility
float STUDENT_TICKET_PRICE = 0.5; // Changed to float for flexibility

// Define initial ticket stock
int regular_tickets_stock = 100;
int student_tickets_stock = 50;

// Define admin credentials
const char *ADMIN_USERNAME = "admin";
const char *ADMIN_PASSWORD = "admin260200";

// Define bus routes and departure times
#define MAX_ROUTES 3
char bus_routes[MAX_ROUTES][50] = {"City Center", "Airport", "Train Station"};
int bus_departure_times[MAX_ROUTES] = {0, 15, 30}; // Departure times in minutes past the hour

// Function prototypes
void displayMenu();
void issueTicket();
void serviceMode();
bool authenticateAdmin(const char *username, const char *password);
void busInformation();
void dateTimeInformation();
void cashierInformation();
void ticketSleeveInformation();
void changeBusRoutes();
void changeDepartureTimes();
void changeTicketPrices();
void changeTicketStock();
void clearScreen(); // Function to clear the screen
void showCurrentTime(); // Function to display current time
void printTicketForNextBus(); // Function to print a ticket for the next bus

int main() {
    printf("Welcome to the Ticket Vending Machine by Vasileios Kourtidis\n");
    showCurrentTime(); // Show current time when the program starts

    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                issueTicket();
                break;
            case 2:
                serviceMode();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

void displayMenu() {
    printf("\nTicket Vending Machine\n");
    printf("1. Issue Ticket\n");
    printf("2. Service Mode\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

void issueTicket() {
    int ticket_type, quantity, route_choice;
    printf("\nSelect Ticket Type:\n");
    printf("1. Regular Ticket (%.2f euros)\n", REGULAR_TICKET_PRICE);
    printf("2. Student Ticket (%.2f euros)\n", STUDENT_TICKET_PRICE);
    printf("Enter ticket type: ");
    scanf("%d", &ticket_type);

    printf("Select Bus Route:\n");
    int i;
    for (i = 0; i < MAX_ROUTES; ++i) {
        printf("%d. %s\n", i + 1, bus_routes[i]);
    }
    printf("Enter route choice: ");
    scanf("%d", &route_choice);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    float total_price = (ticket_type == 1) ? REGULAR_TICKET_PRICE * quantity : STUDENT_TICKET_PRICE * quantity;

    if (ticket_type == 1 && regular_tickets_stock < quantity) {
        printf("Insufficient stock for regular tickets. Available: %d\n", regular_tickets_stock);
    } else if (ticket_type == 2 && student_tickets_stock < quantity) {
        printf("Insufficient stock for student tickets. Available: %d\n", student_tickets_stock);
    } else {
        printf("Insert payment (%.2f euros): ", total_price);
        float payment;
        scanf("%f", &payment);

        if (payment < total_price) {
            printf("Insufficient payment. Please insert more money.\n");
        } else {
            float change = payment - total_price;
            if (change >= 0) {
                if (change > 0)
                    printf("Change: %.2f euros\n", change);
                
                // Update ticket stock
                if (ticket_type == 1)
                    regular_tickets_stock -= quantity;
                else
                    student_tickets_stock -= quantity;

                // Display date and time
                time_t now;
                struct tm *local_time;
                time(&now);
                local_time = localtime(&now);
                printf("Ticket(s) issued successfully at %s", asctime(local_time));

                // Print ticket for the next bus departure
                printTicketForNextBus();

                // Delay for 3 seconds
                sleep(3);

                // Clear screen
                clearScreen();

                // Show welcome message again
                printf("Welcome to the Ticket Vending Machine by Vasileios Kourtidis\n");
                showCurrentTime();
            } else {
                printf("Unable to make change. Please use exact change.\n");
            }
        }
    }
}

void serviceMode() {
    char username[20], password[20];
    printf("\nEnter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticateAdmin(username, password)) {
        int choice;
        do {
            clearScreen(); // Clear the screen before displaying the service mode menu
            printf("\nService Mode\n");
            printf("1. Bus Information (Display, Correct, Insert)\n");
            printf("2. Departure Times Information (Display, Correct, Insert)\n");
            printf("3. Ticket Prices Information (Display, Correct, Insert)\n");
            printf("4. Ticket Stock Information (Display, Correct, Insert)\n");
            printf("5. Exit Service Mode\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    changeBusRoutes();
                    break;
                case 2:
                    changeDepartureTimes();
                    break;
                case 3:
                    changeTicketPrices();
                    break;
                case 4:
                    changeTicketStock();
                    break;
                case 5:
                    printf("Exiting Service Mode...\n");
                    // Delay for 2 seconds
                    sleep(2);
                    // Clear screen
                    clearScreen();
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } while (choice != 5);
    } else {
        printf("Authentication failed. Access denied.\n");
    }
}

bool authenticateAdmin(const char *username, const char *password) {
    return strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0;
}

void changeBusRoutes() {
    int route_number;
    printf("\nCurrent Bus Routes:\n");
    int i = 0;
    while (i < MAX_ROUTES) {
        printf("%d. %s\n", i + 1, bus_routes[i]);
        i++;
    }
    printf("Enter the route number to change: ");
    scanf("%d", &route_number);
    if (route_number >= 1 && route_number <= MAX_ROUTES) {
        printf("Enter the new name for the route: ");
        scanf("%s", bus_routes[route_number - 1]);
        printf("Route name changed successfully.\n");
    } else {
        printf("Invalid route number.\n");
    }
}

void changeDepartureTimes() {
    int route_number;
    printf("\nCurrent Departure Times:\n");
    int i = 0;
    while (i < MAX_ROUTES) {
        printf("%d. %s: %d minutes past the hour\n", i + 1, bus_routes[i], bus_departure_times[i]);
        i++;
    }
    printf("Enter the route number to change departure time: ");
    scanf("%d", &route_number);
    if (route_number >= 1 && route_number <= MAX_ROUTES) {
        printf("Enter the new departure time (minutes past the hour): ");
        scanf("%d", &bus_departure_times[route_number - 1]);
        printf("Departure time changed successfully.\n");
    } else {
        printf("Invalid route number.\n");
    }
}

void changeTicketPrices() {
    printf("\nCurrent Ticket Prices:\n");
    printf("Regular Ticket Price: %.2f euros\n", REGULAR_TICKET_PRICE);
    printf("Student Ticket Price: %.2f euros\n", STUDENT_TICKET_PRICE);
    printf("Enter the new price for regular tickets: ");
    scanf("%f", &REGULAR_TICKET_PRICE);
    printf("Enter the new price for student tickets: ");
    scanf("%f", &STUDENT_TICKET_PRICE);
    printf("Ticket prices changed successfully.\n");
}

void changeTicketStock() {
    printf("\nCurrent Ticket Stock:\n");
    printf("Regular Tickets Stock: %d\n", regular_tickets_stock);
    printf("Student Tickets Stock: %d\n", student_tickets_stock);
    printf("Enter the new stock for regular tickets: ");
    scanf("%d", &regular_tickets_stock);
    printf("Enter the new stock for student tickets: ");
    scanf("%d", &student_tickets_stock);
    printf("Ticket stock changed successfully.\n");
}

void clearScreen() {
    // Clear screen function for Windows and UNIX-like systems
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showCurrentTime() {
    // Display current time when the program starts
    time_t now;
    struct tm *local_time;
    time(&now);
    local_time = localtime(&now);
    printf("Current time: %s\n", asctime(local_time));
}

void printTicketForNextBus() {
    time_t now;
    struct tm *local_time;
    time(&now);
    local_time = localtime(&now);

    int current_hour = local_time->tm_hour;
    int current_minute = local_time->tm_min;

    // Calculate the time for the next bus (every 15 minutes)
    int next_bus_hour = current_hour;
    int next_bus_minute = (current_minute < 45) ? ((current_minute / 15 + 1) * 15) % 60 : 0;

    // If the next bus minute is 0, increment the hour
    if (next_bus_minute == 0) {
        next_bus_hour = (next_bus_hour + 1) % 24;
    }

    // Print the ticket for the next bus
    printf("\nNext Bus Departure: %02d:%02d\n", next_bus_hour, next_bus_minute);
    printf("Ticket issued successfully for the next bus at %02d:%02d\n", next_bus_hour, next_bus_minute);
}

