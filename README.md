# Driveit: Console-Based Car Rental System

**Driveit** is a C++ console application designed to manage car rentals efficiently. It features a dual-user system (Admin and Customer) with persistent data storage using text files. This project was developed as part of my first-semester Computer Science coursework.

## 🚀 Features

### **Admin Portal**
* **Inventory Management:** Add new vehicles to the fleet or remove old ones.
* **Fleet Overview:** View a complete list of all cars including model, brand, and pricing.
* **Reservation Tracking:** Monitor all active and past bookings made by customers.

### **Customer Portal**
* **User Registration:** Create a personal account with a unique Customer ID.
* **Smart Availability Check:** Search for cars that are available specifically during your requested dates.
* **Booking System:** Reserve a car with automatic cost calculation based on duration.
* **Manage Bookings:** View your current reservations or cancel them if plans change.

### **Technical Highlights**
* **File Handling:** Uses `users.txt`, `cars.txt`, and `reservations.txt` to save data permanently.
* **Date Logic:** Includes a custom date-to-days conversion algorithm to handle reservation scheduling and overlap prevention.
* **Data Structures:** Utilizes `std::vector` and `structs` for efficient in-memory data management.

## 🛠️ How to Run

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/YourUsername/Driveit.git
    ```
2.  **Compile the Code:**
    Use any C++ compiler (like G++):
    ```bash
    g++ main.cpp -o Driveit
    ```
3.  **Run the Executable:**
    ```bash
    ./Driveit
    ```
    *Note: Ensure the `.txt` files are in the same directory as the executable.*

## 📂 File Structure
* `main.cpp`: The primary source code containing the logic and UI.
* `users.txt`: Stores user credentials and roles.
* `cars.txt`: Stores the car inventory details.
* `reservations.txt`: Stores all booking transaction records.

## 📝 License
This project is for educational purposes. Feel free to use and modify it!
