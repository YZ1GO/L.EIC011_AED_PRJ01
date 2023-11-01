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
                {"Admin", nullptr},
                {"[Exit]", nullptr}
        };

        int mainChoice = showMenu("Main Menu", mainMenu);
        if (mainChoice == 4) {
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
                vector<MenuItem> requestMenu = {
                        {"\033[1mRequest change class\033[0m", &Script::changeClass},
                        {"\033[1mRequest change UC\033[0m", &Script::changeUC},
                        {"\033[1mRequest leave UC and class\033[0m", &Script::leaveUCAndClass},
                        {"\033[1mRequest join UC and class\033[0m", &Script::joinUCAndClass},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("Request Menu", requestMenu);
                if (searchChoice == 5) {
                    break;  // Go back to the main menu
                }
                if (requestMenu[searchChoice - 1].action != nullptr) {
                    (this->*requestMenu[searchChoice - 1].action)();
                }
            }
        } else if (mainChoice == 3) {
            clearScreen();
            string enteredPassword;
            cout << "Enter the admin password: ";
            cin >> enteredPassword;

            if (enteredPassword == adminPassword) {
                cout << "Welcome admin!" << endl;
                clearScreen();
                while (true) {
                    vector<MenuItem> adminMenu = {
                            {"Process request", &Script::processChangeRequests},
                            {"[Back]", nullptr}
                    };

                    int searchChoice = showMenu("Admin Menu", adminMenu);
                    if (searchChoice == 2) {
                        break;  // Go back to the main menu
                    }
                    if (adminMenu[searchChoice - 1].action != nullptr) {
                        (this->*adminMenu[searchChoice - 1].action)();
                    }
                }
            } else {
                cout << "Password incorrect. Access denied." << endl;
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
    ChangeClassRequest request;

    cout << "\033[2J\033[H"; // Clear screen
    // Get student code from the user
    cout << "Enter student code: ";
    cin >> request.studentCode;

    // Get UC code from the user
    cout << "Enter UC code: ";
    cin >> request.currentUcCode;

    // Get current class code from the user
    cout << "Enter current class code: ";
    cin >> request.currentClassCode;

    // Get new class code from the user
    cout << "Enter class you wish to change to: ";
    cin >> request.newClassCode;

    ChangeRequest changeRequest;
    changeRequest.requestType = "ChangeClassRequest";
    changeRequest.requestData = request;

    changeRequestQueue.push(changeRequest);

    cout << "ChangeClass request enqueued for admin review." << endl;
}

void Script::changeUC() {
    ChangeUcRequest request;

    cout << "\033[2J\033[H"; // Clear screen
    cout << "Enter student code: ";
    cin >> request.studentCode;

    cout << "Enter current UC code: ";
    cin >> request.currentUcCode;

    cout << "Enter the respective class code: ";
    cin >> request.currentClassCode;

    cout << "Enter UC you wish to change to: ";
    cin >> request.newUcCode;

    ChangeRequest changeRequest;
    changeRequest.requestType = "ChangeUCRequest";
    changeRequest.requestData = request;

    changeRequestQueue.push(changeRequest);

    cout << "ChangeUC request enqueued for admin review." << endl;
}

void Script::leaveUCAndClass() {
    LeaveUcClassRequest request;

    cout << "\033[2J\033[H"; // Clear screen
    cout << "Enter student code: ";
    cin >> request.studentCode;

    cout << "Enter UC you wish to leave: ";
    cin >> request.currentUcCode;

    cout << "Enter respective class code: ";
    cin >> request.currentClassCode;

    ChangeRequest changeRequest;
    changeRequest.requestType = "LeaveUcClassRequest";
    changeRequest.requestData = request;

    changeRequestQueue.push(changeRequest);

    cout << "LeaveUcClass request enqueued for admin review." << endl;
}

void Script::joinUCAndClass() {
    JoinUcClassRequest request;

    cout << "\033[2J\033[H"; // Clear screen
    cout << "Enter student code: ";
    cin >> request.studentCode;

    cout << "Enter UC you wish to join: ";
    cin >> request.newUcCode;

    ChangeRequest changeRequest;
    changeRequest.requestType = "JoinUcClassRequest";
    changeRequest.requestData = request;

    changeRequestQueue.push(changeRequest);

    cout << "JoinUcClass request enqueued for admin review." << endl;
    /*Change change(global);
    change.joinUCAndClass();
    updateData(change.global);*/
}

void Script::processChangeRequests() {
    while (!changeRequestQueue.empty()) {
        ChangeRequest request = changeRequestQueue.front();
        changeRequestQueue.pop();

        if (request.requestType == "ChangeClassRequest") {
            ChangeClassRequest changeRequest = get<ChangeClassRequest>(request.requestData);
            Change change(global);
            change.changeClass(changeRequest.studentCode, changeRequest.currentUcCode, changeRequest.currentClassCode, changeRequest.newClassCode);
            updateData(change.global);
            break;
        } else if (request.requestType == "ChangeUcRequest") {
            ChangeUcRequest changeRequest = get<ChangeUcRequest>(request.requestData);
            Change change(global);
            change.changeUC(changeRequest.studentCode, changeRequest.currentUcCode, changeRequest.currentClassCode, changeRequest.newUcCode);
            updateData(change.global);
            break;
        } else if (request.requestType == "LeaveUcClassRequest") {
            LeaveUcClassRequest changeRequest = get<LeaveUcClassRequest>(request.requestData);
            Change change(global);
            change.leaveUCAndClass(changeRequest.studentCode, changeRequest.currentUcCode, changeRequest.currentClassCode);
            updateData(change.global);
            break;
        } else if (request.requestType == "JoinUcClassRequest") {
            JoinUcClassRequest changeRequest = get<JoinUcClassRequest>(request.requestData);
            Change change(global);
            change.joinUCAndClass(changeRequest.studentCode, changeRequest.newUcCode);
            updateData(change.global);
            break;
        } else {
            cout << "Unsupported request type: " << request.requestType << endl;
            break;
        }
    }
    if (changeRequestQueue.empty()) {
        cout << "No requests pending." << endl;
    }
}
