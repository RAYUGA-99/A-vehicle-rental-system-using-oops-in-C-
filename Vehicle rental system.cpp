
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

// Base class
class Vehicle {
private:
    string vehicleId;
    string model;
    double hourlyRate;

protected:
    double getHourlyRate() const {
        return hourlyRate;
    }

public:
    Vehicle(string id, string m, double rate) {
        vehicleId = id;
        model = m;
        hourlyRate = rate;
    }

    virtual ~Vehicle() {}

    virtual double calculateRental(int hours) const = 0;
    virtual string getVehicleType() const = 0;

    virtual void displayDetails(int hours) const {
        cout << "\n------ " << getVehicleType()
             << " Rental Details ------\n";

        cout << "Vehicle ID      : " << vehicleId << endl;
        cout << "Model           : " << model << endl;
        cout << "Rental Duration : " << hours << " hours" << endl;

        cout << fixed << setprecision(2);
        cout << "Hourly Rate     : Rs. "
             << hourlyRate << endl;

        cout << "Total Charges   : Rs. "
             << calculateRental(hours) << endl;
    }
};

// Derived class: Car
class Car : public Vehicle {
public:
    Car(string id, string model, double rate)
        : Vehicle(id, model, rate) {}

    double calculateRental(int hours) const override {
        return getHourlyRate() * hours;
    }

    string getVehicleType() const override {
        return "Car";
    }
};

// Derived class: Bike
class Bike : public Vehicle {
public:
    Bike(string id, string model, double rate)
        : Vehicle(id, model, rate) {}

    double calculateRental(int hours) const override {
        return getHourlyRate() * hours * 0.90;
    }

    string getVehicleType() const override {
        return "Bike";
    }
};

// Function to validate rental duration
int getRentalHours() {
    int hours;

    while (true) {
        cout << "Enter rental duration in hours: ";

        if (cin >> hours && hours > 0) {
            return hours;
        }

        cout << "Invalid input! Enter a positive whole number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    Car car("CAR101", "Honda City", 250.00);
    Bike bike("BIKE201", "Honda Activa", 80.00);

    int choice;

    cout << "====================================\n";
    cout << "       VEHICLE RENTAL SYSTEM\n";
    cout << "====================================\n";

    cout << "1. Rent a Car\n";
    cout << "2. Rent a Bike\n";
    cout << "3. Exit\n";

    while (true) {
        cout << "\nEnter your choice (1-3): ";

        if (cin >> choice && choice >= 1 && choice <= 3) {
            break;
        }

        cout << "Invalid choice! Please select 1, 2, or 3.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (choice == 3) {
        cout << "Thank you for using the system!\n";
        return 0;
    }

    int hours = getRentalHours();

    // Runtime polymorphism
    Vehicle* selectedVehicle;

    if (choice == 1) {
        selectedVehicle = &car;
    } else {
        selectedVehicle = &bike;
    }

    selectedVehicle->displayDetails(hours);

    cout << "\nThank you for using the Vehicle Rental System!\n";

    return 0;
}
