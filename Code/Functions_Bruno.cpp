//
// Created by Bruno Huang on 2023/10/20.
//

#include "Functions_Bruno.h"

Functions_Bruno::Functions_Bruno(ReadData datareader) {
    dataReader = datareader;
}

void Functions_Bruno::ListStudentsWithSameName(const string& searchName) {
    vector<Student> matchingStudents;

    // Find all students with the same name
    for (const Student& student : dataReader.students) {
        if (student.StudentName == searchName) {
            matchingStudents.push_back(student);
        }
    }

    // Student not found
    if (matchingStudents.empty()) {
        cout << "Student with name: " << searchName << " not found." << endl;
        return;
    }

    // List all students with "searchName" and allow user to select one
    cout << "\033[1mSearch criteria\033[0m: (Name: " << searchName << ")" << endl;
    cout << "\n";
    cout << "Results of the search: " << endl;
    for (int i = 0; i < matchingStudents.size(); i++) {
        cout << i + 1 << ". " << "Student Code: " << matchingStudents[i].StudentCode
        << " Name: " << matchingStudents[i].StudentName << endl;
    }

    cout << "Enter the number of the student you want to view: ";
    int choice;
    cin >> choice;

    // Check if user's choice is valid
    if (choice < 1 || choice > matchingStudents.size()) {
        cout << "Invalid choice. PLease enter a valid number. " << endl;
        return;
    }

    const Student chosenStudent = matchingStudents[choice - 1];
    cout << "Selected student information: " << endl;
    cout << "Student Code: " << chosenStudent.StudentCode << endl;
    cout << "Student Name: " << chosenStudent.StudentName << endl;
    cout << "UCs and Classes: " << endl;
    for (const Class& ucToClass : chosenStudent.UcToClasses) {
        cout << "UcCode: " << ucToClass.UcCode  << ", ClassCode: " << ucToClass.ClassCode << endl;
    }
}

int main() {
    ReadData datareader;
    Functions_Bruno functions(datareader);
    string searchName = "Oceano";
    functions.ListStudentsWithSameName(searchName);
}