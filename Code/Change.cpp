#include "Change.h"
#include <cmath>

Change::Change(Global& globalCopy) : global(globalCopy) {}

bool Change::checkIfClassCapacityExceeds(map<string, int> classStudentsCount, const string& newClassCode) {
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

void Change::getStudentSchedule(const Student& student, vector<Schedule>& studentSchedule) {
    // Iterate through the classes for this student
    for (const Class& studentClass: student.UcToClasses) {
        for (const Schedule& schedule: this->global.Schedules) {
            if (checkIfClassCodeEqual(studentClass.ClassCode, schedule.UcToClasses.ClassCode)
                && checkIfUCCodeEqual(studentClass.UcCode, schedule.UcToClasses.UcCode)) {
                studentSchedule.push_back(schedule);
            }
        }
    }
    sort(studentSchedule.begin(), studentSchedule.end());
}

bool Change::tryBuildNewSchedule(const Student& student) {
    vector<Schedule> studentSchedule;
    getStudentSchedule(student, studentSchedule);

    // Debug print: Print the student's schedule
    cout << "Student Schedule:" << endl;
    for (const Schedule& schedule : studentSchedule) {
        cout << "UC Code: " << schedule.UcToClasses.UcCode << ", Class Code: " << schedule.UcToClasses.ClassCode << ", Weekday: " << schedule.WeekDay << ", Start Hour: " << schedule.StartHour << ", Duration: " << schedule.Duration << ", Type: " << schedule.Type << endl;
    }

    for (size_t i = 0; i < studentSchedule.size(); i++) {
        for (size_t j = i + 1; j < studentSchedule.size(); j++) {
            const Schedule& schedule1 = studentSchedule[i];
            const Schedule& schedule2 = studentSchedule[j];

            if (schedule1.WeekDay == schedule2.WeekDay) {
                string trimmedType1 = schedule1.Type;
                trimmedType1.erase(trimmedType1.begin(), find_if(trimmedType1.begin(), trimmedType1.end(),
                                                                 [](char c) { return !isspace(c); }));
                trimmedType1.erase(find_if(trimmedType1.rbegin(), trimmedType1.rend(),
                                           [](char c) { return !isspace(c); }).base(), trimmedType1.end());

                string trimmedType2 = schedule2.Type;
                trimmedType2.erase(trimmedType2.begin(), find_if(trimmedType2.begin(), trimmedType2.end(),
                                                                 [](char c) { return !isspace(c); }));
                trimmedType2.erase(find_if(trimmedType2.rbegin(), trimmedType2.rend(),
                                           [](char c) { return !isspace(c); }).base(), trimmedType2.end());

                // If one of the classes is of type "T," allow overlapping
                if (trimmedType1 == "T" || trimmedType2 == "T") {
                    continue;
                }

                // Check for non-T classes that overlap
                if (!(schedule1.StartHour + schedule1.Duration <= schedule2.StartHour ||
                      schedule2.StartHour + schedule2.Duration <= schedule1.StartHour)) {
                    return false; // Can't build schedule
                }
            }
        }
    }

    return true; // Can build schedule
}

void Change::changeClass(int studentCode, const string& ucCode, const string& currentClassCode, const string& newClassCode) {
    Student* student = this->global.Students.searchByCode(studentCode);
    bool ucAndClassFound = false;

    if (student) {
        for (Class& ucClass : student->UcToClasses) {
            if (checkIfUCCodeEqual(ucClass.UcCode, ucCode)) {
                ucAndClassFound = true;
                // Create a map to store #students in each class for a certain uc
                map<string, int> classStudentsCount;
                this->global.Students.getStudentsCountInClass(ucCode, classStudentsCount);

                // Check if new class code is the same as the current class code
                if (checkIfClassCodeEqual(currentClassCode, newClassCode)) {
                    cerr << "ERROR: Student already in " << newClassCode << endl;
                    break;
                }

                // Check if new class code is valid
                if (classStudentsCount.find(newClassCode) == classStudentsCount.end()) {
                    cerr << "ERROR: Invalid new class code, please try a different class." << endl;
                    break;
                }

                // Check if capacity exceeds
                if (checkIfClassCapacityExceeds(classStudentsCount, newClassCode)) {
                    cerr << "ERROR: Class capacity exceeded, can't change class." << endl;
                    break; // No need to check for other rules
                }

                //Check if class balance is disturbed
                if (checkIfBalanceBetweenClassesDisturbed(classStudentsCount, currentClassCode, newClassCode)) {
                    cout << currentClassCode << " and " << newClassCode << endl;
                    cerr << "ERROR: Balance between classes disturbed, can't change class." << endl;
                    break; // No need to check for other rules
                }

                // Change student class to check if schedule can be built
                ucClass.ClassCode = newClassCode;

                // Check for schedule conflict
                if (!tryBuildNewSchedule(*student)) {
                    cerr << "ERROR: Conflict in new schedule, can't change class." << endl;
                    ucClass.ClassCode = currentClassCode; // Change back to current class
                    break;
                }

                cout << "Class changed successfully!" << endl;
                break;
            }
        }
        if (!ucAndClassFound) {
            cout << "Uc " << ucCode << " and class " << currentClassCode << " not found in students classes." << endl;
        }
    } else {
        cout << "Student not found." << endl;
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
            string trimmedClassCode = it.first;
            trimmedClassCode.erase(trimmedClassCode.begin(), find_if(trimmedClassCode.begin(), trimmedClassCode.end(),
                                                                     [](char c) { return !isspace(c); }));
            trimmedClassCode.erase(find_if(trimmedClassCode.rbegin(), trimmedClassCode.rend(),
                                           [](char c) { return !isspace(c); }).base(), trimmedClassCode.end());
            classesWithVacancy[trimmedClassCode] = it.second;
        }
    }

    return classesWithVacancy;
}

