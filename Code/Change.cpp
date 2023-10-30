#include "Change.h"

Change::Change() {}

void Change::removeStudent(Global& globalCopy) {
    cout << "Enter the student code of the student you want to remove: ";
    int studentCode;
    cin >> studentCode;

    globalCopy.Students.removeStudent(studentCode);
    this->global = globalCopy;
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

    string previousClassCode;

    if (student) {
        for (Class& ucClass : student->UcToClasses) {
            if (checkIfUCCodeEqual(ucClass.UcCode, ucCode)) {
                previousClassCode = ucClass.ClassCode;
                ucClass.ClassCode = newClassCode;
                // Check for schedule conflict
                if (!tryBuildNewSchedule(globalCopy, *student)) {
                    ucClass.ClassCode = previousClassCode;
                    cerr << "ERROR: Conflict in new schedule, undoing action." << endl;
                }
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

