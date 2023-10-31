#include "Change.h"
#include <cmath>

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

bool Change::checkIfBalanceBetweenClassesDisturbed(map<string, int> classStudentsCount, const string& oldClassCode, const string& newClassCode) {
    // Trim leading and trailing spaces from ucClass.ClassCode
    string trimmedClassCode = oldClassCode;
    trimmedClassCode.erase(trimmedClassCode.begin(), find_if(trimmedClassCode.begin(), trimmedClassCode.end(),
                                                             [](char c) { return !isspace(c); }));
    trimmedClassCode.erase(find_if(trimmedClassCode.rbegin(), trimmedClassCode.rend(),
                                   [](char c) { return !isspace(c); }).base(), trimmedClassCode.end());

    // Check if student wants to change from a bigger class to a smaller class
    if (classStudentsCount[trimmedClassCode] > classStudentsCount[newClassCode]) {
        return false;
    }

    classStudentsCount[trimmedClassCode]--;
    classStudentsCount[newClassCode]++;

    // Check if the difference in student counts exceeds 4 if student changes class
    for (const auto& it : classStudentsCount) {
        if (abs(it.second - classStudentsCount[trimmedClassCode]) > 4 || abs(it.second - classStudentsCount[newClassCode]) > 4) {
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

void Change::changeClass(Global& globalCopy, int studentCode, const string& ucCode, const string& currentClassCode, const string& newClassCode) {
    Student* student = globalCopy.Students.searchByCode(studentCode);
    bool ucAndClassFound = false;

    if (student) {
        for (Class& ucClass : student->UcToClasses) {
            if (checkIfUCCodeEqual(ucClass.UcCode, ucCode) && checkIfClassCodeEqual(ucClass.ClassCode, currentClassCode)) {
                ucAndClassFound = true;
                // Create a map to store #students in each class for a certain uc
                map<string, int> classStudentsCount;
                globalCopy.Students.getStudentsCountInClass(ucCode, classStudentsCount);

                // Check if new class code is the same as the current class code
                if (checkIfClassCodeEqual(currentClassCode, newClassCode)) {
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
                if (checkIfBalanceBetweenClassesDisturbed(classStudentsCount, currentClassCode, newClassCode)) {
                    cerr << "ERROR: Balance between classes disturbed, can't change class." << endl;
                    break; // No need to check for other rules
                }

                // Change student class to check if schedule can be built
                ucClass.ClassCode = newClassCode;

                // Check for schedule conflict
                if (!tryBuildNewSchedule(globalCopy, *student)) {
                    cerr << "ERROR: Conflict in new schedule, can't change class." << endl;
                    ucClass.ClassCode = currentClassCode; // Change back to current class
                    break;
                }

                cout << "Class changed successfully!" << endl;
                break;
            }
        }
        if (!ucAndClassFound) {
            cout << "Uc " << ucCode << " and class " << currentClassCode << " not found." << endl;
        }
    } else {
        cout << "Student not found." << endl;
    }

    this->global = globalCopy;
}

