#include "Script.h"

using namespace std;

Script::Script() {
    System system_;
    system = system_;
    global = {system.get_Classes(), system.get_Schedules(), system.get_Students()};

    consult.set_data(global);
}

void Script::run() {
    clearScreen();
    vector<MenuItem> mainMenu = {
            {"Search", nullptr},
            {"Changes", nullptr},
            {"[Exit]", nullptr}
    };

    vector<MenuItem> searchMenu = {
            {"Schedules", &Script::searchSchedule},
            {"Students Information", &Script::searchStudent},
            {"Students in Class", &Script::consultStudentsInClass},
            {"Students in UC", &Script::consultStudentsInUc},
            {"Students registered in at least X UCs", &Script::consultListOfStudentsInAtLeastNucs},
            {"Year Occupation", &Script::consultOccupationInYear},
            {"[Back]", nullptr}
    };

    bool exitMenu = false;

    while (!exitMenu) {
        clearScreen();

        // Show the main menu table
        cout << "Main Menu:" << endl;
        for (int i = 0; i < mainMenu.size(); i++) {
            cout << i + 1 << ". " << mainMenu[i].label << endl;
        }

        int choice;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            if (cin.eof()) {
                // The user pressed Enter without entering any choice
                continue; // Ignore and continue the loop
            }
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();
        if (choice >= 1 && choice <= mainMenu.size()) {
            if (mainMenu[choice - 1].action != nullptr) {
                (this->*mainMenu[choice - 1].action)();
            } else if (choice == 1) {
                bool exitSubMenu = false;
                while (!exitSubMenu) {
                    clearScreen();
                    cout << "Search Menu:" << endl;
                    for (int i = 0; i < searchMenu.size(); i++) {
                        cout << i + 1 << ". " << searchMenu[i].label << endl;
                    }
                    int subChoice;
                    cout << "Enter your choice: ";
                    if (!(cin >> subChoice)) {
                        // Invalid input (not an integer)
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    if (subChoice == 7) {
                        exitSubMenu = true;
                        clearScreen();
                    } else if (subChoice >= 1 && subChoice <= searchMenu.size()) {
                        if (searchMenu[subChoice - 1].action != nullptr) {
                            (this->*searchMenu[subChoice - 1].action)();
                        }
                    }
                }
            } else if (choice == 2) {
                cout << "Not implemented yet" << endl;
            } else {
                exitMenu = true;
            }
        }
    }
    clearScreen();
    cout << "Goodbye!" << endl;
}

void Script::clearScreen() {
    cout << "\033[2J\033[H";
}

void Script::actionGoBack() {
    clearScreen();
}

void Script::backToMenu() {
    cin.get();
    cout << "Press any key to continue...";
    cin.get();
}

// Implement the actions for your specific menu items
void Script::searchSchedule() {
    clearScreen();
    cout << "Search Schedule selected." << endl;

    vector<MenuItem> scheduleMenu = {
            {"Student Schedule", &Script::consultTheScheduleOfStudent},
            {"Class Schedule", &Script::consultTheScheduleOfClass},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        cout << "Schedule Menu:" << endl;
        for (int i = 0; i < scheduleMenu.size(); i++) {
            cout << i + 1 << ". " << scheduleMenu[i].label << endl;
        }
        int choice;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            if (cin.eof()) {
                // The user pressed Enter without entering any choice
                continue; // Ignore and continue the loop
            }
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();
        if (choice == 3) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= scheduleMenu.size()) {
            (this->*scheduleMenu[choice - 1].action)();
        }
    }
}

void Script::searchStudent() {
    clearScreen();
    cout << "Search Student selected." << endl;

    vector<MenuItem> studentMenu = {
            {"Search by student code", &Script::FindStudentByCode},
            {"Search by student name", &Script::ListStudentsByName},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        cout << "Student Menu:" << endl;
        for (int i = 0; i < studentMenu.size(); i++) {
            cout << i + 1 << ". " << studentMenu[i].label << endl;
        }
        int choice;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            if (cin.eof()) {
                // The user pressed Enter without entering any choice
                continue; // Ignore and continue the loop
            }
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();
        if (choice == 3) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= studentMenu.size()) {
            (this->*studentMenu[choice - 1].action)();
        }
    }
}

void Script::consultTheScheduleOfStudent() {
    cout << "Enter the student code for the schedule you want search for: ";
    int studentCode;
    cin >> studentCode;
    consult.consultTheScheduleOfStudent(studentCode);
    backToMenu();
}

void Script::consultTheScheduleOfClass() {
    cout << "Enter the class code for the schedule you want search for: ";
    string classCode;
    cin >> classCode;
    consult.consultTheScheduleOfClass(classCode);
    backToMenu();
}

void Script::ListStudentsByName() {
    consult.ListStudentsByName();
    backToMenu();
}

void Script::FindStudentByCode() {
    consult.FindStudentByCode();
    backToMenu();
}

void Script::consultListOfStudentsInAtLeastNucs() {
    cout << "Enter the number of students registered in at least \n" <<
            "how many UCs you want to search for: ";
    int n;
    cin >> n;
    consult.consultListOfStudentsInAtLeastNUCs(n);
    backToMenu();
}

void Script::consultStudentsInClass() {
    string classCode;
    cin >> classCode;
    consult.consultStudentsInClass(classCode);
    backToMenu();
}

void Script::consultStudentsInUc() {
    string ucCode;
    cin >> ucCode;
    consult.consultStudentsInUc(ucCode);
    backToMenu();
}

void Script::consultOccupationInYear() {
    string year;
    cin >> year;
    consult.consultStudentsInYear(year);
    backToMenu();
}