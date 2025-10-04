#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Room {
    int number;
    string customerName;
    string address;
    string phoneNumber;
    string roomType;
    int numberOfPeople;
    bool isAvailable;
};

vector<Room> rooms;

void displayMenu() {
    system("cls"); // clear the screen
    cout << "Hotel Management System" << endl;
    cout << "-----------------------" << endl;
    cout << "1. Room Management" << endl;
    cout << "2. Check-in" << endl;
    cout << "3. Room Availability" << endl;
    cout << "4. Customer Search" << endl;
    cout << "5. Check-out" << endl;
    cout << "6. Hotel Guest Report" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}

void roomManagement() {
    system("cls"); // clear the screen
    int num;
    cout << "Room Management" << endl;
    cout << "----------------" << endl;
    cout << "Enter the number of rooms to add: ";
    cin >> num;
    
    int startingRoomNumber = rooms.empty() ? 1 : rooms.back().number + 1;

    for (int i = 0; i < num; i++) {
        Room room;
        room.number = startingRoomNumber + i;
        room.isAvailable = true;
        rooms.push_back(room);
    }

    cout << "Rooms added successfully!" << endl;
    system("pause"); // wait for user input
}

void checkIn() {
    system("cls"); // clear the screen
    int roomNumber;
    string customerName, address, phoneNumber, roomType;
    int numberOfPeople;
    
    cout << "Check-in" << endl;
    cout << "---------" << endl;
    cout << "Enter room number: ";
    cin >> roomNumber;

    cout << "Enter customer name: ";
    cin >> customerName;
    
    cout << "Enter address: ";
    cin.ignore(); // clear input buffer
    getline(cin, address);

    cout << "Enter phone number: ";
    getline(cin, phoneNumber);

    cout << "Enter room type (standard/premium): ";
    cin >> roomType;
    
    cout << "Enter number of people: ";
    cin >> numberOfPeople;

    for (Room &room : rooms) {
        if (room.number == roomNumber && room.isAvailable) {
            room.customerName = customerName;
            room.address = address;
            room.phoneNumber = phoneNumber;
            room.roomType = roomType;
            room.numberOfPeople = numberOfPeople;
            room.isAvailable = false;
            cout << "Check-in successful!" << endl;
            system("pause"); // wait for user input
            return;
        }
    }
    cout << "Room not available!" << endl;
    system("pause"); // wait for user input
}

void roomAvailability() {
    system("cls"); // clear the screen
    cout << "Room Availability" << endl;
    cout << "-----------------" << endl;
    if (rooms.empty()) {
        cout << "No rooms available." << endl;
    } else {
        for (const Room &room : rooms) {
            cout << "Room " << room.number << ": " << (room.isAvailable ? "Available" : "Not Available") << endl;
        }
    }
    system("pause"); // wait for user input
}

void customerSearch() {
    system("cls"); // clear the screen
    string customerName;
    cout << "Customer Search" << endl;
    cout << "--------------" << endl;
    cout << "Enter customer name: ";
    cin >> customerName;
    for (const Room &room : rooms) {
        if (room.customerName == customerName) {
            cout << "Room Number: " << room.number << endl;
            cout << "Customer Name: " << room.customerName << endl;
            cout << "Address: " << room.address << endl;
            cout << "Phone Number: " << room.phoneNumber << endl;
            cout << "Room Type: " << room.roomType << endl;
            cout << "Number of People: " << room.numberOfPeople << endl;
            cout << endl;
            system("pause"); // wait for user input
            return;
        }
    }
    cout << "Customer not found!" << endl;
    system("pause"); // wait for user input
}

void checkOut() {
    system("cls"); // clear the screen
    int roomNumber;
    cout << "Check-out" << endl;
    cout << "---------" << endl;
    cout << "Enter room number: ";
    cin >> roomNumber;
    for (Room &room : rooms) {
        if (room.number == roomNumber && !room.isAvailable) {
            room.customerName = "";
            room.address = "";
            room.phoneNumber = "";
            room.roomType = "";
            room.numberOfPeople = 0;
            room.isAvailable = true;
            cout << "Check-out successful!" << endl;
            system("pause"); // wait for user input
            return;
        }
    }
    cout << "Room not found or already available!" << endl;
    system("pause"); // wait for user input
}

void hotelGuestReport() {
    system("cls"); // clear the screen
    cout << "Hotel Guest Report" << endl;
    cout << "-----------------" << endl;
    bool anyGuests = false;
    for (const Room &room : rooms) {
        if (!room.isAvailable) {
            anyGuests = true;
            cout << "Room Number: " << room.number << endl;
            cout << "Customer Name: " << room.customerName << endl;
            cout << "Address: " << room.address << endl;
            cout << "Phone Number: " << room.phoneNumber << endl;
            cout << "Room Type: " << room.roomType << endl;
            cout << "Number of People: " << room.numberOfPeople << endl;
            cout << endl;
        }
    }
    if (!anyGuests) {
        cout << "No guests currently staying." << endl;
    }
    system("pause"); // wait for user input
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                roomManagement();
                break;
            case 2:
                checkIn();
                break;
            case 3:
                roomAvailability();
                break;
            case 4:
                customerSearch();
                break;
            case 5:
                checkOut();
                break;
            case 6:
                hotelGuestReport();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);
    return 0;
}
