#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Structure to store student details
struct Student {
    int rollNumber;
    string name;
    float marks;
};

// Function to load student records from a text file
vector<Student> loadFromFile() {
    vector<Student> students;
    ifstream inFile("students.txt");
    if (!inFile) return students;

    Student s;
    while (inFile >> s.rollNumber) {
        inFile.ignore(); // Clear newline
        getline(inFile, s.name);
        inFile >> s.marks;
        students.push_back(s);
    }
    inFile.close();
    return students;
}

// Function to save all student records back to the text file
void saveToFile(const vector<Student>& students) {
    ofstream outFile("students.txt");
    for (const auto& s : students) {
        outFile << s.rollNumber << "\n" << s.name << "\n" << s.marks << "\n";
    }
    outFile.close();
}

// 1. Add a new student
void addStudent(vector<Student>& students) {
    Student s;
    cout << "\nEnter Roll Number: ";
    cin >> s.rollNumber;
    
    // Check if roll number already exists
    for (const auto& existing : students) {
        if (existing.rollNumber == s.rollNumber) {
            cout << "Error: Student with this Roll Number already exists!\n";
            return;
        }
    }

    cin.ignore(); // Clear input buffer
    cout << "Enter Name: ";
    getline(cin, s.name);
    
    cout << "Enter Marks: ";
    cin >> s.marks;

    students.push_back(s);
    saveToFile(students);
    cout << "Student added successfully!\n";
}

// 2. Display all student records
void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\nNo student records found!\n";
        return;
    }

    cout << "\n--- Student Records ---\n";
    for (const auto& s : students) {
        cout << "Roll No: " << s.rollNumber 
             << " | Name: " << s.name 
             << " | Marks: " << s.marks << "\n";
    }
}

// 3. Update an existing student's record
void updateStudent(vector<Student>& students) {
    int roll;
    cout << "\nEnter Roll Number to update: ";
    cin >> roll;

    for (auto& s : students) {
        if (s.rollNumber == roll) {
            cin.ignore();
            cout << "Enter New Name: ";
            getline(cin, s.name);
            cout << "Enter New Marks: ";
            cin >> s.marks;

            saveToFile(students);
            cout << "Record updated successfully!\n";
            return;
        }
    }
    cout << "Student with Roll Number " << roll << " not found.\n";
}

// 4. Delete a student record
void deleteStudent(vector<Student>& students) {
    int roll;
    cout << "\nEnter Roll Number to delete: ";
    cin >> roll;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->rollNumber == roll) {
            students.erase(it);
            saveToFile(students);
            cout << "Record deleted successfully!\n";
            return;
        }
    }
    cout << "Student with Roll Number " << roll << " not found.\n";
}

// Main Menu System
int main() {
    vector<Student> students = loadFromFile();
    int choice;

    do {
        cout << "\n===============================\n";
        cout << "  STUDENT MANAGEMENT SYSTEM    \n";
        cout << "===============================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: displayStudents(students); break;
            case 3: updateStudent(students); break;
            case 4: deleteStudent(students); break;
            case 5: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice! Please select 1 to 5.\n";
        }
    } while (choice != 5);

    return 0;
}
