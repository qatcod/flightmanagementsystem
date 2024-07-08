#include <iostream>
#include<windows.h>
#include <fstream>
#include <string>
using namespace std;

const int max_flights = 100; 

void loadingBar();
void greeting();

class Flight {
private:
    string flightNumber;
    string source;
    string destination;
    string date;
    string time;
    int availableSeats;
    double fare;

public:
    Flight() : availableSeats(0), fare(0.0) {}

    void setDetails(const string& fn, const string& src, const string& dest, const string& d, const string& t, int seats, double f) {
        flightNumber = fn;
        source = src;
        destination = dest;
        date = d;
        time = t;
        availableSeats = seats;
        fare = f;
    }

    void displayDetails() const;
    bool checkAvailability(int seats) const;
    bool bookSeat(int seats);
    bool cancelSeat(int seats);
    string getFlightNumber() const { return flightNumber; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    string getDate() { return date; }
    string getTime() { return time; }
    int getSeats() { return availableSeats; }
};

class Admin {
private:
    string username;
    string password;

public:
    Admin(const string& u, const string& p) : username(u), password(p) {}

    void addFlight(Flight flights[], int& flightCount);
    void removeFlight(Flight flights[], int& flightCount, const string& flightNumber);
    void modifyFlight(Flight flights[], int flightCount, const string& flightNumber);
    void viewAllFlights(const Flight flights[], int flightCount) const;
    void setFlightDetails(Flight& flight);
    void setTicketPrice(Flight& flight, double price);
    string getUsername() { return username; }
    string getPassword() { return password; }
};

class User {
private:
    string userID;
    string name;
    string contactDetails;

public:
    User(const string& id, const string& n, const string& contact) : userID(id), name(n), contactDetails(contact) {}

    void searchFlight(const Flight flights[], int flightCount, const string& source, const string& destination) const;
    void bookFlight(Flight flights[], int flightCount, const string& flightNumber, int seats);
    void cancelBooking(Flight flights[], int flightCount, const string& flightNumber, int seats);
    void viewBooking(const Flight flights[], int flightCount, const string& flightNumber) const;
};

class Booking {
private:
    string bookingID;
    string flightNumber;
    string userID;
    int seatsBooked;

public:
    Booking(const string& bid, const string& fn, const string& uid, int seats) : bookingID(bid), flightNumber(fn), userID(uid), seatsBooked(seats) {}

