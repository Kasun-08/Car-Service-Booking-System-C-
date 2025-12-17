#include <iostream>
#include <string>
#include <vector> // for vectors (Dynamic array)
#include <fstream>
#include <algorithm> // Algorithms for sequences
#include <ctime> // Date and time utilities
#include <regex> // Regular expression support
#include <sstream>
#include <iomanip> // I/O manipulators for formatting output

using namespace std;

// Class representing a customer and their details
class Customer {
private:
    string name;
    string address;
    string phoneNumber;
    string vehicleNumber;
    string vehicleMake;
    string vehicleModel;
    int vehicleYear;

public:
    // Default and parameterized constructor
    Customer() = default;
    Customer(string n, string a, string p, string vn, string vm, string vmod, int vy)
        : name(n), address(a), phoneNumber(p), vehicleNumber(vn), vehicleMake(vm), vehicleModel(vmod), vehicleYear(vy) {}

    // Getter for vehicle number
    string getVehicleNumber() const { return vehicleNumber; }
    // Getter for customer name
    string getName() const { return name; }
    // Function to edit the customer profile
    void editProfile();
    // Overload output operator for displaying customer details
    friend ostream& operator<<(ostream& os, const Customer& customer);
};

// Class representing a booking
class Booking {
private:
    string referenceNumber;
    string date;
    string time;
    string location;
    Customer customer;
    string type;

public:
    //constructor
    Booking(string ref, string d, string t, string l, Customer c, string ty)
        : referenceNumber(ref), date(d), time(t), location(l), customer(c), type(ty) {}


    // Getters for various booking attributes
    string getReferenceNumber() const { return referenceNumber; }
    string getDate() const { return date; }
    string getTime() const { return time; }
    string getLocation() const { return location; }
    Customer getCustomer() const { return customer; }
    // Overload output operator for displaying booking details
    friend ostream& operator<<(ostream& os, const Booking& booking);
};

// Class for managing customers, bookings, and system operations
class BookingSystem {
private:
    vector<Customer> customers;// Store list of registered customers
    vector<Booking> bookings; // List of all bookings
    // Predefined locations & staff credentials
    const vector<string> locations = {"Tokyo", "Osaka", "Kyoto", "Nara", "Chiba"};
    const vector<pair<string, string>> staffCredentials = {
        {"staff1", "pass1"},
        {"staff2", "pass2"},
        {"staff3", "pass3"},
        {"staff4", "pass4"},
        {"staff5", "pass5"}
    };

    // Validate date format and logical correctness
    bool isValidDate(const string& date) {
        regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
        if (!regex_match(date, datePattern)) {
            return false;
        }

        int year, month, day;
        sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

        if (year < 2025 || month < 1 || month > 12 || day < 1 || day > 31) {
            return false;
        }

        return true;
    }

    // Validate time format and ensure it's within the allowed range
    bool isValidTime(const string& time) {
        regex timePattern("^(09|1[0-4]):[0-5][0-9]$");
        return regex_match(time, timePattern);
    }

public:
    // Validate phone number format
    bool isValidPhoneNumber(const string& phoneNumber) {
        regex phonePattern("^\\d{10}$");
        return regex_match(phoneNumber, phonePattern);
    }

    // Authenticate staff credentials
    bool authenticateStaff(const string& username, const string& password) {
        return find(staffCredentials.begin(), staffCredentials.end(),
                    make_pair(username, password)) != staffCredentials.end();
    }

    // Functionality for managing profiles and bookings
    void createCustomerProfile();
    Customer* findCustomerByVehicle(const string& vehicleNumber);
    void createBooking(const string& type);
    void viewBooking();
    void cancelBooking();
    void staffViewBookingsByDate();
    void exportBookingsToFile();
    string generateReferenceNumber(); // Generate a unique booking reference number
};

// Class for managing user interactions with the system
class UserInterface {
private:
    BookingSystem bookingSystem;

    // Log staff activities to a file
    void logStaffActivity(const string& username, const string& action) {
        ofstream logFile("staff_activity.log", ios::app);
        if (logFile.is_open()) {
            time_t now = time(0);
            char* dt = ctime(&now);
            logFile << dt << "User: " << username << " - Action: " << action << "\n";
            logFile.close();
        }
    }

public:
    void mainMenu(); // Main menu for navigating the system
    void staffMenu(); // Menu for staff functionalities
    void customerMenu(); // Menu for customer functionalities
};

// Function for customer to edit their profile details
void Customer::editProfile() {
    cout << "Enter new details:\n";
    cout << "Name: ";
    getline(cin >> ws, name);
    cout << "Address: ";
    getline(cin, address);

    // For validating the phone number
    BookingSystem bs;
    do {
        cout << "Phone Number (10 digits): ";
        getline(cin, phoneNumber);
        if (!bs.isValidPhoneNumber(phoneNumber)) {
            cout << "Invalid phone number. Please enter a 10-digit number.\n";
        }
    } while (!bs.isValidPhoneNumber(phoneNumber));

    cout << "Vehicle Make: ";
    getline(cin, vehicleMake);
    cout << "Vehicle Model: ";
    getline(cin, vehicleModel);
    cout << "Vehicle Manufacturing Year: ";
    cin >> vehicleYear;
}

