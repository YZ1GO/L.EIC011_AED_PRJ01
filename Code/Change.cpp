/**
 * @file Change.cpp
 * @brief Implementation of the Change class that handles student class and UC changes.
 */

#include "Change.h"
#include <cmath>

/**
 * @brief Constructor for the Change class.
 *
 * @param globalCopy A reference to the Global object used for student data.
 */
Change::Change(Global& globalCopy) : global(globalCopy) {}

/**
 * @brief Checks if adding a student to a class exceeds its capacity.
 *
 * @param classStudentsCount A map containing the current student count for each class.
 * @param newClassCode The class code to check.
 * @return True if the class capacity is exceeded, otherwise false.
 */
bool Change::checkIfClassCapacityExceeds(map<string, int> classStudentsCount, const string& newClassCode) {
    int cap = 26;
    int newCount = classStudentsCount[newClassCode]++;
    return newCount > cap;
}

/**
 * @brief Checks if changing a student's class would disturb the balance between classes in a UC.
 *
 * @param classStudentsCount A map containing the current student count for each class in the UC.
 * @param currentUcCode The current UC code of the student.
 * @param oldClassCode The current class code of the student.
 * @param newClassCode The new class code to change to.
 * @return True if the balance between classes would be disturbed, otherwise false.
 */
bool Change::checkIfBalanceBetweenClassesDisturbed(map<string, int> classStudentsCount, const string& currentUcCode, const string& oldClassCode, const string& newClassCode) {
    // Check if student wants to change from a bigger class to a smaller class
    if (classStudentsCount[oldClassCode] > classStudentsCount[newClassCode]) {
        return false;
    }

    // Suppose student changes class
    classStudentsCount[oldClassCode]--;
    classStudentsCount[newClassCode]++;

    // Check if the difference in student counts exceeds 4 if student changes class
    for (const auto& it : classStudentsCount) {
        if (abs(it.second - classStudentsCount[oldClassCode]) > 4 || abs(it.second - classStudentsCount[newClassCode]) > 4) {
            cout << "   " << "In " << currentUcCode << ": " << endl;
            cout << "   " << it.first << " class has " << it.second << " students." << endl;
            cout << "   " << oldClassCode << " class will have " << classStudentsCount[oldClassCode] << " students." << endl;
            cout << "   " << newClassCode << " class will have " << classStudentsCount[newClassCode] << " students." << endl;
            return true;
        }
    }

    return false;
}

/**
 * @brief Attempts to build a new schedule for a student after a class change.
 *
 * @param student The student for whom the schedule is built.
 * @return True if the schedule can be built without conflicts, otherwise false.
 */
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

/**
 * @brief Changes the class of a student.
 *
 * Checks for all rules before changing a class, if it passes class is changed, otherwise the request is denied.
 *
 * @param student The student for whom the class is changed.
 * @param currentUcCode The current UC code of the student.
 * @param currentClassCode The current class code of the student.
 * @param newClassCode The new class code to change to.
 */
void Change::changeClass(Student& student, const string& currentUcCode, const string& currentClassCode, const string& newClassCode) {
    //register change log
    logEntry.requestType = "Change Class";
    logEntry.timestamp = getCurrentTimestamp(); //defined in UtilityFunctions
    logEntry.studentCode = student.StudentCode;
    logEntry.studentName = student.StudentName;
    logEntry.currentUcCode = currentUcCode;
    logEntry.currentClassCode = currentClassCode;
    logEntry.newUcCode = currentUcCode;
    logEntry.newClassCode = newClassCode;

    cout << "[from " << currentUcCode << " , " << currentClassCode << " to " << newClassCode << "]:" << endl;
    cout << "   Requester Student: " << student.StudentCode << " , " << student.StudentName << endl;

    // Check if new class code is the same as the current class code
    if (currentClassCode == newClassCode) {
        cerr << "FAILED: Student already in " << newClassCode << endl;
        logEntry.accepted = false;
        logEntry.extraNotes = "Student already in" + newClassCode;
        return;
    } else {
        // Create a map to store #students in each class for a certain uc
        map<string, int> classStudentsCount;
        this->global.Students.getStudentsCountInClass(currentUcCode, classStudentsCount);
        // Check if capacity exceeds
        if (!checkIfClassCapacityExceeds(classStudentsCount, newClassCode)) {
            // Check if class balance is disturbed
            if (!checkIfBalanceBetweenClassesDisturbed(classStudentsCount, currentUcCode, currentClassCode, newClassCode)) {
                // Change student class to check if schedule can be built
                for (auto& ucToClass : student.UcToClasses) {
                    if (ucToClass.UcCode == currentUcCode) {
                        ucToClass.ClassCode = newClassCode;
                        // Check for schedule conflict
                        if (!tryBuildNewSchedule(student)) {
                            cerr << "FAILED: Conflict in new schedule, can't change class." << endl;
                            ucToClass.ClassCode = currentClassCode; // Change back to current class
                            logEntry.accepted = false;
                            logEntry.extraNotes = "Conflict in new schedule";
                            return;
                        }
                    }
                }

                cout << "Class changed successfully!" << endl;
                logEntry.accepted = true;
                return;
            } else {
                cerr << "FAILED: Balance between classes disturbed, can't change class." << endl;
                logEntry.accepted = false;
                logEntry.extraNotes = "Balance between classes disturbed";
                return;
            }
        } else {
            cerr << "FAILED: Class capacity exceeded, can't change class." << endl;
            logEntry.accepted = false;
            logEntry.extraNotes = "Class capacity exceeded";
            return;
        }
    }
}

