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
            {"Schedule", searchSchedule},
            {"Student", searchStudent},
            {"UC Occupations", searchUCOccupations},
            {"Year Occupations", searchYearOccupations},
            {"[Back]", nullptr}
    };

    bool exitMenu = false;

    while (!exitMenu) {
        clearScreen();

        //show the main menu table
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

        if (choice >= 1 && choice <= mainMenu.size()) {
            if (mainMenu[choice - 1].action != nullptr) {
                mainMenu[choice - 1].action();
            } else if (choice == 1) {
                bool exitSubMenu = false;
                while (!exitSubMenu) {
                    clearScreen();
                    cout << "Search Menu:" << endl;
                    for (int i = 0; i < searchMenu.size(); i++) {
                        cout << i + 1 << ". " << searchMenu[i].label << endl;
                    }
                    int subChoice;
                    cout << "Enter your choice (5 to go back to the main menu): ";
                    if (!(cin >> subChoice)) {
                        // Invalid input (not an integer)
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    if (subChoice == 5) {
                        exitSubMenu = true;
                    } else if (subChoice >= 1 && subChoice <= searchMenu.size()) {
                        if (searchMenu[subChoice - 1].action != nullptr) {
                            searchMenu[subChoice - 1].action();
                        }
                    }
                }
            } else {
                exitMenu = true;
            }
        }
    }

    cout << "Goodbye!" << endl;

}

void Script::clearScreen() {
    cout << "\033[2J\033[H";
}

void Script::actionOption1() {
    clearScreen();
    cout << "Option 1 selected." << endl;
}

void Script::actionOption2() {
    clearScreen();
    cout << "Option 2 selected." << endl;
}

void Script::actionOption3() {
    clearScreen();
    cout << "Option 3 selected." << endl;
}

void Script::actionGoBack() {
    clearScreen();
    cout << "Going back to the previous menu." << endl;
}

// Implement the actions for your specific menu items
void Script::searchSchedule() {
    clearScreen();
    cout << "Search Schedule selected." << endl;
    // Implement your code for searching the schedule here
}

void Script::searchStudent() {
    clearScreen();
    cout << "Search Student selected." << endl;
    // Implement your code for searching students here
}

void Script::searchUCOccupations() {
    clearScreen();
    cout << "Search UC Occupations selected." << endl;

    vector<MenuItem> ucOccupationsMenu = {
            {"Option 1", actionOption1},
            {"Option 2", actionOption2},
            {"Option 3", actionOption3},
            {"Go Back", actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        cout << "UC Occupations Menu:" << endl;
        for (int i = 0; i < ucOccupationsMenu.size(); i++) {
            cout << i + 1 << ". " << ucOccupationsMenu[i].label << endl;
        }
        int choice;
        cout << "Enter your choice (4 to go back to the Occupations menu): ";
        if (!(cin >> choice)) {
            // Invalid input (not an integer)
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 4) {
            exitSubMenu = true;
        } else if (choice >= 1 && choice <= ucOccupationsMenu.size()) {
            ucOccupationsMenu[choice - 1].action();
        }
    }
    // Implement your code for searching UC occupations here
}

void Script::searchYearOccupations() {
    clearScreen();
    cout << "Search Year Occupations selected." << endl;
    // Implement your code for searching year occupations here
}


void Script::consultTheScheduleOfStudent() {
    int studentCode;
    cin >> studentCode;
    consult.consultTheScheduleOfStudent(studentCode);
}

void Script::consultTheScheduleOfClass() {
    string classCode;
    cin >> classCode;
    consult.consultTheScheduleOfClass(classCode);
}

void Script::consultListOfStudentsInAtLeastNucs() {
    int n;
    cin >> n;
    consult.consultListOfStudentsInAtLeastNUCs(n);
}

void Script::consultStudentsInClass() {

}

void Script::consultStudentsInClass_ascendingOrder() {

}

void Script::consultStudentsInClass_descendingOrder() {

}

void Script::consultOccupation() {

}

void Script::consultOccupationOfUc() {

}

void Script::consultOccupationOfUc_ascendingOrder() {

}

void Script::consultOccupationOfUc_descendingOrder() {

}

void Script::consultOccupationOfYear() {

}

void Script::consultOccupationOfYear_ascendingOrder() {

}

void Script::consultOccupationOfYear_descendingOrder() {

}