ostream& operator<<(ostream& os, const Customer& customer) {
    os << "Name: " << customer.name << "\n"
       << "Vehicle Number: " << customer.vehicleNumber;
    return os;
}

ostream& operator<<(ostream& os, const Booking& booking) {
    os << "Reference Number: " << booking.referenceNumber << "\n"
       << "Date: " << booking.date << "\n"
       << "Time: " << booking.time << "\n"
       << "Location: " << booking.location << "\n"
       << "Customer: " << booking.customer;
    return os;
}

// Create a customer profile by collecting and validating details
void BookingSystem::createCustomerProfile() {
    string name, address, phoneNumber, vehicleNumber, vehicleMake, vehicleModel;
    int vehicleYear;

    cout << "Enter the following details:\n";
    cout << "Name: ";
    getline(cin >> ws, name);
    cout << "Address: ";
    getline(cin, address);

    do {
        cout << "Phone Number (10 digits): ";
        getline(cin, phoneNumber);
        if (!isValidPhoneNumber(phoneNumber)) {
            cout << "Invalid phone number. Please enter a 10-digit number.\n";
        }
    } while (!isValidPhoneNumber(phoneNumber));

    cout << "Vehicle Number: ";
    getline(cin, vehicleNumber);
    cout << "Vehicle Make: ";
    getline(cin, vehicleMake);
    cout << "Vehicle Model: ";
    getline(cin, vehicleModel);
    cout << "Vehicle Manufacturing Year: ";
    cin >> vehicleYear;

    customers.emplace_back(name, address, phoneNumber, vehicleNumber, vehicleMake, vehicleModel, vehicleYear);
    cout << "Customer profile created successfully.\n";
}

Customer* BookingSystem::findCustomerByVehicle(const string& vehicleNumber) {
    auto it = find_if(customers.begin(), customers.end(),
        [&vehicleNumber](const Customer& c) { return c.getVehicleNumber() == vehicleNumber; });
    return it != customers.end() ? &(*it) : nullptr;
}

void BookingSystem::createBooking(const string& type) {
    string vehicleNumber;
    cout << "Enter your vehicle number: ";
    cin >> vehicleNumber;
    Customer* customer = findCustomerByVehicle(vehicleNumber);

    if (!customer) {
        cout << "Customer profile not found. Please create a profile first.\n";
        return;
    }

    string date, time, location;
    do {
        cout << "Enter booking date (YYYY-MM-DD): ";
        cin >> date;
        if (!isValidDate(date)) {
            cout << "Invalid date format or date. Please use YYYY-MM-DD format and ensure the date is valid.\n";
        }
    } while (!isValidDate(date));

    if (type == "Service") {
        do {
            cout << "Enter time slot (09:00 - 14:00): ";
            cin >> time;
            if (!isValidTime(time)) {
                cout << "Invalid time format or time. Please use HH:MM format and ensure the time is between 09:00 and 14:00.\n";
            }
        } while (!isValidTime(time));

        cout << "Available locations:\n";
        for (size_t i = 0; i < locations.size(); i++) {
            cout << i + 1 << ". " << locations[i] << "\n";
        }
        int locationChoice;
        cout << "Select location (1-5): ";
        cin >> locationChoice;

        if (locationChoice < 1 || locationChoice > static_cast<int>(locations.size())) {
            cout << "Invalid location choice. Booking cancelled.\n";
            return;
        }
        location = locations[locationChoice - 1];

        auto it = find_if(bookings.begin(), bookings.end(),
            [&](const Booking& b) { return b.getDate() == date && b.getTime() == time && b.getLocation() == location; });
        if (it != bookings.end()) {
            cout << "Selected time is already filled. Select another time.\n";
            return;
        }
    }

    string referenceNumber = generateReferenceNumber();
    bookings.emplace_back(referenceNumber, date, time, location, *customer, type);

    cout << "Booking created successfully.\n";
    cout << bookings.back();
}

void BookingSystem::viewBooking() {
    // Prompt the customer to enter their vehicle number to view the booking.
    string vehicleNumber;
    cout << "Enter your vehicle number to view booking: ";
    cin >> vehicleNumber;

    // Search for bookings associated with the given vehicle number.
    auto it = find_if(bookings.begin(), bookings.end(),
        [&](const Booking& b) { return b.getCustomer().getVehicleNumber() == vehicleNumber; });

    // Display the booking details if found, or notify the user if no booking is found.
        if (it != bookings.end()) {
        cout << *it;
    } else {
        cout << "No booking found for the given vehicle number.\n";
    }
}