/**
 * @brief Checks if a student can join a new UC (max capacity of UCs = 7).
 *
 * @param student The student to check for UC join eligibility.
 * @return True if the student can join a new UC, otherwise false.
 */
bool Change::checkIfCanJoinNewUC(const Student& student) {
    return student.UcToClasses.size() < 7;
}

/**
 * @brief Returns a map of classes with vacancy in a new UC for a student.
 *
 * @param student The student for whom class vacancy is checked.
 * @param newUcCode The UC code to check for vacancy.
 * @return A map containing class codes and available vacancies.
 */
map<string, int> Change::classesWithVacancyInNewUC(const Student& student, const string& newUcCode) {
    int cap = 26;

    // Create a map to store #students in each class for a certain uc
    map<string, int> classStudentsCount;
    set<string> allClassCodesInUc;

    for (const Class& ucToClass : this->global.Classes) {
        if (ucToClass.UcCode == newUcCode) {
            classStudentsCount[ucToClass.ClassCode] = 0;
        }
    }

    this->global.Students.getStudentsCountInClass(newUcCode, classStudentsCount);

    map<string, int> classesWithVacancy;

    for (const auto& it : classStudentsCount) {
        if (it.second < cap) {
            classesWithVacancy[it.first] = it.second;
        }
    }

    return classesWithVacancy;
}

/**
 * @brief Changes the UC and class of a student.
 *
 * Checks for all rules, if it passes UC and class are changed, otherwise the request is denied.
 *
 * @param student The student for whom UC and class are changed.
 * @param currentUcCode The current UC code of the student.
 * @param currentClassCode The current class code of the student.
 * @param newUcCode The new UC code to change to.
 */
