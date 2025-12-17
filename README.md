# Car-Service-Booking-System-C-
Car Service Booking System developed using C++

# Car Service Booking System (C++)

## Overview
The **Car Service Booking System** is a console-based C++ application designed to manage vehicle service bookings.  
It supports **customer profile management**, **service booking**, and **staff operations** such as viewing bookings by date and exporting data.

The system demonstrates object-oriented programming concepts, input validation, file handling, and role-based access control.

---

## Features

### Customer Features
- Create and edit customer profiles
- Book vehicle service appointments
- View existing bookings using vehicle number
- Cancel bookings using reference number

### Staff Features
- Secure staff login (username & password)
- Create customer profiles
- Create and cancel bookings
- View bookings by **date and location**
- Export all bookings to a text file
- Staff activity logging

---

## Technologies Used
- **Language:** C++
- **Standard:** C++11 or later
- **Libraries:**
  - `<vector>` for dynamic data storage
  - `<regex>` for input validation
  - `<fstream>` for file handling
  - `<algorithm>` for searching and filtering
  - `<ctime>` for logging timestamps

---

## System Design
The application follows an **object-oriented design**:

- `Customer`  
  Stores customer and vehicle details and supports profile editing.

- `Booking`  
  Represents a service booking with date, time, location, and reference number.

- `BookingSystem`  
  Core business logic for managing customers, bookings, validation, and file export.

- `UserInterface`  
  Handles menus, user interaction, and staff activity logging.

---

## Validation Rules
- **Phone number:** Must be exactly 10 digits
- **Date format:** `YYYY-MM-DD` (Year ≥ 2025)
- **Time slots:** Between `09:00` and `14:59`
- **Duplicate bookings:** Same date, time, and location are not allowed

---

## How to Build

### Using g++ (Linux / macOS / Windows with MinGW)
```bash
g++ -std=c++11 main.cpp -o booking_system
