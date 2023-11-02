#include "Change.h"
#include <cmath>

Change::Change(Global& globalCopy) : global(globalCopy) {}

bool Change::checkIfClassCapacityExceeds(map<string, int> classStudentsCount, const string& newClassCode) {
    int cap = 26;
    return classStudentsCount[newClassCode]++ > cap;
}

bool Change::checkIfBalanceBetweenClassesDisturbed(map<string, int> classStudentsCount, const string& oldClassCode, const string& newClassCode) {
    // Check if student wants to change from a bigger class to a smaller class
    if (classStudentsCount[oldClassCode] > classStudentsCount[newClassCode]) {
        return false;
    }

    classStudentsCount[oldClassCode]--;
    classStudentsCount[newClassCode]++;

    // Check if the difference in student counts exceeds 4 if student changes class
    for (const auto& it : classStudentsCount) {
        if (abs(it.second - classStudentsCount[oldClassCode]) > 4 || abs(it.second - classStudentsCount[newClassCode]) > 4) {
            cout << "   " << oldClassCode << " class has " << classStudentsCount[oldClassCode] << " students." << endl;
            cout << "   " << newClassCode << " class has " << classStudentsCount[newClassCode] << " students." << endl;
            return true;
        }
    }

    return false;
}

bool Change::tryBuildNewSchedule(const Student& student) {
    Consult consult(global);
    vector<Schedule> studentSchedule = consult.getStudentSchedule(student);

    vector<Schedule> conflictingClasses; // Stores classes with schedule conflicts

    for (size_t i = 0; i < studentSchedule.size(); i++) {
        for (size_t j = i + 1; j < studentSchedule.size(); j++) {
            const Schedule& schedule1 = studentSchedule[i];
            const Schedule& schedule2 = studentSchedule[j];

            if (schedule1.WeekDay == schedule2.WeekDay) {
                if (schedule1.Type == "T" || schedule2.Type == "T") {
                    continue;
                }
                // Check for non-T classes that overlap
                if (!(schedule1.StartHour + schedule1.Duration <= schedule2.StartHour ||
                      schedule2.StartHour + schedule2.Duration <= schedule1.StartHour)) {
                    conflictingClasses.push_back(schedule1);
                    conflictingClasses.push_back(schedule2);
                }
            }
        }
    }

    if (!conflictingClasses.empty()) {
        cout << "Classes with schedule conflicts: " << endl;
        for (const Schedule& schedule : conflictingClasses) {
            cout << "   UC Code: " << schedule.UcToClasses.UcCode << ", Class Code: " << schedule.UcToClasses.ClassCode << ", Weekday: " << schedule.WeekDay << ", Start Hour: " << schedule.StartHour << ", Duration: " << schedule.Duration << ", Type: " << schedule.Type << endl;
        }
        return false; // Can't build schedule
    }

    return true; // Can build schedule
}

void Change::changeClass(int studentCode, const string& ucCode, const string& currentClassCode, const string& newClassCode) {
    Student* student = this->global.Students.searchByCode(studentCode);

    //register change log
    logEntry.requestType = "Change Class";
    logEntry.timestamp = getCurrentTimestamp(); //defined in UtilityFunctions
    logEntry.studentCode = studentCode;
    logEntry.currentUcCode = ucCode;
    logEntry.currentClassCode = currentClassCode;
    logEntry.newUcCode = ucCode;
    logEntry.newClassCode = newClassCode;

    cout << "[from " << ucCode << " , " << currentClassCode << " to " << newClassCode << "]:" << endl;
    cout << "   Requester Student: " << studentCode << " , " << student->StudentName << endl;

    bool ucAndClassFound = false;

    if (student) {
        for (Class& ucClass : student->UcToClasses) {
            if (ucClass.UcCode == ucCode) {
                ucAndClassFound = true;
                // Create a map to store #students in each class for a certain uc
                map<string, int> classStudentsCount;
                this->global.Students.getStudentsCountInClass(ucCode, classStudentsCount);

                // Check if new class code is the same as the current class code
                if (currentClassCode == newClassCode) {
                    cerr << "FAILED: Student already in " << newClassCode << endl;
                    logEntry.accepted = false;
                    logEntry.extraNotes = "Student already in" + newClassCode;
                    break;
                }

                // Check if new class code is valid
                if (classStudentsCount.find(newClassCode) == classStudentsCount.end()) {
                    cerr << "FAILED: Invalid new class code, please try a different class." << endl;
                    logEntry.accepted = false;
                    logEntry.extraNotes = "Invalid new class code";
                    break;
                }

                // Check if capacity exceeds
                if (checkIfClassCapacityExceeds(classStudentsCount, newClassCode)) {
                    cerr << "FAILED: Class capacity exceeded, can't change class." << endl;
                    logEntry.accepted = false;
                    logEntry.extraNotes = "Class capacity exceeded (max 26 students per class)";
                    break; // No need to check for other rules
                }

                //Check if class balance is disturbed
                if (checkIfBalanceBetweenClassesDisturbed(classStudentsCount, currentClassCode, newClassCode)) {
                    cout << currentClassCode << " and " << newClassCode << endl;
                    cerr << "FAILED: Balance between classes disturbed, can't change class." << endl;
                    logEntry.accepted = false;
                    logEntry.extraNotes = "Balance between classes disturbed";
                    break; // No need to check for other rules
                }

                // Change student class to check if schedule can be built
                ucClass.ClassCode = newClassCode;

                // Check for schedule conflict
                if (!tryBuildNewSchedule(*student)) {
                    cerr << "FAILED: Conflict in new schedule, can't change class." << endl;
                    logEntry.accepted = false;
                    logEntry.extraNotes = "Conflict in new schedule";
                    ucClass.ClassCode = currentClassCode; // Change back to current class
                    break;
                }
                cout << "Class changed successfully!" << endl;
                logEntry.accepted = true;
                break;
            }
        }
        if (!ucAndClassFound) {
            cout << "FAILED: Uc " << ucCode << " and class " << currentClassCode << " not found in students classes." << endl;
            logEntry.accepted = false;
            logEntry.extraNotes = "Uc " + ucCode + " and class " + currentClassCode + " not found in students classes";
        }
    } else {
        cout << "FAILED: Student not found." << endl;
    }
}

