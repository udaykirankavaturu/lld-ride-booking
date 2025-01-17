#include <iostream>
#include <string>
#include <vector>

// Location class
class Location {
public:
    float latitude;
    float longitude;

    Location(float lat, float lon) : latitude(lat), longitude(lon) {}
};

// RideType class
class RideType {
public:
    std::string type;
    float basePricePerKM;

    RideType(std::string t, float price) : type(t), basePricePerKM(price) {}
};

// RideState enum
enum RideState {
    REQUESTED,
    ACCEPTED,
    STARTED,
    COMPLETED,
    CANCELLED
};

// DriverState enum
enum DriverState {
    AVAILABLE,
    IN_RIDE,
    OFFLINE
};

// Vehicle class
class Vehicle {
public:
    std::string number;
    std::string color;
    int year;
    RideState state;

    Vehicle(std::string n, std::string c, int y) : number(n), color(c), year(y), state(RideState::CANCELLED) {}
};

// Driver class
class Driver {
public:
    std::string name;
    std::string mobile;
    Vehicle vehicle;
    DriverState state;

    Driver(std::string n, std::string m, Vehicle v) : name(n), mobile(m), vehicle(v), state(DriverState::AVAILABLE) {}

    void assignRide() {
        state = DriverState::IN_RIDE;
        vehicle.state = RideState::ACCEPTED;
    }

    void startRide() {
        vehicle.state = RideState::STARTED;
    }

    void completeRide() {
        state = DriverState::AVAILABLE;
        vehicle.state = RideState::COMPLETED;
    }

    void goOffline() {
        state = DriverState::OFFLINE;
    }

    void goOnline() {
        state = DriverState::AVAILABLE;
    }
};

// PricingStrategy interface
class PricingStrategy {
public:
    virtual float calculate(int distance, RideType type) = 0;
};

// NormalPricing class
class NormalPricing : public PricingStrategy {
public:
    float calculate(int distance, RideType type) override {
        return distance * type.basePricePerKM; // Base price per km
    }
};

// SurgePricing class
class SurgePricing : public PricingStrategy {
public:
    float calculate(int distance, RideType type) override {
        return distance * type.basePricePerKM * 2; // Double the base price during surge
    }
};

// Ride class
class Ride {
public:
    int id;
    Location pickup;
    Location destination;
    RideState state;
    RideType type;
    Driver* driver;

    Ride(int i, Location p, Location d, RideType t) : id(i), pickup(p), destination(d), type(t), state(RideState::REQUESTED), driver(nullptr) {}

    void assignDriver(Driver* d) {
        driver = d;
        driver->assignRide();
        state = RideState::ACCEPTED;
    }

    void startRide() {
        driver->startRide();
        state = RideState::STARTED;
    }

    void completeRide() {
        driver->completeRide();
        state = RideState::COMPLETED;
    }
};

// RidesManager class
class RidesManager {
public:
    std::vector<Ride> rides;
    std::vector<Driver> drivers;
    PricingStrategy* ps;

    RidesManager(PricingStrategy* strategy) : ps(strategy) {}

    Ride* createRide(Location pickup, Location destination, RideType type) {
        Ride* ride = new Ride(rides.size() + 1, pickup, destination, type);
        rides.push_back(*ride);
        return ride;
    }

    void requestRide(Ride* ride) {
        // Logic to find and assign a driver
        for (Driver& driver : drivers) {
            if (driver.state == DriverState::AVAILABLE) {
                ride->assignDriver(&driver);
                std::cout << "Driver " << driver.name << " assigned to ride " << ride->id << std::endl;
                return;
            }
        }
        std::cout << "No drivers available for ride " << ride->id << std::endl;
    }

    void startRide(Ride* ride) {
        if (ride->driver != nullptr && ride->state == RideState::ACCEPTED) {
            ride->startRide();
            std::cout << "Ride " << ride->id << " started." << std::endl;
        } else {
            std::cout << "Cannot start ride " << ride->id << std::endl;
        }
    }

    void completeRide(Ride* ride) {
        if (ride->driver != nullptr && ride->state == RideState::STARTED) {
            ride->completeRide();
            std::cout << "Ride " << ride->id << " completed." << std::endl;
            float fare = ps->calculate(10, ride->type); // Assuming distance is 10 km
            std::cout << "Fare: ₹" << fare << std::endl;
        } else {
            std::cout << "Cannot complete ride " << ride->id << std::endl;
        }
    }
};

// Main function to demonstrate the ride lifecycle
int main() { 
    // Create pricing strategy
    PricingStrategy* ps = new NormalPricing();

    // Create rides manager
    RidesManager manager(ps);

    // Create some drivers
    Vehicle car1("ABC123", "Red", 2020);
    Driver driver1("Vinay Kumar", "1234567890", car1);
    manager.drivers.push_back(driver1);

    Vehicle car2("XYZ789", "Blue", 2022);
    Driver driver2("Rahul Sharma", "0987654321", car2);
    manager.drivers.push_back(driver2);

    // Driver goes online
    driver1.goOnline();
    std::cout << "Driver " << driver1.name << " is now available." << std::endl;

    // Create ride types
    RideType economy("Economy", 15.0);
    RideType premium("Premium", 20.0);

    // Create a ride
    Location pickup(37.7749, -122.4194); 
    Location destination(37.7805, -122.4073); 

    Ride* ride = manager.createRide(pickup, destination, economy);

    // Request the ride
    manager.requestRide(ride);

    // Start the ride
    manager.startRide(ride);

    // Complete the ride
    manager.completeRide(ride);

    // Driver goes offline
    driver1.goOffline();
    std::cout << "Driver " << driver1.name << " is now offline." << std::endl;



    return 0;
}