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
                {"\033[1mSearch\033[0m", nullptr},
                {"\033[1mChange\033[0m", nullptr},
                {"[Exit]", nullptr}
        };

        int mainChoice = showMenu("Main Menu", mainMenu);
        if (mainChoice == 3) {
            break;  // Exit the loop and end the program
        }

        if (mainChoice == 1) {
            while (true) {
                vector<MenuItem> searchMenu = {
                        {"\033[1mSchedules\033[0m (student/class)", &Script::searchSchedule},
                        {"\033[1mStudents Information\033[0m", &Script::searchStudent},
                        {"\033[1mOccupation of\033[0m (classes/UCs/years)", &Script::searchOccupation},
                        {"\033[1mList of students registered in a\033[0m (class/UC/year)", &Script::searchListOfStudents},
                        {"\033[1mList of students registered in at least N UCs\033[0m", &Script::listOfStudentsInAtLeastNUCs},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("Search Menu", searchMenu);
                if (searchChoice == 6) {
                    break;  // Go back to the main menu
                }
                if (searchMenu[searchChoice - 1].action != nullptr) {
                    (this->*searchMenu[searchChoice - 1].action)();
                }
            }
        } else if (mainChoice == 2) {
            while (true) {
                vector<MenuItem> changeMenu = {
                        {"\033[1mChange class\033[0m", &Script::changeClass},
                        {"\033[1mChange uc\033[0m", &Script::changeUC},
                        {"\033[1mLeave uc and class\033[0m", &Script::leaveUCAndClass},
                        {"\033[1mJoin uc and class\033[0m", &Script::joinUCAndClass},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("Change Menu", changeMenu);
                if (searchChoice == 5) {
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

void Script::drawBox(const string &text) {
    int width = text.length() + 4;
    string horizontalLine(width, '-');
    cout << "+" << horizontalLine << "+" << endl;
    cout << "|  " << text << "  |" << endl;
    cout << "+" << horizontalLine << "+" << endl;
}

int Script::showMenu(const string& menuName, const vector<MenuItem>& menuItems) {
    clearScreen();
    drawBox(menuName);
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
            {"\033[1mStudent Schedule\033[0m", &Script::consultTheScheduleOfStudent},
            {"\033[1mClass Schedule\033[0m", &Script::consultTheScheduleOfClass},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("Search Schedule Menu");
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
            {"\033[1mSearch by student code\033[0m", &Script::findStudentByCode},
            {"\033[1mSearch by student name\033[0m", &Script::listStudentsByName},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("Student Menu");
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
    vector<MenuItem> occupationMenu = {
            {"\033[1mOccupation of the Classes\033[0m", &Script::occupationOfClasses},
            {"\033[1mOccupation of the UCs\033[0m", &Script::occupationOfUcs},
            {"\033[1mOccupation of the Years\033[0m", &Script::occupationOfYears},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("Occupation Menu");
        for (int i = 0; i < occupationMenu.size(); i++) {
            cout << i + 1 << ". " << occupationMenu[i].label << endl;
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
        } else if (choice >= 1 && choice <= occupationMenu.size()) {
            (this->*occupationMenu[choice - 1].action)();
        }
    }
}

void Script::searchListOfStudents() {
    vector<MenuItem> listofstudentMenu = {
            {"\033[1mList of students in a Class\033[0m", &Script::listOfStudentsInClass},
            {"\033[1mList of students in a UC\033[0m", &Script::listOfStudentsInUc},
            {"\033[1mList of students in a Year\033[0m", &Script::listOfStudentsInYear},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("List of Students Menu");
        for (int i = 0; i < listofstudentMenu.size(); i++) {
            cout << i + 1 << ". " << listofstudentMenu[i].label << endl;
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
        } else if (choice >= 1 && choice <= listofstudentMenu.size()) {
            (this->*listofstudentMenu[choice - 1].action)();
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

void Script::findStudentByCode() {
    consult.findStudentByCode();
    backToMenu();
}

void Script::listStudentsByName() {
    consult.listStudentsByName();
    backToMenu();
}

void Script::occupationOfClasses() {
    consult.occupationInClasses();
    backToMenu();
}

void Script::occupationOfUcs() {
    consult.occupationInUcs();
    backToMenu();
}

void Script::occupationOfYears() {
    consult.occupationInYears();
    backToMenu();
}

void Script::listOfStudentsInClass() {
    consult.listOfStudentsInClass();
    backToMenu();
}

void Script::listOfStudentsInUc() {
    consult.listOfStudentsInUc();
    backToMenu();
}

void Script::listOfStudentsInYear() {
    consult.listOfStudentsInYear();
    backToMenu();
}

void Script::listOfStudentsInAtLeastNUCs() {
    clearScreen();
    consult.listOfStudentsInAtLeastNUCs();
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

void Script::changeClass() {
    Change change(global);
    change.changeClass();
    updateData(change.global);
}

void Script::changeUC() {
    Change change(global);
    change.changeUC();
    updateData(change.global);
}

void Script::leaveUCAndClass() {
    Change change(global);
    change.leaveUCAndClass();
    updateData(change.global);
}

void Script::joinUCAndClass() {
    Change change(global);
    change.joinUCAndClass();
    updateData(change.global);
}

