//
// Created by Bruno Huang on 2023/10/20.
//

#include "Functions_Bruno.h"

Functions_Bruno::Functions_Bruno(ReadData datareader) {
    dataReader = datareader;
}

// Helper function to convert a string to lowercase
string Functions_Bruno::ToLower(const string& input) {
    string lowered;
    for (char c : input) {
        lowered += tolower(c);
    }
    return lowered;
}

void Functions_Bruno::ListStudentsWithSameName() {
    cout << "Enter the student you want to search for: ";
    string searchName;
    cin >> searchName;
    //searchName = ToLower(searchName);

    vector<Student> matchingStudents;

    // Search for students with the exact same name using the binary search tree
    Student* foundStudent = dataReader.students.searchByName(searchName);
    if (foundStudent != nullptr) {
        cout << "Student Name: " << foundStudent->StudentName << endl;
        cout << "Student Code: " << foundStudent->StudentCode << endl;
        cout << "Classes: " << endl;
        for (const Class& ucClass : foundStudent->UcToClasses) {
            cout << "  UC Code: " << ucClass.UcCode << ", Class Code: " << ucClass.ClassCode << endl;
        }
    } else {
        cout << "Student with name '" << searchName << "' not found." << endl;
    }
/*
    // Student not fou
    if (matchingStudents.empty()) {
        cout << "Student with name: " << searchName << " not found." << endl;
        return;
    }

    // List all students with "searchName" and allow user to select one
    //system("cls"); // Windows
    system("clear"); // Unix-like system
    cout << "\033[1mSearch criteria:\033[0m (Name: " << searchName << ")" << endl;
    cout << "\n";
    cout << "\033[1mResults of the search:\033[0m " << endl;
    for (int i = 0; i < matchingStudents.size(); i++) {
        cout << i + 1 << ". " << "Student Code: " << matchingStudents[i].StudentCode
        << "     Name: " << matchingStudents[i].StudentName << endl;
    }
    cout << "\n";

    int choice;
    while (true) {
        cout << "Enter the number of the student you want to view: ";
        cin >> choice;

        // Check if user's choice is valid
        if (choice >= 1 && choice <= matchingStudents.size()) {
            system("clear");
            break;
        }

        cout << "Invalid choice. PLease enter a valid number. " << endl << flush;
        cout << "\n";
    }

    // Output chosen student's information
    const Student chosenStudent = matchingStudents[choice - 1];
    cout << "\n";
    cout << "\033[1mSelected student information:\033[0m " << endl;
    cout << "Student Code: " << chosenStudent.StudentCode << endl;
    cout << "Student Name: " << chosenStudent.StudentName << endl;
    cout << "UCs and Classes: " << endl;
    for (const Class& ucToClass : chosenStudent.UcToClasses) {
        cout << "UcCode: " << ucToClass.UcCode  << ", ClassCode: " << ucToClass.ClassCode << endl;
    }
    cout << "\n"; */
}

int main() {
    ReadData datareader;
    Functions_Bruno functions(datareader);
    functions.ListStudentsWithSameName();
}