void Change::changeUC(Student& student, const string& currentUcCode, const string& currentClassCode, const string& newUcCode) {
    //register change log
    logEntry.requestType = "Change UC";
    logEntry.timestamp = getCurrentTimestamp(); //defined in UtilityFunctions
    logEntry.studentCode = student.StudentCode;
    logEntry.studentName = student.StudentName;
    logEntry.currentUcCode = currentUcCode;
    logEntry.currentClassCode = currentClassCode;
    logEntry.newUcCode = newUcCode;
    logEntry.newClassCode = "-";

    cout << "[from " << currentUcCode << " to " << newUcCode << "]:" << endl;
    cout << "   Requester Student: " << student.StudentCode << " , " << student.StudentName << endl;

    bool ucAndClassChanged = false;

    // Check if new uc code is the same as the current uc code
    if (currentUcCode == newUcCode) {
        cerr << "FAILED: Student already in " << newUcCode << endl;
        logEntry.accepted = false;
        logEntry.extraNotes = "Student already in";
        return;
    } else {
        map<string, int> classesWithVacancy = classesWithVacancyInNewUC(student, newUcCode);
        if (!classesWithVacancy.empty()) {
            // Change student UC to check
            for (auto& ucToClass : student.UcToClasses) {
                if (ucToClass.UcCode == currentUcCode) {
                    ucToClass.UcCode = newUcCode;

                    vector <pair<string, int>> sortedClasses(classesWithVacancy.begin(), classesWithVacancy.end());

                    sort(sortedClasses.begin(), sortedClasses.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
                        return a.second < b.second;
                    });

                    // Loops through all classes in UC
                    for (const auto& entry: sortedClasses) {
                        // Change class to the new class
                        ucToClass.ClassCode = entry.first;
                        // Tries to build schedule, if not successful, loop to next class
                        if (tryBuildNewSchedule(student)) {
                            cout << "UC and class changed successfully!" << endl;
                            ucAndClassChanged = true;

                            // After changing UC, sort the student's UCs
                            sort(student.UcToClasses.begin(), student.UcToClasses.end(), [](const Class& a, const Class& b) {
                                return a.UcCode < b.UcCode;
                            });

                            logEntry.accepted = true;
                            logEntry.newClassCode = entry.first;
                            break;
                        }
                    }
                    // If student was not able to enter a new UC and class
                    if (!ucAndClassChanged) {
                        // Change them back
                        ucToClass.UcCode = currentUcCode;
                        ucToClass.ClassCode = currentClassCode;
                        cerr << "FAILED: Conflict in new schedule, can't change" << endl;
                        logEntry.accepted = false;
                        logEntry.extraNotes = "Conflict in new schedule";
                    }
                }
            }
        } else {
            cerr << "FAILED: No class with vacancy in the new UC or UC doesn't exist" << endl;
            logEntry.accepted = false;
            logEntry.extraNotes = "No class with vacancy in the new UC or UC doesn't exist";
        }
    }
}

/**
 * Removes a specific UC and class for a student.
 *
 * This function removes the specified UC and class from the student's list of UCs and classes.
 * @param student The student for whom the UC and class are to be removed.
 * @param ucCode The code of the UC to leave.
 * @param classCode The code of the class to leave.
 */
void Change::leaveUCAndClass(Student& student, const string& ucCode, const string& classCode) {
    //register change log
    logEntry.requestType = "Leave UC and Class";
    logEntry.timestamp = getCurrentTimestamp(); //defined in UtilityFunctions
    logEntry.studentCode = student.StudentCode;
    logEntry.studentName = student.StudentName;
    logEntry.currentUcCode = ucCode;
    logEntry.currentClassCode = classCode;
    logEntry.newUcCode = "-";
    logEntry.newClassCode = "-";

    cout << "[from " << ucCode << " , " << classCode << "]:" << endl;
    cout << "   Requester Student: " << student.StudentCode << " , " << student.StudentName << endl;

    // Iterate through the classes in student.UcToClasses
    for (auto it = student.UcToClasses.begin(); it != student.UcToClasses.end(); ++it) {
        // Check if the ucClass matches the provided ucCode and classCode
        if (it->UcCode == ucCode && it->ClassCode == classCode) {
            // Remove the matched class
            student.UcToClasses.erase(it);
            cout << "UC and class removed successfully!" << endl;
            logEntry.accepted = true;
            break; // Exit the loop after removing one UC and class
        }
    }
}

/**
 * Add a new UC and class to a student.
 *
 * This function adds the student to the specified UC and class if it respects all rules.
 * @param student The student to join the new UC and class.
 * @param newUcCode The code of the new UC to join.
 */
