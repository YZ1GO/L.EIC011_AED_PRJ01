#include "Change.h"

Change::Change() {}

void Change::removeStudent(Global& global1) {
    cout << "Enter the student code of the student you want to remove: ";
    int studentCode;
    cin >> studentCode;

    global1.Students.removeStudent(studentCode);
    this->global = global1;
}

/*
int main() {

   // change.removeStudent();
    return 0;
}*/