bool Change::checkIfCanJoinNewUC(const Student& student) {
    return student.UcToClasses.size() < 7;
}

map<string, int> Change::classesWithVacancyInNewUC(const Student& student, const string& newUcCode) {
    int cap = 26;

    // Create a map to store #students in each class for a certain uc
    map<string, int> classStudentsCount;
    this->global.Students.getStudentsCountInClass(newUcCode, classStudentsCount);

    map<string, int> classesWithVacancy;

    for (const auto& it : classStudentsCount) {
        if (it.second < cap) {
            classesWithVacancy[it.first] = it.second;
        }
    }

    return classesWithVacancy;
}

void Change::changeUC(int studentCode, const string& currentUcCode, const string& currentClassCode, const string& newUcCode) {
    Student* student = this->global.Students.searchByCode(studentCode);

    //register change log
    logEntry.requestType = "Change UC";
    logEntry.timestamp = getCurrentTimestamp(); //defined in UtilityFunctions
    logEntry.studentCode = studentCode;
    logEntry.currentUcCode = currentUcCode;
    logEntry.currentClassCode = currentClassCode;
    logEntry.newUcCode = newUcCode;
    logEntry.newClassCode = "-";

    cout << "[from " << currentUcCode << "]:" << endl;
    cout << "   Requester Student: " << studentCode << " , " << student->StudentName << endl;

    bool ucAndClassFound = false;
    bool ucAndClassChanged = false;

    if (student) {
        for (Class& ucClass : student->UcToClasses) {
            // Check if new uc code is the same as the current uc code
            if (ucClass.UcCode == newUcCode) {
                cerr << "FAILED: Student already in " << newUcCode << endl;
                logEntry.accepted = false;
                logEntry.extraNotes = "Student already in";
                return;
            }
        }
        for (Class& ucClass : student->UcToClasses) {
            if (ucClass.UcCode == currentUcCode && ucClass.ClassCode == currentClassCode) {
                ucAndClassFound = true;

                map<string, int> classesWithVacancy = classesWithVacancyInNewUC(*student, newUcCode);

                if (classesWithVacancy.empty()) {
                    cerr << "FAILED: No class with vacancy in the new UC or UC doesn't exist" << endl;
                    logEntry.accepted = false;
                    logEntry.extraNotes = "No class with vacancy in the new UC or UC doesn't exist";
                    return;
                }
                ucClass.UcCode = newUcCode;

                vector<pair<string, int>> sortedClasses(classesWithVacancy.begin(), classesWithVacancy.end());
                sort(sortedClasses.begin(), sortedClasses.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
                    return a.second < b.second;
                });

                for (const auto& entry: sortedClasses) {
                    ucClass.ClassCode = entry.first;
                    if (tryBuildNewSchedule(*student)) {
                        cout << "UC and class changed successfully!" << endl;
                        ucAndClassChanged = true;
                        logEntry.accepted = true;
                        logEntry.newClassCode = entry.first;
                        break;
                    }
                    else {
                        cerr << "FAILED: Conflict in new schedule, can't change" << endl;
                        logEntry.accepted = false;
                        logEntry.extraNotes = "Conflict in new schedule";
                    }
                }

                if (!ucAndClassChanged) {
                    ucClass.UcCode = currentUcCode;
                    ucClass.ClassCode = currentClassCode;
                    cout << "FAILED: Cannot change UC." << endl;
                }
            }
        }
        if (!ucAndClassFound) {
            cout << "FAILED: Uc not found." << endl;
            logEntry.accepted = false;
            logEntry.extraNotes = "Uc not found";
        }
    } else {
        cout << "FAILED: Student not found." << endl;
    }
}

