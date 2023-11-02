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
                {"\033[1mAdmin\033[0m", nullptr},
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
                        {"\033[1mOccupation of ALL\033[0m (classes/UCs/years)", &Script::searchAllOccupations},
                        {"\033[1mOccupation of the\033[0m (classes of a UC/UCs of a year)", &Script::searchSpecificOccupation},
                        {"\033[1mList of students registered in a\033[0m (class/UC/year)", &Script::searchListOfStudents},
                        {"\033[1mList of students registered in at least N UCs\033[0m", &Script::listOfStudentsInAtLeastNUCs},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("Search Menu", searchMenu);
                if (searchChoice == 7) {
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
                            {"Successful requests", &Script::successfulRequests},
                            {"Failed requests", &Script::failedRequests},
                            {"[Back]", nullptr}
                    };

                    int searchChoice = showMenu("Admin Menu", adminMenu);
                    if (searchChoice == 4) {
                        break;  // Go back to the main menu
                    }
                    if (adminMenu[searchChoice - 1].action != nullptr) {
                        (this->*adminMenu[searchChoice - 1].action)();
                    }
                }
            } else {
                cout << "Password incorrect. Access denied." << endl;
                backToMenu();
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

void Script::searchAllOccupations() {
    vector<MenuItem> occupationMenu = {
            {"\033[1mOccupation of the Classes\033[0m", &Script::occupationOfClasses},
            {"\033[1mOccupation of the UCs\033[0m", &Script::occupationOfUcs},
            {"\033[1mOccupation of the Years\033[0m", &Script::occupationOfYears},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("Occupations Menu");
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

void Script::searchSpecificOccupation() {
    vector<MenuItem> occupationMenu = {
            {"\033[1mOccupation of the Classes of a UC\033[0m", &Script::occupationOfClassesOfUc},
            {"\033[1mOccupation of the UCs of a Year\033[0m", &Script::occupationOfUcsOfYear},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("Occupations Menu");
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
        if (choice == 3) {
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

void Script::occupationOfClassesOfUc() {
    consult.consultUcOccupation();
    backToMenu();
}

void Script::occupationOfUcsOfYear() {
    consult.consultYearOccupation();
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
    Consult consult(global);
    ChangeClassRequest request;

    clearScreen();
    int studentCode;
    // Get student code from the user
    cout << "Enter student code: ";
    cin >> studentCode;

    Student* student = global.Students.searchByCode(studentCode);

    if (student) {
        request.student = student;
        clearScreen();

        cout << "Student Code: " << student->StudentCode << endl;
        cout << "Student Name: " << student->StudentName << endl;
        cout << "UCs and Classes: " << endl;

        int index = 1;
        for (const Class& ucToClass : student->UcToClasses) {
            cout << index << ". UcCode: " << ucToClass.UcCode  << ", ClassCode: " << ucToClass.ClassCode << endl;
            index++;
        }
        cout << index << ". [back]" << endl;
        int choice;
        bool validChoice = false;

        while (!validChoice) {
            cout << "Choose the class you'd wish to change: ";
            cin >> choice;
            //go back
            if (choice == index) {
                return;
            }
            // Check if user's choice is valid
            if (choice >= 1 && choice <= student->UcToClasses.size()) {
                validChoice = true; // Set flag to exit the loop
            } else {
                cerr << "ERROR: Invalid input. Please enter a valid choice." << endl;
                cin.clear();  // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                cout << "\n";
            }
        }

        const Class& selectedClass = student->UcToClasses[choice - 1];
        request.currentUcCode = selectedClass.UcCode;
        request.currentClassCode = selectedClass.ClassCode;

        cout << "You've chosen " << request.currentUcCode << ", " << request.currentClassCode << endl;
        cout << "\n";
        if (request.currentUcCode == "UP001") {
            cout << "There are no other classes in UP001." << endl;
            return;
        }
        cout << "These are the possible classes and respective number of students in " << request.currentUcCode << " you can choose: " << endl;

        index = 1;

        map<string, int> classStudentsCount;
        global.Students.getStudentsCountInClass(selectedClass.UcCode, classStudentsCount);

        for (const auto& classes : classStudentsCount) {
            cout << index << ". " << classes.first << ": " << classes.second << endl;
            index++;

        }

        cout << "\n";
        validChoice = false;

        while (!validChoice) {
            cout << "Choose the class you'd wish to change to: ";
            cin >> choice;

            // Check if user's choice is valid
            if (choice >= 1 && choice <= classStudentsCount.size()) {
                validChoice = true; // Set flag to exit the loop
            } else {
                cerr << "Invalid input. Please enter a valid choice." << endl;
                cin.clear();  // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                cout << "\n";
            }
        }

        auto it = classStudentsCount.begin();
        advance(it, choice - 1);
        request.newClassCode = it->first;
        cout << "You've chosen to change to " << request.newClassCode << endl;
        cout << "\n";

        ChangeRequest changeRequest;
        changeRequest.requestType = "ChangeClassRequest";
        changeRequest.requestData = request;

        changeRequestQueue.push(changeRequest);

        cout << "Change Class request enqueued for admin review." << endl;
        cout << "\n";
    } else {
        cerr << "ERROR: Student not found." << endl;
    }
    backToMenu();
}

void Script::changeUC() {
    ChangeUcRequest request;

    clearScreen();
    int studentCode;
    cout << "Enter student code: ";
    cin >> studentCode;

    Student* student = global.Students.searchByCode(studentCode);

    if (student) {
        request.student = student;
        clearScreen();

        cout << "Student Code: " << student->StudentCode << endl;
        cout << "Student Name: " << student->StudentName << endl;
        cout << "UCs and Classes: " << endl;

        set<string> studentUcCodes;
        int index = 1;
        for (const Class& ucToClass : student->UcToClasses) {
            studentUcCodes.insert(ucToClass.UcCode);
            cout << index << ". UcCode: " << ucToClass.UcCode  << ", ClassCode: " << ucToClass.ClassCode << endl;
            index++;
        }
        cout << index << ". [back]" << endl;
        int choice;
        bool validChoice = false;

        while (!validChoice) {
            cout << "Choose the UC you'd wish to change: ";
            cin >> choice;
            //go back
            if (choice == index) {
                return;
            }
            // Check if user's choice is valid
            if (choice >= 1 && choice <= student->UcToClasses.size()) {
                validChoice = true; // Set flag to exit the loop
            } else {
                cerr << "ERROR: Invalid input. Please enter a valid choice." << endl;
                cin.clear();  // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                cout << "\n";
            }
        }

        const Class& selectedClass = student->UcToClasses[choice - 1];
        request.currentUcCode = selectedClass.UcCode;
        request.currentClassCode = selectedClass.ClassCode;

        cout << "You've chosen " << request.currentUcCode << ", " << request.currentClassCode << endl;
        cout << "\n";
        cout << "These are the UCs you are not registered in: " << endl;

        index = 1;
        set<string> uniqueUcCodes;
        map<int, string> correspondingUcCode;
        for (const Class& classes: global.Classes) {
            const string& ucCode = classes.UcCode;
            if (uniqueUcCodes.find(ucCode) == uniqueUcCodes.end() && studentUcCodes.find(ucCode) == studentUcCodes.end()) {
                cout << index << ". " << ucCode << endl;
                uniqueUcCodes.insert(ucCode);
                correspondingUcCode[index] = ucCode;
                index++;
            }
        }

        cout << "\n";
        validChoice = false;
        while (!validChoice) {
            cout << "Choose the UC you'd wish to change to: ";
            cin >> choice;

            // Check if user's choice is valid
            if (choice >= 1 && choice <= index) {
                request.newUcCode = correspondingUcCode[choice];
                validChoice = true; // Set flag to exit the loop
            } else {
                cerr << "Invalid input. Please enter a valid choice." << endl;
                cin.clear();  // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                cout << "\n";
            }
        }

        cout << "You've chosen to change to " << request.newUcCode << endl;
        cout << "\n";

        ChangeRequest changeRequest;
        changeRequest.requestType = "ChangeUcRequest";
        changeRequest.requestData = request;

        changeRequestQueue.push(changeRequest);

        cout << "ChangeUc request enqueued for admin review." << endl;
        cout << "\n";
    } else {
        cerr << "ERROR: Student not found." << endl;
    }
    backToMenu();
}

void Script::leaveUCAndClass() {
    LeaveUcClassRequest request;

    clearScreen();
    int studentCode;
    cout << "Enter student code: ";
    cin >> studentCode;

    Student* student = global.Students.searchByCode(studentCode);

    if (student) {
        request.student = student;
        clearScreen();

        cout << "Student Code: " << student->StudentCode << endl;
        cout << "Student Name: " << student->StudentName << endl;
        cout << "UCs and Classes: " << endl;

        int index = 1;
        for (const Class& ucToClass : student->UcToClasses) {
            cout << index << ". UcCode: " << ucToClass.UcCode  << ", ClassCode: " << ucToClass.ClassCode << endl;
            index++;
        }
        cout << index << ". [back]" << endl;
        int choice;
        bool validChoice = false;

        while (!validChoice) {
            cout << "Choose the UC and class you'd wish to leave: ";
            cin >> choice;
            //go back
            if (choice == index) {
                return;
            }
            // Check if user's choice is valid
            if (choice >= 1 && choice <= student->UcToClasses.size()) {
                validChoice = true; // Set flag to exit the loop
            } else {
                cerr << "ERROR: Invalid input. Please enter a valid choice." << endl;
                cin.clear();  // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                cout << "\n";
            }
        }

        const Class& selectedClass = student->UcToClasses[choice - 1];
        request.currentUcCode = selectedClass.UcCode;
        request.currentClassCode = selectedClass.ClassCode;

        cout << "You've chosen to leave " << request.currentUcCode << ", " << request.currentClassCode << endl;
        cout << "\n";

        ChangeRequest changeRequest;
        changeRequest.requestType = "LeaveUcClassRequest";
        changeRequest.requestData = request;

        changeRequestQueue.push(changeRequest);

        cout << "LeaveUcClass request enqueued for admin review." << endl;
        cout << "\n";
        backToMenu();
    } else {
        cerr << "ERROR: Student not found." << endl;
    }
    backToMenu();
}

void Script::joinUCAndClass() {
    JoinUcClassRequest request;

    clearScreen();
    int studentCode;
    cout << "Enter student code: ";
    cin >> studentCode;

    Student* student = global.Students.searchByCode(studentCode);

    if (student) {
        request.student = student;
        clearScreen();

        cout << "Student Code: " << student->StudentCode << endl;
        cout << "Student Name: " << student->StudentName << endl;
        cout << "UCs and Classes: " << endl;

        set<string> studentUcCodes;
        int index = 1;
        for (const Class& ucToClass : student->UcToClasses) {
            studentUcCodes.insert(ucToClass.UcCode);
            cout << index << ". UcCode: " << ucToClass.UcCode  << ", ClassCode: " << ucToClass.ClassCode << endl;
            index++;
        }
        cout << index << ". [back]" << endl;
        cout << "These are the UCs you are not registered in: " << endl;

        index = 1;
        set<string> uniqueUcCodes;
        map<int, string> correspondingUcCode;
        for (const Class& classes: global.Classes) {
            const string& ucCode = classes.UcCode;
            if (uniqueUcCodes.find(ucCode) == uniqueUcCodes.end() && studentUcCodes.find(ucCode) == studentUcCodes.end()) {
                cout << index << ". " << ucCode << endl;
                uniqueUcCodes.insert(ucCode);
                correspondingUcCode[index] = ucCode;
                index++;
            }
        }
        cout << "\n";

        int choice;
        bool validChoice = false;
        while (!validChoice) {
            cout << "Choose the UC you'd wish to change to: ";
            cin >> choice;
            //go back
            if (choice == index) {
                return;
            }
            // Check if user's choice is valid
            if (choice >= 1 && choice < index) {
                request.newUcCode = correspondingUcCode[choice];
                validChoice = true; // Set flag to exit the loop
            } else {
                cerr << "Invalid input. Please enter a valid choice." << endl;
                cin.clear();  // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                cout << "\n";
            }
        }

        cout << "You've chosen to join " << request.newUcCode << endl;
        cout << "\n";

        ChangeRequest changeRequest;
        changeRequest.requestType = "JoinUcClassRequest";
        changeRequest.requestData = request;

        changeRequestQueue.push(changeRequest);

        cout << "JoinUcClass request enqueued for admin review." << endl;
        cout << "\n";
        backToMenu();
    } else {
        cerr << "ERROR: Student not found." << endl;
    }
    backToMenu();
}

void Script::processChangeRequests() {
    clearScreen();

    drawBox("Change Requests");
    int i = 1;
    while (!changeRequestQueue.empty()) {
        ChangeRequest request = changeRequestQueue.front();
        changeRequestQueue.pop();

        if (request.requestType == "ChangeClassRequest") {
            cout << i++ << ". \033[1mChange Class\033[0m ";
            ChangeClassRequest changeRequest = get<ChangeClassRequest>(request.requestData);
            Change change(global);
            change.changeClass(*changeRequest.student, changeRequest.currentUcCode, changeRequest.currentClassCode, changeRequest.newClassCode);
            updateData(change.global);
            cout << endl;
        }
        if (request.requestType == "ChangeUcRequest") {
            cout << i++ << ". \033[1mChange UC\033[0m ";
            ChangeUcRequest changeRequest = get<ChangeUcRequest>(request.requestData);
            Change change(global);
            change.changeUC(*changeRequest.student, changeRequest.currentUcCode, changeRequest.currentClassCode, changeRequest.newUcCode);
            updateData(change.global);
            cout << endl;
        }
        if (request.requestType == "LeaveUcClassRequest") {
            cout << i++ << ". \033[1mLeave UC and Class\033[0m ";
            LeaveUcClassRequest changeRequest = get<LeaveUcClassRequest>(request.requestData);
            Change change(global);
            change.leaveUCAndClass(*changeRequest.student, changeRequest.currentUcCode, changeRequest.currentClassCode);
            updateData(change.global);
            cout << endl;
        }
        if (request.requestType == "JoinUcClassRequest") {
            cout << i++ << ". \033[1mJoin UC and Class\033[0m ";
            JoinUcClassRequest changeRequest = get<JoinUcClassRequest>(request.requestData);
            Change change(global);
            change.joinUCAndClass(*changeRequest.student, changeRequest.newUcCode);
            updateData(change.global);
            cout << endl;
        }
    }
    if (changeRequestQueue.empty()) {
        cout << "No requests pending." << endl;
        cout << "\n";
    }
    backToMenu();
}

void Script::successfulRequests() {

}

void Script::failedRequests() {

}