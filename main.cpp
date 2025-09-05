#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;

// Class to represent a Patient
class Patient {
public:
    string id;
    string name;
    int age;
    string contact;

    Patient(string id, string name, int age, string contact) 
        : id(id), name(name), age(age), contact(contact) {}

    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Age: " << age << ", Contact: " << contact << endl;
    }
};

// Class to represent an Appointment
class Appointment {
public:
    string patientId;
    string doctorName;
    string date;
    string time;

    Appointment(string patientId, string doctorName, string date, string time)
        : patientId(patientId), doctorName(doctorName), date(date), time(time) {}

    void display() const {
        cout << "Patient ID: " << patientId << ", Doctor: " << doctorName 
             << ", Date: " << date << ", Time: " << time << endl;
    }
};

// Class to represent a Bill
class Bill {
public:
    string patientId;
    double amount;
    string date;

    Bill(string patientId, double amount, string date)
        : patientId(patientId), amount(amount), date(date) {}

    void display() const {
        cout << "Patient ID: " << patientId << ", Amount: $" << amount 
             << ", Date: " << date << endl;
    }
};

// Class to manage the Hospital Management System
class HospitalManagementSystem {
private:
    vector<Patient> patients;
    vector<Appointment> appointments;
    vector<Bill> bills;

    // Helper function to get current date
    string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[11];
        sprintf(buffer, "%02d-%02d-%04d", ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
        return string(buffer);
    }

    // Helper function to check if patient exists
    bool patientExists(string id) {
        return find_if(patients.begin(), patients.end(), 
            [id](const Patient& p) { return p.id == id; }) != patients.end();
    }

public:
    // Adding a new patient
    void addPatient(string id, string name, int age, string contact) {
        if (patientExists(id)) {
            cout << "Error: Patient ID already exists.\n";
            return;
        }
        if (age <= 0 || name.empty() || contact.empty()) {
            cout << "Error: Invalid patient details.\n";
            return;
        }
        patients.emplace_back(id, name, age, contact);
        cout << "Patient added successfully.\n";
    }

    // Scheduling an appointment
    void scheduleAppointment(string patientId, string doctorName, string date, string time) {
        if (!patientExists(patientId)) {
            cout << "Error: Patient ID does not exist.\n";
            return;
        }
        if (doctorName.empty() || date.empty() || time.empty()) {
            cout << "Error: Invalid appointment details.\n";
            return;
        }
        appointments.emplace_back(patientId, doctorName, date, time);
        cout << "Appointment scheduled successfully.\n";
    }

    // Generating a bill
    void generateBill(string patientId, double amount) {
        if (!patientExists(patientId)) {
            cout << "Error: Patient ID does not exist.\n";
            return;
        }
        if (amount <= 0) {
            cout << "Error: Invalid bill amount.\n";
            return;
        }
        bills.emplace_back(patientId, amount, getCurrentDate());
        cout << "Bill generated successfully.\n";
    }

    // Displaying all patients
    void displayPatients() {
        if (patients.empty()) {
            cout << "No patients found.\n";
            return;
        }
        cout << "\n--- Patient List ---\n";
        for (const auto& patient : patients) {
            patient.display();
        }
    }

    // Displaying all appointments
    void displayAppointments() {
        if (appointments.empty()) {
            cout << "No appointments found.\n";
            return;
        }
        cout << "\n--- Appointment List ---\n";
        for (const auto& appointment : appointments) {
            appointment.display();
        }
    }

    // Displaying all bills
    void displayBills() {
        if (bills.empty()) {
            cout << "No bills found.\n";
            return;
        }
        cout << "\n--- Bill List ---\n";
        for (const auto& bill : bills) {
            bill.display();
        }
    }

    // Saving data to files
    void saveToFile() {
        ofstream patientFile("patients.txt");
        for (const auto& patient : patients) {
            patientFile << patient.id << "," << patient.name << "," 
                        << patient.age << "," << patient.contact << "\n";
        }
        patientFile.close();

        ofstream appointmentFile("appointments.txt");
        for (const auto& appointment : appointments) {
            appointmentFile << appointment.patientId << "," << appointment.doctorName 
                           << "," << appointment.date << "," << appointment.time << "\n";
        }
        appointmentFile.close();

        ofstream billFile("bills.txt");
        for (const auto& bill : bills) {
            billFile << bill.patientId << "," << bill.amount << "," << bill.date << "\n";
        }
        billFile.close();
        cout << "Data saved to files successfully.\n";
    }

    // Load data from files
    void loadFromFile() {
        ifstream patientFile("patients.txt");
        string id, name, contact;
        int age;
        string line;
        while (getline(patientFile, line)) {
            size_t pos = 0;
            string token;
            vector<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);
            if (tokens.size() == 4) {
                id = tokens[0];
                name = tokens[1];
                age = stoi(tokens[2]);
                contact = tokens[3];
                patients.emplace_back(id, name, age, contact);
            }
        }
        patientFile.close();

        ifstream appointmentFile("appointments.txt");
        while (getline(appointmentFile, line)) {
            size_t pos = 0;
            string token;
            vector<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);
            if (tokens.size() == 4) {
                appointments.emplace_back(tokens[0], tokens[1], tokens[2], tokens[3]);
            }
        }
        appointmentFile.close();

        ifstream billFile("bills.txt");
        while (getline(billFile, line)) {
            size_t pos = 0;
            string token;
            vector<string> tokens;
            while ((pos = line.find(',')) != string::npos) {
                token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);
            if (tokens.size() == 3) {
                bills.emplace_back(tokens[0], stod(tokens[1]), tokens[2]);
            }
        }
        billFile.close();
        cout << "Data loaded from files successfully.\n";
    }
};



int main() {
    HospitalManagementSystem hms;
    hms.loadFromFile();
    int choice;
    string id, name, contact, doctorName, date, time;
    int age;
    double amount;

    while (true) {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Add Patient\n2. Schedule Appointment\n3. Generate Bill\n";
        cout << "4. Display Patients\n5. Display Appointments\n6. Display Bills\n";
        cout << "7. Save and Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter Patient ID: ";
                getline(cin, id);
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter Contact: ";
                getline(cin, contact);
                hms.addPatient(id, name, age, contact);
                break;

            case 2:
                cout << "Enter Patient ID: ";
                getline(cin, id);
                cout << "Enter Doctor Name: ";
                getline(cin, doctorName);
                cout << "Enter Date (DD-MM-YYYY): ";
                getline(cin, date);
                cout << "Enter Time (HH:MM): ";
                getline(cin, time);
                hms.scheduleAppointment(id, doctorName, date, time);
                break;

            case 3:
                cout << "Enter Patient ID: ";
                getline(cin, id);
                cout << "Enter Bill Amount: ";
                cin >> amount;
                hms.generateBill(id, amount);
                break;

            case 4:
                hms.displayPatients();
                break;

            case 5:
                hms.displayAppointments();
                break;

            case 6:
                hms.displayBills();
                break;

            case 7:
                hms.saveToFile();
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}