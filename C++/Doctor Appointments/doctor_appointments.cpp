#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;

// Structure to hold appointment details
struct Appointment {
    string patientName;
    string date;
    string time;
};

// Function to generate a list of available appointments
void generateAvailableAppointments(vector<Appointment>& availableAppointments) {
    // Predefined dates and times for appointments
    vector<string> dates = {"21/05/2024", "22/05/2024", "23/05/2024"};
    vector<string> times = {"10:00", "11:00", "14:00", "15:00"};

    // Generate appointments for each date and time
    for (const auto& date : dates) {
        for (const auto& time : times) {
            availableAppointments.push_back({"", date, time});
        }
    }
}

// Function to display the list of available appointments
void displayAvailableAppointments(const vector<Appointment>& availableAppointments) {
    cout << "Available Appointments:\n";
    for (size_t i = 0; i < availableAppointments.size(); ++i) {
        cout << i + 1 << ". Date: " << availableAppointments[i].date
             << ", Time: " << availableAppointments[i].time << "\n";
    }
}

// Function to check if there is a conflict with an existing appointment
bool isAppointmentConflict(const vector<Appointment>& appointments, const string& date, const string& time) {
    for (const auto& appointment : appointments) {
        if (appointment.date == date && appointment.time == time) {
            return true; // Conflict found
        }
    }
    return false; // No conflict
}

// Function to book an appointment
void bookAppointment(vector<Appointment>& appointments, vector<Appointment>& availableAppointments) {
    string patientName;
    int choice;

    // Display available appointments to the user
    displayAvailableAppointments(availableAppointments);

    // Get the user's choice of appointment
    cout << "Enter the number of the appointment you want to book: ";
    cin >> choice;

    // Validate the user's choice
    if (choice < 1 || choice > availableAppointments.size()) {
        cout << "Invalid choice. Please try again.\n";
        return;
    }

    // Get the patient's name
    cout << "Enter patient name: ";
    cin >> patientName;

    // Get the selected appointment's date and time
    string date = availableAppointments[choice - 1].date;
    string time = availableAppointments[choice - 1].time;

    // Check for conflicts with existing appointments
    if (isAppointmentConflict(appointments, date, time)) {
        cout << "Sorry, there is already another appointment at that date and time.\n";
    } else {
        // Book the appointment and remove it from the available list
        appointments.push_back({patientName, date, time});
        availableAppointments.erase(availableAppointments.begin() + choice - 1);
        cout << "Appointment booked successfully.\n";
    }
}

// Function to check and display existing appointments
void checkAppointments(const vector<Appointment>& appointments) {
    if (appointments.empty()) {
        cout << "No appointments booked yet.\n";
    } else {
        cout << "Existing appointments:\n";
        for (const auto& appointment : appointments) {
            cout << "Patient: " << appointment.patientName
                 << ", Date: " << appointment.date
                 << ", Time: " << appointment.time << "\n";
        }
    }
}

// Function to clear the console screen
void clearScreen() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

// Main function to run the appointment system
int main() {
    vector<Appointment> appointments; // Vector to store booked appointments
    vector<Appointment> availableAppointments; // Vector to store available appointments
    generateAvailableAppointments(availableAppointments); // Generate the available appointments

    int choice;
    do {
        // Display the main menu
        cout << "Doctor Appointment System\n"
             << "1. Book Appointment\n"
             << "2. Check Existing Appointments\n"
             << "0. Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        
        // Handle the user's menu choice
        switch (choice) {
            case 1:
                bookAppointment(appointments, availableAppointments); // Book an appointment
                break;
            case 2:
                checkAppointments(appointments); // Check existing appointments
                break;
            case 0:
                cout << "Exiting...\n"; // Exit the program
                break;
            default:
                cout << "Invalid choice. Please try again.\n"; // Handle invalid choices
        }

        // Wait for user input before clearing the screen and returning to the menu
        if (choice != 0) {
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            clearScreen();
        }
    } while (choice != 0); // Repeat until the user chooses to exit

    return 0;
}
