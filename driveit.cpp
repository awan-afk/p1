#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct User {
    string username, password, role, id;
};

struct Car {
    string id, model, brand;
    int year;
    double pricePerDay;
};

struct Reservation {
    string reservationID, customerID, carID;
    int sd, sm, sy, ed, em, ey;
    double totalCost;
};

vector<User> users;
vector<Car> cars;
vector<Reservation> reservations;

// date to days

int convertToDays(int d, int m, int y) {
    return y * 365 + m * 30 + d;
}

// file funtions

void loadUsers() {
    ifstream file("users.txt");
    User u;
    while (file >> u.username >> u.password >> u.role >> u.id)
        users.push_back(u);
}

void saveUsers() {
    ofstream file("users.txt");
    for (int i = 0; i < users.size(); i++)
        file << users[i].username << " "
             << users[i].password << " "
             << users[i].role << " "
             << users[i].id << endl;
}

void loadCars() {
    ifstream file("cars.txt");
    Car c;
    while (file >> c.id >> c.model >> c.brand >> c.year >> c.pricePerDay)
        cars.push_back(c);
}

void saveCars() {
    ofstream file("cars.txt");
    for (int i = 0; i < cars.size(); i++)
        file << cars[i].id << " "
             << cars[i].model << " "
             << cars[i].brand << " "
             << cars[i].year << " "
             << cars[i].pricePerDay << endl;
}

void loadReservations() {
    ifstream file("reservations.txt");
    Reservation r;
    while (file >> r.reservationID >> r.customerID >> r.carID
                >> r.sd >> r.sm >> r.sy
                >> r.ed >> r.em >> r.ey
                >> r.totalCost)
        reservations.push_back(r);
}

void saveReservations() {
    ofstream file("reservations.txt");
    for (int i = 0; i < reservations.size(); i++)
        file << reservations[i].reservationID << " "
             << reservations[i].customerID << " "
             << reservations[i].carID << " "
             << reservations[i].sd << " "
             << reservations[i].sm << " "
             << reservations[i].sy << " "
             << reservations[i].ed << " "
             << reservations[i].em << " "
             << reservations[i].ey << " "
             << reservations[i].totalCost << endl;
}

// validation functions

bool usernameExists(string name) {
    for (int i = 0; i < users.size(); i++)
        if (users[i].username == name)
            return true;
    return false;
}

bool carAvailable(string id, int sd, int sm, int sy,
                  int ed, int em, int ey) {

    int newStart = convertToDays(sd, sm, sy);
    int newEnd   = convertToDays(ed, em, ey);

    for (int i = 0; i < reservations.size(); i++) {

        if (reservations[i].carID == id) {

            int oldStart = convertToDays(
                reservations[i].sd,
                reservations[i].sm,
                reservations[i].sy);

            int oldEnd = convertToDays(
                reservations[i].ed,
                reservations[i].em,
                reservations[i].ey);

            if (!(newEnd < oldStart || newStart > oldEnd))
                return false;
        }
    }

    return true;
}

// admin

void addCar() {
    Car c;
    cout << "Car ID: "; cin >> c.id;
    cout << "Model: "; cin >> c.model;
    cout << "Brand: "; cin >> c.brand;
    cout << "Year: "; cin >> c.year;
    cout << "Price per day: "; cin >> c.pricePerDay;
    cars.push_back(c);
    saveCars();
    cout << "Car added!\n";
}

void deleteCar() {
    string id;
    cout << "Enter Car ID to delete: ";
    cin >> id;

    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].id == id) {
            cars.erase(cars.begin() + i);
            saveCars();
            cout << "Car deleted!\n";
            return;
        }
    }
    cout << "Car not found!\n";
}

void viewCars() {
    for (int i = 0; i < cars.size(); i++)
        cout << cars[i].id << " | "
             << cars[i].model << " | "
             << cars[i].brand << " | "
             << cars[i].year << " | "
             << cars[i].pricePerDay << endl;
}

void viewAllReservations() {
    for (int i = 0; i < reservations.size(); i++)
        cout << reservations[i].reservationID << " | "
             << reservations[i].customerID << " | "
             << reservations[i].carID << " | "
             << reservations[i].sd << "/"
             << reservations[i].sm << "/"
             << reservations[i].sy << " to "
             << reservations[i].ed << "/"
             << reservations[i].em << "/"
             << reservations[i].ey
             << " | Cost: "
             << reservations[i].totalCost << endl;
}

// customer

void registerUser() {
    User u;
    cout << "Username: ";
    cin >> u.username;

    if (usernameExists(u.username)) {
        cout << "Username already exists!\n";
        return;
    }

    cout << "Password: ";
    cin >> u.password;

    u.role = "customer";

    int count = 0;
    for (int i = 0; i < users.size(); i++)
        if (users[i].role == "customer")
            count++;

    u.id = "C" + to_string(count + 1);

    users.push_back(u);
    saveUsers();

    cout << "Registered successfully!\n";
    cout << "Your Customer ID: " << u.id << endl;
}

