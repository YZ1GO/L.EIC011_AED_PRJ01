#include "Change.h"

Change::Change() {}

void Change::removeStudent(Global& globalCopy) {
    cout << "Enter the student code of the student you want to remove: ";
    int studentCode;
    cin >> studentCode;

    globalCopy.Students.removeStudent(studentCode);
    this->global = globalCopy;
}

bool Change::checkIfClassCapacityExceeds(const Global& globalCopy, map<string, int> classStudentsCount, const string& newClassCode) {
    int cap = 26;
    return classStudentsCount[newClassCode]++ > cap;
}

bool Change::checkIfBalanceBetweenClassesDisturbed(const Global& globalCopy, map<string, int> classStudentsCount, const string& oldClassCode, const string& newClassCode) {
    // Check if student wants to change from a bigger class to a smaller class
    if (classStudentsCount[oldClassCode] > classStudentsCount[newClassCode]) {
        return false;
    }

    for (const auto& it : classStudentsCount) {
        cout << "Class: " << it.first << ", Count: " << it.second << endl;
        // Check if the difference in student counts exceeds 4
        if (abs(it.second - classStudentsCount[oldClassCode]) > 4 || abs(it.second - classStudentsCount[newClassCode]) > 4) {
            cout << "Class: " << it.first << ", Count: " << it.second << endl;
            cout << abs(it.second - classStudentsCount[oldClassCode]) << endl;
            cout << "OldClass: " << oldClassCode << " Count: " << classStudentsCount[oldClassCode] << endl;
            return true;
        }
    }

    return false;
}

void Change::getStudentSchedule(const Global& globalCopy, const Student& student, vector<Schedule>& studentSchedule) {
    // Iterate through the classes for this student
    for (const Class& studentClass: student.UcToClasses) {
        for (const Schedule& schedule: globalCopy.Schedules) {
            if (checkIfClassCodeEqual(studentClass.ClassCode, schedule.UcToClasses.ClassCode)
                && checkIfUCCodeEqual(studentClass.UcCode, schedule.UcToClasses.UcCode)) {
                studentSchedule.push_back(schedule);
            }
        }
    }
    sort(studentSchedule.begin(), studentSchedule.end());
}

bool Change::tryBuildNewSchedule(const Global& globalCopy, const Student& student) {
    vector<Schedule> studentSchedule;
    getStudentSchedule(globalCopy, student, studentSchedule);

    for (size_t i = 0; i < studentSchedule.size(); i++) {
        for (size_t j = i + 1; j < studentSchedule.size(); j++) {
            const Schedule& schedule1 = studentSchedule[i];
            const Schedule& schedule2 = studentSchedule[j];

            if (schedule1.WeekDay == schedule2.WeekDay &&
                !(schedule1.StartHour + schedule1.Duration <= schedule2.StartHour ||
                  schedule2.StartHour + schedule2.Duration <= schedule1.StartHour)) {
                return false; // Can't build schedule
            }
        }
    }

    return true; // Can build schedule
}

void Change::changeClass(Global& globalCopy, int studentCode, const string& ucCode, const string& newClassCode) {
    Student* student = globalCopy.Students.searchByCode(studentCode);


    if (student) {
        for (Class& ucClass : student->UcToClasses) {
            if (checkIfUCCodeEqual(ucClass.UcCode, ucCode)) {
                cout << "Found student and matching ucClass." << endl;

                // Create a map to store #students in each class for a certain uc
                map<string, int> classStudentsCount;
                globalCopy.Students.getStudentsCountInClass(ucClass.UcCode, classStudentsCount);

                // Check if new class code is the same as the current class code
                if (checkIfClassCodeEqual(ucClass.ClassCode, newClassCode)) {
                    cerr << "ERROR: Student already in " << newClassCode << endl;
                    break;
                }

                // Check if new class code is valid
                if (classStudentsCount.find(newClassCode) == classStudentsCount.end()) {
                    cerr << "ERROR: Invalid new class code, please try a different class.";
                    break;
                }

                // Check if capacity exceeds
                if (checkIfClassCapacityExceeds(globalCopy, classStudentsCount, newClassCode)) {
                    cerr << "ERROR: Class capacity exceeded, can't change class." << endl;
                    break; // No need to check for other rules
                }

                //Check if class balance is disturbed
                if (checkIfBalanceBetweenClassesDisturbed(globalCopy, classStudentsCount, ucClass.ClassCode, newClassCode)) {
                    // Add debug prints to display variable values
                    cout << "Old class code: " << ucClass.ClassCode << endl;
                    cout << "New class code: " << newClassCode << endl;
                    cerr << "ERROR: Balance between classes disturbed, undoing action." << endl;
                    break; // No need to check for other rules
                } else {
                    continue;
                }

                // Check for schedule conflict
                if (!tryBuildNewSchedule(globalCopy, *student)) {
                    cerr << "ERROR: Conflict in new schedule, undoing action." << endl;
                    break;
                }

                ucClass.ClassCode = newClassCode;
                cout << "Class changed successfully!" << endl;
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