    void createBooking();
    void cancelBooking();
    void displayBookingDetails() const;
};

// Function definitions for Flight
void Flight::displayDetails() const {
    cout << "Flight Number: " << flightNumber << endl;
    cout << "Source: " << source << endl;
    cout << "Destination: " << destination << endl;
    cout << "Date: " << date << endl;
    cout << "Time: " << time << endl;
    cout << "Available Seats: " << availableSeats << endl;
    cout << "Fare: $" << fare << endl;
}

bool Flight::checkAvailability(int seats) const {
    return availableSeats >= seats;
}

bool Flight::bookSeat(int seats) {
    if (checkAvailability(seats)) {
        availableSeats -= seats;
        return true;
    }
    return false;
}

bool Flight::cancelSeat(int seats) {
    availableSeats += seats;
    return true;
}

void Admin::addFlight(Flight flights[], int& flightCount) {
    if (flightCount >= max_flights) {
        cout << "Cannot add more flights. Maximum limit reached." << endl;
        return;
    }
    string fn, src, dest, d, t;
    int seats;
    double fare;
    cout << "Enter Flight Number: ";
    cin >> fn;
    cout << "Enter Source: ";
    cin >> src;
    cout << "Enter Destination: ";
    cin >> dest;
    cout << "Enter Date: ";
    cin >> d;
    cout << "Enter Time: ";
    cin >> t;
    cout << "Enter Available Seats: ";
    cin >> seats;
    cout << "Enter Fare: ";
    cin >> fare;
    flights[flightCount++].setDetails(fn, src, dest, d, t, seats, fare);
}

void Admin::removeFlight(Flight flights[], int& flightCount, const string& flightNumber) {
    for (int i = 0; i < flightCount; ++i) {
        if (flights[i].getFlightNumber() == flightNumber) {
            for (int j = i; j < flightCount - 1; ++j) {
                flights[j] = flights[j + 1];
            }
            --flightCount;
            break;
        }
    }
}

void Admin::modifyFlight(Flight flights[], int flightCount, const string& flightNumber) {
    for (int i = 0; i < flightCount; ++i) {
        if (flights[i].getFlightNumber() == flightNumber) {
            setFlightDetails(flights[i]);
            break;
        }
    }
}

void Admin::viewAllFlights(const Flight flights[], int flightCount) const {
    for (int i = 0; i < flightCount; ++i) {
        flights[i].displayDetails();
        cout << "--------------------------" << endl;
    }
}

void Admin::setFlightDetails(Flight& flight) {
    string fn, src, dest, d, t;
    int seats;
    double fare;
    cout << "Enter new Flight Number: ";
    cin >> fn;
    cout << "Enter new Source: ";
    cin >> src;
    cout << "Enter new Destination: ";
    cin >> dest;
    cout << "Enter new Date: ";
    cin >> d;
    cout << "Enter new Time: ";
    cin >> t;
    cout << "Enter new Available Seats: ";
    cin >> seats;
    cout << "Enter new Fare: ";
    cin >> fare;
    flight.setDetails(fn, src, dest, d, t, seats, fare);
}

void Admin::setTicketPrice(Flight& flight, double price) {
    string fn, src, dest, d, t;
    int seats;
    flight.setDetails(flight.getFlightNumber(), flight.getSource(), flight.getDestination(), flight.getDate(), flight.getTime(), flight.getSeats(), price);
}

void User::searchFlight(const Flight flights[], int flightCount, const string& source, const string& destination) const {
    for (int i = 0; i < flightCount; ++i) {
        if (flights[i].getSource() == source && flights[i].getDestination() == destination) {
            flights[i].displayDetails();
        }
    }
}

void User::bookFlight(Flight flights[], int flightCount, const string& flightNumber, int seats) {
    for (int i = 0; i < flightCount; ++i) {
        if (flights[i].getFlightNumber() == flightNumber) {
            if (flights[i].bookSeat(seats)) {
                cout << "Booking successful!" << endl;
            }
            else {
                cout << "Not enough seats available." << endl;
            }
            break;
        }
    }
}

void User::cancelBooking(Flight flights[], int flightCount, const string& flightNumber, int seats) {
    for (int i = 0; i < flightCount; ++i) {
        if (flights[i].getFlightNumber() == flightNumber) {
            flights[i].cancelSeat(seats);
            cout << "Booking cancelled." << endl;
            break;
        }
    }
}

void User::viewBooking(const Flight flights[], int flightCount, const string& flightNumber) const {
    for (int i = 0; i < flightCount; ++i) {
        if (flights[i].getFlightNumber() == flightNumber) {
            flights[i].displayDetails();
            break;
        }
    }
}

void Booking::createBooking() {
    ofstream outFile("bookings.txt", ios::app); 

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    outFile << "Booking ID: " << bookingID << endl;
    outFile << "Flight Number: " << flightNumber << endl;
    outFile << "User ID: " << userID << endl;
    outFile << "Seats Booked: " << seatsBooked << endl;
    outFile << "--------------------------" << endl;

    outFile.close();
    cout << "Booking created successfully!" << endl;
}

void Booking::cancelBooking() {
    ifstream inFile("bookings.txt");
    ofstream outFile("temp.txt");

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        inFile.close();
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.find("Booking ID: " + bookingID) != string::npos) {
            for (int i = 0; i < 4; ++i) {
                getline(inFile, line); 
            }
            found = true;
        }
        else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");

    if (found) {
        cout << "Booking with ID " << bookingID << " cancelled successfully!" << endl;
    }
    else {
        cout << "Booking with ID " << bookingID << " not found!" << endl;
    }
}

void Booking::displayBookingDetails() const {
    cout << "Booking ID: " << bookingID << endl;
    cout << "Flight Number: " << flightNumber << endl;
    cout << "User ID: " << userID << endl;
    cout << "Seats Booked: " << seatsBooked << endl;
}