void Change::leaveUCAndClass(int studentCode, const string& ucCode, const string& classCode) {
    Student* student = this->global.Students.searchByCode(studentCode);

    //register change log
    logEntry.requestType = "Leave UC and Class";
    logEntry.timestamp = getCurrentTimestamp(); //defined in UtilityFunctions
    logEntry.studentCode = studentCode;
    logEntry.currentUcCode = ucCode;
    logEntry.currentClassCode = classCode;
    logEntry.newUcCode = "-";
    logEntry.newClassCode = "-";

    cout << "[from " << ucCode << " , " << classCode << "]:" << endl;
    cout << "   Requester Student: " << studentCode << " , " << student->StudentName << endl;

    if (student) {
        bool removed = false; // Variable to track if a UC and class have been removed

        // Iterate through the classes in student->UcToClasses
        for (auto it = student->UcToClasses.begin(); it != student->UcToClasses.end(); ++it) {
            // Check if the ucClass matches the provided ucCode and classCode
            if (it->UcCode == ucCode && it->ClassCode == classCode) {
                // Remove the matched class
                student->UcToClasses.erase(it);
                cout << "UC and class removed successfully!" << endl;
                removed = true; // Set the flag to indicate removal
                logEntry.accepted = true;
                break; // Exit the loop after removing one UC and class
            }
        }

        if (!removed) {
            cout << "FAILED: No matching UC and class found for removal." << endl;
            logEntry.accepted = false;
        }
    } else {
        cerr << "Student not found." << endl;
    }
}

void Change::joinUCAndClass(int studentCode, const string& newUcCode) {
    Student* student = this->global.Students.searchByCode(studentCode);

    //register change log
    logEntry.requestType = "Leave UC and Class";
    logEntry.timestamp = getCurrentTimestamp(); //defined in UtilityFunctions
    logEntry.studentCode = studentCode;
    logEntry.currentUcCode = "-";
    logEntry.currentClassCode = "-";
    logEntry.newUcCode = newUcCode;
    logEntry.newClassCode = "-";

    cout << "[to " << newUcCode << "]:" << endl;
    cout << "   Requester Student: " << studentCode << " , " << student->StudentName << endl;

    bool ucAndClassAdded = false;

    if (student) {
        // Check if student will be registered in more than 7 UCs
        if (!checkIfCanJoinNewUC(*student)) {
            cerr << "FAILED: Maximum number of UCs will exceed (max: 7 UCs)." << endl;
            logEntry.accepted = false;
            logEntry.extraNotes = "Maximum number of UCs will exceed (max 7 UCs)";
            return;
        }

        // Check if the provided UC code exists in the system
        bool ucFound = false;

        for (const auto ucClass : this->global.Classes) {
            if (ucClass.UcCode == newUcCode) {
                ucFound = true;
                break;
            }
        }
        if (!ucFound) {
            return;
        }

        for (const Class& ucClass : student->UcToClasses) {
            if (ucClass.UcCode == newUcCode) {
                cout << "FAILED: Student is already registered in " << newUcCode << endl;
                logEntry.accepted = false;
                logEntry.extraNotes = "Student is already registered in";
                return;
            }
        }

        map<string, int> classesWithVacancy = classesWithVacancyInNewUC(*student, newUcCode);

        if (classesWithVacancy.empty()) {
            cerr << "FAILED: No class with vacancy in the new UC." << endl;
            logEntry.accepted = false;
            logEntry.extraNotes = "No class with vacancy in the new UC";
            return;
        }

        vector<pair<string, int>> sortedClasses(classesWithVacancy.begin(), classesWithVacancy.end());
        sort(sortedClasses.begin(), sortedClasses.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        });

        for (const auto& entry: sortedClasses) {
            Class newClass = Class(newUcCode, entry.first);
            student->UcToClasses.push_back(newClass);
            if (tryBuildNewSchedule(*student)) {
                cout << "UC and class added successfully!" << endl;
                ucAndClassAdded = true;
                logEntry.newClassCode = entry.first;
                logEntry.accepted = true;
                break;
            } else {
                // Find the iterator pointing to the newly added class
                auto it = student->UcToClasses.end() - 1;
                student->UcToClasses.erase(it);  // Erase the last added class
                cerr << "FAILED: Conflict in new schedule , can't join" << endl;
                logEntry.accepted = false;
                logEntry.extraNotes = "Conflict in new schedule";
            }
        }
        if (!ucAndClassAdded) {
            cerr << "FAILED: No matching UC and class found for adding." << endl;
            logEntry.accepted = false;
            logEntry.extraNotes = "No matching UC and class found for adding";
        }
    } else {
        cerr << "FAILED: Student not found." << endl;
    }
}