# Ride Booking System Simulation

## Overview

This project demonstrates a Low-Level Design (LLD) of a **Ride Booking System** using core Object-Oriented Programming (OOP) principles and **Design Patterns**. The system models real-world interactions between rides, drivers, and vehicles, showcasing best practices in software design, state management, and strategy implementation.

---

## Features

### Functional Features

- Simulates the lifecycle of a ride request, from initiation to completion.
- Supports multiple pricing strategies, including normal and surge pricing.
- Manages ride and driver states dynamically throughout the ride lifecycle.
- Encapsulates system components for modular and scalable design.

## Code Structure

### Classes and Responsibilities

#### Core Classes

- **Ride**: Represents a ride and its attributes, including state and pricing strategy.
- **Driver**: Represents a driver and manages their current state (available, in ride, etc.).
- **Vehicle**: Represents a vehicle with attributes like type and registration number.
- **RidesManager**: Coordinates the ride booking process, driver assignment, and pricing.

#### Patterns in Action

- **State Pattern**

  - `RideState`: Manages the lifecycle of a ride (`Idle`, `InProgress`, `Completed`).
  - `DriverState`: Handles driver availability and activity states.

- **Strategy Pattern**

  - `PricingStrategy`: Abstract class for pricing logic.
  - `NormalPricing`: Concrete implementation for standard pricing.
  - `SurgePricing`: Concrete implementation for surge pricing based on demand.

- **Dependency Injection**

  - Allows dynamic injection of different pricing strategies into the `RidesManager`.

- **Mediator Pattern**
  - `RidesManager` managing interactions between rides and drivers.

---

## How to Use

### Run the Simulation

1. Compile the code using a C++ compiler:
   ```bash
   g++ -std=c++14 main.cpp -o main
   ```
2. Execute the program:
   ```bash
   ./main
   ```

### Observe the Output

- The simulation demonstrates the end-to-end flow of a ride booking system:
  - Requesting a ride.
  - Assigning a driver and vehicle.
  - Calculating the ride cost using the pricing strategy.
  - Completing the ride.

---

## Key Learnings

### Design Patterns in Practice

- **State Pattern**

  - Simplifies transitions between ride and driver states.
  - Adheres to the **Single Responsibility Principle (SRP)** by separating state-specific logic.

- **Strategy Pattern**

  - Encapsulates pricing logic to support multiple strategies.
  - Follows the **Open/Closed Principle (OCP)**, allowing new strategies without modifying existing code.

- **Dependency Injection**
  - Decouples pricing logic from the `RidesManager`, improving flexibility and testability.

---

## Possible Extensions

- Support for multiple users and concurrent ride requests.
- Advanced pricing strategies, such as distance-based or time-based pricing.
- Introduce cancellation policies and penalties.
- Add location tracking for more realistic driver assignment.
- Implement analytics for completed rides (e.g., average cost, peak hours).

---

## Conclusion

This project provides a comprehensive example of designing a simple **Ride Booking System**. It serves as a foundation for understanding **Design Patterns**, state management, and OOP principles in the context of LLD. By studying and extending this implementation, developers can enhance their design skills and gain confidence in applying patterns to solve real-world problems.
