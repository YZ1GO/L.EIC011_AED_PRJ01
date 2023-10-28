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

    while (true) {
        vector<MenuItem> mainMenu = {
                {"Search", nullptr},
                {"Changes", nullptr},
                {"[Exit]", nullptr}
        };

        int mainChoice = showMenu("Main Menu", mainMenu);
        if (mainChoice == 3) {
            break;  // Exit the loop and end the program
        }

        if (mainChoice == 1) {
            while (true) {
                vector<MenuItem> searchMenu = {
                        {"Schedules", &Script::searchSchedule},
                        {"Students Information", &Script::searchStudent},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("Search Menu", searchMenu);
                if (searchChoice == 3) {
                    break;  // Go back to the main menu
                }
                if (searchMenu[searchChoice - 1].action != nullptr) {
                    (this->*searchMenu[searchChoice - 1].action)();
                }
            }
        } else if (mainChoice == 2) {
            cout << "Not implemented yet" << endl;
        }
    }

    clearScreen();
    cout << "Goodbye!" << endl;
}

int Script::showMenu(const string& menuName, const vector<MenuItem>& menuItems) {
    clearScreen();
    cout << menuName << ":" << endl;
    for (int i = 0; i < menuItems.size(); i++) {
        cout << i + 1 << ". " << menuItems[i].label << endl;
    }

    int choice;
    cout << "Enter your choice: ";
    if (!(cin >> choice)) {
        if (cin.eof()) {
            cin.clear();
            return 0;  // User pressed Enter without entering a choice
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 0;  // Invalid choice (not an integer)
    }

    if (choice >= 1 && choice <= menuItems.size()) {
        return choice;
    } else {
        return 0;  // Invalid choice (out of range)
    }
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