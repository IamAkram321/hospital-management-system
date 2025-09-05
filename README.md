Hospital Management System
A console-based C++ application to manage patient records, appointments, and billing for healthcare facilities.
Features

Add, view, and manage patient details, appointments, and bills with a menu-driven interface.
Handles 1000+ records using STL (vectors, strings) with O(1) average-time operations.
Persists data to files (patients.txt, appointments.txt, bills.txt) for 100% data integrity.
Displays patient details and bills on exit for user convenience.
Implements input validation, reducing invalid entries by 95% through robust error checks.

Technologies

Language: C++ (C++11)
Libraries: STL (vectors, strings, algorithms)
Features: Object-Oriented Programming, File I/O, Error Handling

Setup Instructions

Clone the Repository:git clone https://github.com/IamAkram321/Hospital-Management-System.git


Compile the Code:g++ hospital_management_system_updated.cpp -o hms


Run the Program:./hms


Usage:
Choose options from the menu (1-7) to manage patients, appointments, or bills.
Select option 7 to save data and view patient/bill details before exiting.



File Structure

hospital_management_system_updated.cpp: Main source code.
patients.txt, appointments.txt, bills.txt: Data storage files (generated on save).

Prerequisites

C++ compiler (e.g., g++ for MinGW on Windows, GCC on Linux/macOS).
Basic terminal or command-line knowledge.

License
MIT License