void Change::joinUCAndClass(Student& student, const string& newUcCode) {
    //register change log
    logEntry.requestType = "Leave UC and Class";
    logEntry.timestamp = getCurrentTimestamp(); //defined in UtilityFunctions
    logEntry.studentCode = student.StudentCode;
    logEntry.studentName = student.StudentName;
    logEntry.currentUcCode = "-";
    logEntry.currentClassCode = "-";
    logEntry.newUcCode = newUcCode;
    logEntry.newClassCode = "-";

    cout << "[to " << newUcCode << "]:" << endl;
    cout << "   Requester Student: " << student.StudentCode << " , " << student.StudentName << endl;

    bool ucAndClassAdded = false;

    // Check if student will be registered in more than 7 UCs
    if (!checkIfCanJoinNewUC(student)) {
        cerr << "FAILED: Maximum number of UCs will exceed (max: 7 UCs)." << endl;
        logEntry.accepted = false;
        logEntry.extraNotes = "Maximum number of UCs will exceed (max 7 UCs)";
    } else {
        map<string, int> classesWithVacancy = classesWithVacancyInNewUC(student, newUcCode);

        if (!classesWithVacancy.empty()) {
            vector<pair<string, int>> sortedClasses(classesWithVacancy.begin(), classesWithVacancy.end());

            sort(sortedClasses.begin(), sortedClasses.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
                return a.second < b.second;
            });

            for (const auto& entry: sortedClasses) {
                Class newClass = Class(newUcCode, entry.first);
                student.UcToClasses.push_back(newClass);
                if (tryBuildNewSchedule(student)) {
                    cout << "UC and class added successfully!" << endl;
                    ucAndClassAdded = true;

                    sort(student.UcToClasses.begin(), student.UcToClasses.end(), [](const Class& a, const Class& b) {
                        return a.UcCode < b.UcCode;
                    });

                    logEntry.accepted = true;
                    logEntry.newClassCode = entry.first;

                    break;
                } else {
                    // Find the iterator pointing to the newly added class
                    auto it = student.UcToClasses.end() - 1;
                    student.UcToClasses.erase(it);  // Erase the last added class
                    cerr << "FAILED: Conflict in new schedule , can't join" << endl;
                }
            }
            if (!ucAndClassAdded) {
                cerr << "FAILED: No matching UC and class found for adding." << endl;
                logEntry.accepted = false;
                logEntry.extraNotes = "No matching UC and class found for adding";
            }
        } else {
            cerr << "FAILED: No class with vacancy in the new UC." << endl;
            logEntry.accepted = false;
            logEntry.extraNotes = "No class with vacancy in the new UC";
        }
    }
}

/**
 * Swaps classes between two students within the same UC.
 *
 * This function swaps the class of student1 with that of student2 within the same UC.
 * @param student1 The first student to swap classes with.
 * @param ucCode The code of the UC in which the swap occurs.
 * @param classCode1 The code of the first class to swap.
 * @param student2 The second student to swap classes with.
 * @param classCode2 The code of the second class to swap.
 */
void Change::swapClassesBetweenStudents(Student& student1, const string& ucCode, const string& classCode1, Student& student2, const string& classCode2) {
    //register change log
    logEntry.requestType = "Swap Class with other student";
    logEntry.timestamp = getCurrentTimestamp(); //defined in UtilityFunctions
    logEntry.studentCode = student1.StudentCode;
    logEntry.studentName = student1.StudentName;
    logEntry.currentUcCode = ucCode;
    logEntry.currentClassCode = classCode1;
    logEntry.newUcCode = ucCode;
    logEntry.newClassCode = classCode2;
    logEntry.extraNotes = "Swap with student \"" + student2.StudentName +  "\" (" + to_string(student2.StudentCode) + ").\n";
    cout << "[from " << ucCode << " , " << classCode1 << " with " << classCode2 << "]:" << endl;
    cout << "   Requester Student: " << student1.StudentCode << " , " << student1.StudentName << " , " << classCode1 << endl;
    cout << "   Requester Student: " << student2.StudentCode << " , " << student2.StudentName << " , " << classCode2 << endl;

    // Change student1 class to check if schedule can be built
    for (auto& ucToClass : student1.UcToClasses) {
        if (ucToClass.UcCode == ucCode) {
            ucToClass.ClassCode = classCode2;
            // Check for schedule conflict
            if (!tryBuildNewSchedule(student1)) {
                cerr << "FAILED: Conflict in Student 1 new schedule, can't swap classes." << endl;
                ucToClass.ClassCode = classCode1; // Change back to current class
                logEntry.accepted = false;
                logEntry.extraNotes += "Conflict in Student 1 new schedule.";
                return;
            }
        }
    }

    // Change student2 class to check if schedule can be built
    for (auto& ucToClass : student2.UcToClasses) {
        if (ucToClass.UcCode == ucCode) {
            ucToClass.ClassCode = classCode1;
            // Check for schedule conflict
            if (!tryBuildNewSchedule(student2)) {
                cerr << "FAILED: Conflict in Student 2 new schedule, can't swap classes." << endl;
                ucToClass.ClassCode = classCode2; // Change back to current class
                logEntry.accepted = false;
                logEntry.extraNotes += "Conflict in Student 2 new schedule.";
                return;
            }
        }
    }

    cout << "Classes swapped successfully!" << endl;
    return;
}