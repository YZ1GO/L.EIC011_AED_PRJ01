#include "Change.h"

Change::Change() {}

void Change::removeStudent(Global& global1) {
    cout << "Enter the student code of the student you want to remove: ";
    int studentCode;
    cin >> studentCode;

    global1.Students.removeStudent(studentCode);
    this->global = global1;
}

void Change::changeClass(Global& global1, int studentCode, const string& ucCode, const string& newClassCode) {
    Student* student = global1.Students.searchByCode(studentCode);

    if (student) {
        for (Class& ucClass : student->UcToClasses) {
            if (checkIfUCCodeEqual(ucClass.UcCode, ucCode)) {
                ucClass.ClassCode = newClassCode;
                cout << "Changed from " << ucClass.ClassCode << " to " << newClassCode << "." << endl;
                break;
            } else {
                cout << ucCode << " not found." << endl;
            }
        }
    } else {
        cout << "Student with code: " << studentCode << " not found." << endl;
    }

    this->global = global1;
}

