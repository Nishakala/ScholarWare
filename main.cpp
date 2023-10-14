#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// ScholarWare - Student Information Management System
// This program allows users to manage student data by providing basic CRUD (Create, Read, Update, Delete) functionalities.
// It demonstrates the use of C++, file handling, and the Standard Template Library (STL) for data storage.
// Written by [Your Name]

class Student {
public:
    std::string name;
    int rollNumber;
};

// Function to save student data to a file
void SaveDataToFile(const std::vector<Student>& students) {
    std::ofstream outFile("students.txt");
    if (outFile.is_open()) {
        for (const Student& student : students) {
            outFile << student.name << " " << student.rollNumber << "\n";
        }
        outFile.close();
        cout << "\x1b[32mData saved to file.\x1b[0m" << endl;  // Set text color to green
    } else {
        cerr << "\x1b[31mError saving data to file.\x1b[0m" << endl;  // Set text color to red
    }
}

// Function to load student data from a file
void LoadDataFromFile(std::vector<Student>& students) {
    students.clear();
    std::ifstream inFile("students.txt");
    if (inFile.is_open()) {
        Student student;
        while (inFile >> student.name >> student.rollNumber) {
            students.push_back(student);
        }
        inFile.close();
    } else {
        cerr << "\x1b[31mFile not found or unable to open.\x1b[0m" << endl;  // Set text color to red
    }
}

int main() {
    std::vector<Student> students;
    LoadDataFromFile(students);

    int choice;
    bool found;  // Declare found outside the switch
    auto it = students.begin();  // Declare it outside the switch

    while (true) {
        cout << "\x1b[36mScholarWare Menu\x1b[0m" << endl;  // Set text color to cyan
        cout << "1. Add Student" << endl;
        cout << "2. Display Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student Record" << endl;
        cout << "5. Delete Student" << endl;
        cout << "6. Save and Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear the newline character from the input buffer

        switch (choice) {
            case 1:  // Add Student
            {
                Student newStudent;
                cout << "Enter student name: ";
                getline(cin, newStudent.name);
                cout << "Enter student roll number: ";
                cin >> newStudent.rollNumber;
                cin.ignore();  // Clear the newline character
                students.push_back(newStudent);
                cout << "\x1b[32mStudent added.\x1b[0m" << endl;  // Set text color to green
                break;
            }
            case 2:  // Display Students
                cout << "List of Students:" << endl;
                for (const Student& student : students) {
                    cout << "Name: " << student.name << ", Roll Number: " << student.rollNumber << endl;
                }
                break;
            case 3:  // Search Student
                int searchRollNumber;
                cout << "Enter roll number to search for: ";
                cin >> searchRollNumber;
                cin.ignore();  // Clear the newline character
                found = false;
                for (const Student& student : students) {
                    if (student.rollNumber == searchRollNumber) {
                        cout << "Student found: Name: " << student.name << ", Roll Number: " << student.rollNumber << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\x1b[31mStudent not found.\x1b[0m" << endl;  // Set text color to red
                }
                break;
            case 4:  // Update Student Record
                int updateRollNumber;
                cout << "Enter roll number to update: ";
                cin >> updateRollNumber;
                cin.ignore();  // Clear the newline character
                found = false;
                for (Student& student : students) {
                    if (student.rollNumber == updateRollNumber) {
                        cout << "Enter new student name: ";
                        getline(cin, student.name);
                        cout << "\x1b[32mStudent record updated.\x1b[0m" << endl;  // Set text color to green
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "\x1b[31mStudent not found.\x1b[0m" << endl;  // Set text color to red
                }
                break;
            case 5:  // Delete Student
                int deleteRollNumber;
                cout << "Enter roll number to delete: ";
                cin >> deleteRollNumber;
                cin.ignore();  // Clear the newline character
                found = false;
                it = students.begin();  // Initialize it before use
                while (it != students.end()) {
                    if (it->rollNumber == deleteRollNumber) {
                        it = students.erase(it);
                        cout << "\x1b[32mStudent deleted.\x1b[0m" << endl;  // Set text color to green
                        found = true;
                    } else {
                        ++it;
                    }
                }
                if (!found) {
                    cout << "\x1b[31mStudent not found.\x1b[0m" << endl;  // Set text color to red
                }
                break;

            case 6:  // Save and Exit
                SaveDataToFile(students);
                return 0;
            default:
                cout << "\x1b[31mInvalid choice. Please try again.\x1b[0m" << endl;  // Set text color to red
        }
    }

    return 0;
}