void Change::changeUC(int studentCode, const string& currentUcCode, const string& currentClassCode, const string& newUcCode) {
    Student* student = this->global.Students.searchByCode(studentCode);
    bool ucAndClassFound = false;
    bool ucAndClassChanged = false;

    if (student) {
        for (Class& ucClass : student->UcToClasses) {
            // Check if new uc code is the same as the current uc code
            if (checkIfUCCodeEqual(ucClass.UcCode, newUcCode)) {
                cerr << "ERROR: Student already in " << newUcCode << endl;
                return;
            }
        }
        for (Class& ucClass : student->UcToClasses) {
            if (checkIfUCCodeEqual(ucClass.UcCode, currentUcCode) && checkIfClassCodeEqual(ucClass.ClassCode, currentClassCode)) {
                ucAndClassFound = true;


                map<string, int> classesWithVacancy = classesWithVacancyInNewUC(*student, newUcCode);

                if (classesWithVacancy.empty()) {
                    cerr << "ERROR: No class with vacancy in the new UC or UC doesn't exist" << endl;
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
                        break;
                    } else {
                        cerr << "ERROR: Conflict in new schedule with UC Code: " << newUcCode << ", Class Code: " << entry.first << endl;
                    }
                }

                if (!ucAndClassChanged) {
                    ucClass.UcCode = currentUcCode;
                    ucClass.ClassCode = currentClassCode;
                    cout << "Cannot change UC." << endl;
                }
            }
        }
        if (!ucAndClassFound) {
            cout << "Uc not found." << endl;
        }
    } else {
        cout << "Student not found." << endl;
    }
}

void Change::leaveUCAndClass(int studentCode, const string& ucCode, const string& classCode) {
    Student* student = this->global.Students.searchByCode(studentCode);
    if (student) {
        bool removed = false; // Variable to track if a UC and class have been removed

        // Iterate through the classes in student->UcToClasses
        for (auto it = student->UcToClasses.begin(); it != student->UcToClasses.end(); ++it) {
            // Check if the ucClass matches the provided ucCode and classCode
            if (checkIfUCCodeEqual(it->UcCode, ucCode) && checkIfClassCodeEqual(it->ClassCode, classCode)) {
                // Remove the matched class
                student->UcToClasses.erase(it);
                cout << "UC and class removed successfully!" << endl;
                removed = true; // Set the flag to indicate removal
                break; // Exit the loop after removing one UC and class
            }
        }

        if (!removed) {
            cout << "No matching UC and class found for removal." << endl;
        }
    } else {
        cerr << "Student not found." << endl;
    }
}

void Change::joinUCAndClass(int studentCode, const string& newUcCode) {
    Student* student = this->global.Students.searchByCode(studentCode);
    bool ucAndClassAdded = false;

    if (student) {
        // Check if student will be registered in more than 7 UCs
        if (!checkIfCanJoinNewUC(*student)) {
            cerr << "ERROR: Maximum number of UCs will exceed (max: 7 UCs)." << endl;
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
                cout << "Student is already registered in " << newUcCode << endl;
                return;
            }
        }

        map<string, int> classesWithVacancy = classesWithVacancyInNewUC(*student, newUcCode);

        if (classesWithVacancy.empty()) {
            cerr << "ERROR: No class with vacancy in the new UC." << endl;
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
                break;
            } else {
                // Find the iterator pointing to the newly added class
                auto it = student->UcToClasses.end() - 1;
                student->UcToClasses.erase(it);  // Erase the last added class
                cerr << "ERROR: Conflict in new schedule with UC Code: " << newUcCode << ", Class Code: " << entry.first << endl;
            }
        }
        if (!ucAndClassAdded) {
            cerr << "No matching UC and class found for adding." << endl;
        }
    } else {
        cerr << "Student not found." << endl;
    }
}