void viewAvailableCars() {
    int sd, sm, sy, ed, em, ey;

    cout << "Enter start date (d m y): ";
    cin >> sd >> sm >> sy;

    cout << "Enter end date (d m y): ";
    cin >> ed >> em >> ey;

    if (convertToDays(ed, em, ey) <= convertToDays(sd, sm, sy)) {
        cout << "Invalid date range!\n";
        return;
    }

    for (int i = 0; i < cars.size(); i++)
        if (carAvailable(cars[i].id, sd, sm, sy, ed, em, ey))
            cout << cars[i].id << " | "
                 << cars[i].model << " | "
                 << cars[i].brand << " | "
                 << cars[i].pricePerDay << endl;
}

void bookCar(string customerID) {

    string carID;
    cout << "Car ID: ";
    cin >> carID;

    int sd, sm, sy, ed, em, ey;
    cout << "Start date (d m y): ";
    cin >> sd >> sm >> sy;
    cout << "End date (d m y): ";
    cin >> ed >> em >> ey;

    if (convertToDays(ed, em, ey) <= convertToDays(sd, sm, sy)) {
        cout << "Invalid date range!\n";
        return;
    }

    bool found = false;
    double price = 0;

    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].id == carID) {
            found = true;
            price = cars[i].pricePerDay;
            break;
        }
    }

    if (!found) {
        cout << "Car not found!\n";
        return;
    }

    if (!carAvailable(carID, sd, sm, sy, ed, em, ey)) {
        cout << "Car not available!\n";
        return;
    }

    Reservation r;
    r.reservationID = "R" + to_string(reservations.size() + 1);
    r.customerID = customerID;
    r.carID = carID;
    r.sd = sd; r.sm = sm; r.sy = sy;
    r.ed = ed; r.em = em; r.ey = ey;

    int days = convertToDays(ed, em, ey)
             - convertToDays(sd, sm, sy);

    r.totalCost = days * price;

    reservations.push_back(r);
    saveReservations();

    cout << "Booked! Reservation ID: "
         << r.reservationID << endl;
}

void cancelReservation(string customerID) {

    string rid;
    cout << "Enter Reservation ID to cancel: ";
    cin >> rid;

    for (int i = 0; i < reservations.size(); i++) {
        if (reservations[i].reservationID == rid &&
            reservations[i].customerID == customerID) {

            reservations.erase(reservations.begin() + i);
            saveReservations();
            cout << "Reservation cancelled!\n";
            return;
        }
    }

    cout << "Reservation not found!\n";
}

void viewMyReservations(string customerID) {
    for (int i = 0; i < reservations.size(); i++)
        if (reservations[i].customerID == customerID)
            cout << reservations[i].reservationID << " | "
                 << reservations[i].carID << " | "
                 << reservations[i].sd << "/"
                 << reservations[i].sm << "/"
                 << reservations[i].sy << " to "
                 << reservations[i].ed << "/"
                 << reservations[i].em << "/"
                 << reservations[i].ey
                 << endl;
}

// login

User* login() {

    string uname, pass;

    cout << "Username: ";
    cin >> uname;

    cout << "Password: ";
    cin >> pass;

    for (int i = 0; i < users.size(); i++)
        if (users[i].username == uname &&
            users[i].password == pass)
            return &users[i];

    return NULL;
}

// main

int main() {

    loadUsers();
    loadCars();
    loadReservations();

    int choice;

    do {
        cout << "\n===== DriveIT Rentals =====\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {

            User* current = login();

            if (current == NULL) {
                cout << "Invalid login!\n";
                continue;
            }

            if (current->role == "admin") {

                int aChoice;

                do {
                    cout << "\n--- Admin Menu ---\n";
                    cout << "1. Add Car\n";
                    cout << "2. Delete Car\n";
                    cout << "3. View Cars\n";
                    cout << "4. View Reservations\n";
                    cout << "5. Logout\n";
                    cin >> aChoice;

                    if (aChoice == 1) addCar();
                    else if (aChoice == 2) deleteCar();
                    else if (aChoice == 3) viewCars();
                    else if (aChoice == 4) viewAllReservations();

                } while (aChoice != 5);
            }

            else {

                int cChoice;

                do {
                    cout << "\n--- Customer Menu ---\n";
                    cout << "1. View Available Cars\n";
                    cout << "2. Book Car\n";
                    cout << "3. View My Reservations\n";
                    cout << "4. Cancel Reservation\n";
                    cout << "5. Logout\n";
                    cin >> cChoice;

                    if (cChoice == 1) viewAvailableCars();
                    else if (cChoice == 2) bookCar(current->id);
                    else if (cChoice == 3) viewMyReservations(current->id);
                    else if (cChoice == 4) cancelReservation(current->id);

                } while (cChoice != 5);
            }
        }

        else if (choice == 2) {
            registerUser();
        }

    } while (choice != 3);

    return 0;
}

