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
                {"Change", nullptr},
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
                        {"Students registered in at least N UCs", &Script::consultListOfStudentsInAtLeastNucs},
                        {"Occupation/List of students registered in (class/UC/year)", &Script::searchOccupation},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("Search Menu", searchMenu);
                if (searchChoice == 5) {
                    break;  // Go back to the main menu
                }
                if (searchMenu[searchChoice - 1].action != nullptr) {
                    (this->*searchMenu[searchChoice - 1].action)();
                }
            }
        } else if (mainChoice == 2) {
            while (true) {
                vector<MenuItem> changeMenu = {
                        {"Remove student", &Script::removeStudent},
                        {"Change class", &Script::changeClass},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("Change Menu", changeMenu);
                if (searchChoice == 3) {
                    break;  // Go back to the main menu
                }
                if (changeMenu[searchChoice - 1].action != nullptr) {
                    (this->*changeMenu[searchChoice - 1].action)();
                }
            }
        }
    }

    clearScreen();
    cout << "Goodbye!" << endl;
}

Global Script::getData() {
    return this->global;
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
    cout << "Press ENTER to continue...";
    cin.get();
}

void Script::searchSchedule() {
    vector<MenuItem> scheduleMenu = {
            {"Student Schedule", &Script::consultTheScheduleOfStudent},
            {"Class Schedule", &Script::consultTheScheduleOfClass},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        cout << "Search Schedule Menu:" << endl;
        for (int i = 0; i < scheduleMenu.size(); i++) {
            cout << i + 1 << ". " << scheduleMenu[i].label << endl;
        }
        int choice;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
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

void Script::searchOccupation() {
    vector<MenuItem> studentMenu = {
            {"Occupation in a Class", &Script::consultStudentsInClass},
            {"Occupation in a UC", &Script::consultStudentsInUc},
            {"Occupation in a Year", &Script::consultStudentsInYear},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        cout << "Occupation Menu:" << endl;
        for (int i = 0; i < studentMenu.size(); i++) {
            cout << i + 1 << ". " << studentMenu[i].label << endl;
        }
        int choice;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();
        if (choice == 4) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= studentMenu.size()) {
            (this->*studentMenu[choice - 1].action)();
        }
    }
}

void Script::consultTheScheduleOfStudent() {
    consult.consultTheScheduleOfStudent();
    backToMenu();
}

void Script::consultTheScheduleOfClass() {
    consult.consultTheScheduleOfClass();
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
    clearScreen();
    consult.consultListOfStudentsInAtLeastNUCs();
    backToMenu();
}

void Script::consultStudentsInClass() {
    consult.consultStudentsInClass();
    backToMenu();
}

void Script::consultStudentsInUc() {
    consult.consultStudentsInUc();
    backToMenu();
}

void Script::consultStudentsInYear() {
    consult.consultStudentsInYear();
    backToMenu();
}

void Script::updateData(Global data) {
    global = data;
    system.updateData(global);
    system.saveCurrentState();
}

void Script::undoAction() {
    system.undoAction();
    global = {system.get_Classes(), system.get_Schedules(), system.get_Students()};
}

void Script::removeStudent() {
    Change change;
    change.removeStudent(this->global);
    updateData(change.global);
}

void Script::changeClass() {
    Change change;
    change.changeClass(this->global, 202078527, "L.EIC023", "3LEIC05");
    updateData(change.global);
}