int main() {
    system("color 3");
    greeting();
    Flight flights[max_flights];
    int flightCount = 0;
    Admin admin("admin", "admin123"); 

    flights[flightCount++].setDetails("FN001", "New York", "London", "2024-07-10", "14:00", 200, 500.0);
    flights[flightCount++].setDetails("FN002", "London", "Paris", "2024-07-11", "12:00", 150, 400.0);
    flights[flightCount++].setDetails("FN003", "Paris", "Rome", "2024-07-12", "11:00", 180, 450.0);

    int choice;
    string username, password;

    do {
        cout << "\n===== Flight Management System =====" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. User Menu" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nEnter Admin Username: ";
            cin >> username;
            cout << "Enter Admin Password: ";
            cin >> password;

            if (username == admin.getUsername() && password == admin.getPassword()) {
                int adminChoice;
                do {
                    cout << "\n===== Admin Menu =====" << endl;
                    cout << "1. Add Flight" << endl;
                    cout << "2. Remove Flight" << endl;
                    cout << "3. Modify Flight" << endl;
                    cout << "4. View All Flights" << endl;
                    cout << "5. Logout" << endl;
                    cout << "Enter your choice: ";
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1:
                        admin.addFlight(flights, flightCount);
                        break;
                    case 2: {
                        string flightNumber;
                        cout << "Enter Flight Number to Remove: ";
                        cin >> flightNumber;
                        admin.removeFlight(flights, flightCount, flightNumber);
                        break;
                    }
                    case 3: {
                        string flightNumber;
                        cout << "Enter Flight Number to Modify: ";
                        cin >> flightNumber;
                        admin.modifyFlight(flights, flightCount, flightNumber);
                        break;
                    }
                    case 4:
                        admin.viewAllFlights(flights, flightCount);
                        break;
                    case 5:
                        cout << "Logging out from Admin..." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } while (adminChoice != 5);
            }
            else {
                cout << "Invalid username or password. Please try again." << endl;
            }
            break;
        case 2:
        {
            string userID, name, contact;
            cout << "Enter User ID: ";
            cin >> userID;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Contact Details: ";
            cin >> contact;
            User user(userID, name, contact);

            int userChoice;
            do {
                cout << "\n===== User Menu =====" << endl;
                cout << "1. Search Flight" << endl;
                cout << "2. Book Flight" << endl;
                cout << "3. Cancel Booking" << endl;
                cout << "4. View Booking" << endl;
                cout << "5. Logout" << endl;
                cout << "Enter your choice: ";
                cin >> userChoice;

                switch (userChoice) {
                case 1: {
                    string src, dest;
                    cout << "Enter Source: ";
                    cin >> src;
                    cout << "Enter Destination: ";
                    cin >> dest;
                    user.searchFlight(flights, flightCount, src, dest);
                    break;
                }
                case 2: {
                    string flightNumber;
                    int seats;
                    cout << "Enter Flight Number: ";
                    cin >> flightNumber;
                    cout << "Enter Number of Seats: ";
                    cin >> seats;
                    user.bookFlight(flights, flightCount, flightNumber, seats);
                    break;
                }
                case 3: {
                    string flightNumber;
                    int seats;
                    cout << "Enter Flight Number: ";
                    cin >> flightNumber;
                    cout << "Enter Number of Seats to Cancel: ";
                    cin >> seats;
                    user.cancelBooking(flights, flightCount, flightNumber, seats);
                    break;
                }
                case 4: {
                    string flightNumber;
                    cout << "Enter Flight Number: ";
                    cin >> flightNumber;
                    user.viewBooking(flights, flightCount, flightNumber);
                    break;
                }
                case 5:
                    cout << "Logging out from User..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (userChoice != 5);
            break;
        }
        case 3:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}



void loadingBar()

{

    char a = 177, b = 219;
    cout << "\n\n\t\t\t\t\t\t Loading...\n\n";
    cout << "\t\t\t\t\t";

    for (int i = 0; i < 26; i++) {
        cout << char(a);
    }
    cout << "\r\t\t\t\t\t";

    for (int i = 0; i < 26; i++) {
        cout << char(b);

        Sleep(200);

    }
    cout << endl;
    cout << "\t\t\t\t";
    system("pause");
    system("cls");
}

void greeting()
{
    cout << "\n\n\n\n\n";
    cout << "\t\t\t   _        __  ___  __          ____  ___  ___ ___  ____" << endl;
    cout << "\t\t\t /\\  \\      /\\  \\  _ \\/\\   \\        /\\    __\\/\\    _  \\/\\    _  \\  _   \\/\\  __ \\" << endl;
    cout << "\t\t\t \\ \\  \\     \\ \\  \\ \\   _/\\ \\   \\       \\ \\   \\_/\\ \\   \\/\\  \\ \\   \\ \\\\_\\\\   \\ \\   __/" << endl;
    cout << "\t\t\t  \\ \\  \\     \\ \\  \\ \\  \\_\\ \\   \\       \\ \\   \\     \\ \\   \\\\\\  \\ \\   \\ \\|_|\\   \\ \\  \\__" << endl;
    cout << "\t\t\t   \\ \\  \\   _ \\ \\  \\ \\  \\_\\ \\   \\       \\ \\   \\     \\ \\   \\\\\\  \\ \\   \\    \\ \\   \\ \\  \\___\\" << endl;
    cout << "\t\t\t    \\ \\  \\/|_\\\\ \\  \\ \\  \\/|\\ \\   \\__\\ \\   \\__\\ \\   \\\\\\  \\ \\   \\    \\ \\   \\ \\  \\__" << endl;
    cout << "\t\t\t     \\ \\____\\ \\__\\ \\___\\ \\___\\ \\__\\ \\_\\    \\ \\_\\ \\____|" << endl;
    cout << "\t\t\t      \\|____|\\|__\\|____|\\|___|\\___|\\|_|     \\|_|\\|____|" << endl;

    cout << "\n\n";
    cout << "\t\t\t\t**************( " << char(3) << " TO ONESTAR AIRLINES " << char(3) << " )*************\n";
    cout << "\n\n\n\n";
    cout << "\t\tWelcome to our Airline sir....." << endl;
    cout << "\t\twe are opening menu for you\n";
    loadingBar();
}
