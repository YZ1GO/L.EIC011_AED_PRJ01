#include "Change.h"

Change::Change() {}

void Change::removeStudent(Global& globalCopy) {
    cout << "Enter the student code of the student you want to remove: ";
    int studentCode;
    cin >> studentCode;

    globalCopy.Students.removeStudent(studentCode);
    this->global = globalCopy;
}

void Change::changeClass(Global& globalCopy, int studentCode, const string& ucCode, const string& newClassCode) {
    cout << "hi" << endl;
    Student* student = globalCopy.Students.searchByCode(studentCode);

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

    this->global = globalCopy;
}