void BookingSystem::cancelBooking() {
        // Prompt the customer to enter the reference number of the booking they wish to cancel.
    string referenceNumber;
    cout << "Enter the reference number of the booking to cancel: ";
    cin >> referenceNumber;

    // Search for the booking with the given reference number.
    auto it = find_if(bookings.begin(), bookings.end(),
        [&](const Booking& b) { return b.getReferenceNumber() == referenceNumber; });

    // If the booking is found, remove it from the bookings vector.
    // Otherwise, notify the user that the booking was not found.
    if (it != bookings.end()) {
        bookings.erase(it);
        cout << "Booking canceled successfully.\n";
    } else {
        cout << "Booking not found.\n";
    }
}

void BookingSystem::staffViewBookingsByDate() {
    // Prompt the staff to enter the date for which bookings should be displayed.
    string date, location;
    cout << "Enter the date to view bookings (YYYY-MM-DD): ";
    cin >> date;

    // Display the list of available locations for selection.
    cout << "Available locations:\n";
    for (size_t i = 0; i < locations.size(); i++) {
        cout << i + 1 << ". " << locations[i] << "\n";
    }

    // Prompt the staff to select a location from the list.
    int locationChoice;
    cout << "Select location (1-5): ";
    cin >> locationChoice;

    // Validate the location choice and display bookings if valid.
    if (locationChoice < 1 || locationChoice > static_cast<int>(locations.size())) {
        cout << "Invalid location choice.\n";
        return;
    }
    location = locations[locationChoice - 1];

    // Display all bookings that match the given date and location.
    cout << "Bookings for " << date << " at " << location << ":\n";
    for (const auto& booking : bookings) {
        if (booking.getDate() == date && booking.getLocation() == location) {
            cout << booking << "\n";
        }
    }
}

void BookingSystem::exportBookingsToFile() {
    // Open a file to write booking data.
    ofstream outFile("bookings.txt");
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    // Write all bookings to the file.
    for (const auto& booking : bookings) {
        outFile << booking << "\n";
    }

    // Close the file and notify the user of successful export.
    outFile.close();
    cout << "Bookings exported successfully to bookings.txt.\n";
}

// Generate a unique reference number based on the current number of bookings.
string BookingSystem::generateReferenceNumber() {
    return "REF" + to_string(bookings.size() + 1);
}
//Welcome menu prompt
void UserInterface::mainMenu() {
    int choice;
    do {
        cout << "\n--- Welcome to Car Service Booking System ---\n";
        cout << "1. Staff Login\n";
        cout << "2. Customer Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: staffMenu(); break;
            case 2: customerMenu(); break;
            case 3: cout << "Exiting the system. Thank you!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}
//staff menu logging prompt
void UserInterface::staffMenu() {
    string username, password;
    cout << "\n--- Staff Login ---\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    if (!bookingSystem.authenticateStaff(username, password)) {
        cout << "Invalid credentials. Returning to main menu.\n";
        logStaffActivity(username, "Failed login attempt");
        return;
    }

    logStaffActivity(username, "Successful login");
//staff menu prompt
    int choice;
    do {
        cout << "\n--- Staff Menu ---\n";
        cout << "1. Create Customer Profile\n";
        cout << "2. Create Booking\n";
        cout << "3. Cancel Booking\n";
        cout << "4. View Bookings by Date\n";
        cout << "5. Export Bookings to File\n";
        cout << "6. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookingSystem.createCustomerProfile();
                logStaffActivity(username, "Created customer profile");
                break;
            case 2:
                bookingSystem.createBooking("Service");
                logStaffActivity(username, "Created booking");
                break;
            case 3:
                bookingSystem.cancelBooking();
                logStaffActivity(username, "Cancelled booking");
                break;
            case 4:
                bookingSystem.staffViewBookingsByDate();
                logStaffActivity(username, "Viewed bookings by date");
                break;
            case 5:
                bookingSystem.exportBookingsToFile();
                logStaffActivity(username, "Exported bookings to file");
                break;
            case 6:
                cout << "Returning to main menu.\n";
                logStaffActivity(username, "Logged out");
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
}
//customer menu prompt
void UserInterface::customerMenu() {
    int choice;
    do {
        cout << "\n--- Customer Menu ---\n";
        cout << "1. Create Profile\n";
        cout << "2. Book Service/Repair\n";
        cout << "3. View Booking\n";
        cout << "4. Cancel Booking\n";
        cout << "5. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bookingSystem.createCustomerProfile(); break;
            case 2: bookingSystem.createBooking("Service"); break;
            case 3: bookingSystem.viewBooking(); break;
            case 4: bookingSystem.cancelBooking(); break;
            case 5: cout << "Returning to main menu.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

int main() {
    // Initialize the user interface and display the main menu.
    UserInterface ui;
    ui.mainMenu();
    return 0;
}
