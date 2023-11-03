#include "Script.h"

using namespace std;

Script::Script() {
    System system_;
    system = system_;
    global = {system.get_Classes(), system.get_Schedules(), system.get_Students()};
    consult = Consult(global);
}

void Script::updateData(Global global) {
    system.updateData(global);
    system.saveCurrentState();
    consult.updateData(global);
}

void Script::undoAction() {
    system.undoAction();
    global = {system.get_Classes(), system.get_Schedules(), system.get_Students()};
    consult.updateData(global);
}

void Script::run() {
    clearScreen();

    while (true) {
        vector<MenuItem> mainMenu = {
                {"\033[1mSearch\033[0m", nullptr},
                {"\033[1mChange\033[0m", nullptr},
                {"\033[1mAdmin\033[0m", nullptr},
                {"\033[1mPrint to File\033[0m", nullptr},
                {"[Exit]", nullptr}
        };

        int mainChoice = showMenu("Main Menu", mainMenu);
        if (mainChoice == 5) {
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
                if (searchChoice >=1 && searchChoice < 7 && searchMenu[searchChoice - 1].action != nullptr) {
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
                        {"\033[1mRequest swap classes between students\033[0m", &Script::swapClassesBetweenStudents},
                        {"[Back]", nullptr}
                };

                int searchChoice = showMenu("Request Menu", requestMenu);
                if (searchChoice == 6) {
                    break;  // Go back to the main menu
                }
                if (searchChoice >= 1 && searchChoice < 6 && requestMenu[searchChoice - 1].action != nullptr) {
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
                            {"\033[1mProcess next request\033[0m", &Script::processNextChangeRequest},
                            {"\033[1mProcess all requests\033[0m", &Script::processAllChangeRequests},
                            {"\033[1mChange logs\033[0m", &Script::changeLogsMenu},
                            {"[Back]", nullptr}
                    };

                    int searchChoice = showMenu("Admin Menu", adminMenu);


                    if (searchChoice == 4) {
                        break;  // Go back to the main menu
                    }
                    if (searchChoice >=1 && searchChoice < 4 && adminMenu[searchChoice - 1].action != nullptr) {
                        (this->*adminMenu[searchChoice - 1].action)();
                    }
                }
            } else {
                cout << "Password incorrect. Access denied." << endl;
                backToMenu();
            }
        } else if (mainChoice == 4) {
            printToFile();
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
    vector<MenuItem> listOfStudentMenu = {
            {"\033[1mList of students in a Class\033[0m", &Script::listOfStudentsInClass},
            {"\033[1mList of students in a UC\033[0m", &Script::listOfStudentsInUc},
            {"\033[1mList of students in a Year\033[0m", &Script::listOfStudentsInYear},
            {"[Back]", &Script::actionGoBack}
    };

    bool exitSubMenu = false;

    while (!exitSubMenu) {
        clearScreen();
        drawBox("List of Students Menu");
        for (int i = 0; i < listOfStudentMenu.size(); i++) {
            cout << i + 1 << ". " << listOfStudentMenu[i].label << endl;
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
        } else if (choice >= 1 && choice <= listOfStudentMenu.size()) {
            (this->*listOfStudentMenu[choice - 1].action)();
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

void Script::pendingRequest(const int& studentCode) {
    while (!changeRequestQueue.empty()) {
        const ChangeRequest& changeRequest = changeRequestQueue.front();
        cout << "\n";
        cout << "\033[1m[Pending request]\033[0m" << endl;
        if (changeRequest.requestType == "ChangeClassRequest") {
            const ChangeClassRequest& data = get<ChangeClassRequest>(changeRequest.requestData);
            if (data.student->StudentCode == studentCode) {
                cout << "Student Name: " << data.student->StudentName << endl;
                cout << "Request Type: " << changeRequest.requestType << endl;
                cout << "Current UC Code: " << data.currentUcCode << endl;
                cout << "Current Class Code: " << data.currentClassCode << endl;
                cout << "New Class Code: " << data.newClassCode << endl;
            }
        } else if (changeRequest.requestType == "ChangeUcRequest") {
            const ChangeUcRequest& data = get<ChangeUcRequest>(changeRequest.requestData);
            if (data.student->StudentCode == studentCode) {
                cout << "Student Name: " << data.student->StudentName << endl;
                cout << "Request Type: " << changeRequest.requestType << endl;
                cout << "Current UC Code: " << data.currentUcCode << endl;
                cout << "Current Class Code: " << data.currentClassCode << endl;
                cout << "New UC Code: " << data.newUcCode << endl;
            }
        } else if (changeRequest.requestType == "LeaveUcClassRequest") {
            const LeaveUcClassRequest& data = get<LeaveUcClassRequest>(changeRequest.requestData);
            if (data.student->StudentCode == studentCode) {
                cout << "Student Name: " << data.student->StudentName << endl;
                cout << "Request Type: " << changeRequest.requestType << endl;
                cout << "Current UC Code: " << data.currentUcCode << endl;
                cout << "Current Class Code: " << data.currentClassCode << endl;
            }
        } else if (changeRequest.requestType == "JoinUcClassRequest") {
            const JoinUcClassRequest& data = get<JoinUcClassRequest>(changeRequest.requestData);
            if (data.student->StudentCode == studentCode) {
                cout << "Student Name: " << data.student->StudentName << endl;
                cout << "Request Type: " << changeRequest.requestType << endl;
                cout << "New UC Code: " << data.newUcCode << endl;
            }
        } else if (changeRequest.requestType == "SwapClassesRequest") {
            const SwapClassesRequest& data = get<SwapClassesRequest>(changeRequest.requestData);
            if (data.student1->StudentCode == studentCode) {
                cout << "Student Name: " << data.student1->StudentName << endl;
                cout << "Request Type: " << changeRequest.requestType << endl;
                cout << "UC Code: " << data.ucCode << endl;
                cout << "Current Class Code: " << data.classCode1 << endl;
                cout << "New Class Code: " << data.classCode2 << endl;
            } else if (data.student2->StudentCode == studentCode) {
                cout << "Student Name: " << data.student2->StudentName << endl;
                cout << "Request Type: " << changeRequest.requestType << endl;
                cout << "UC Code: " << data.ucCode << endl;
                cout << "Current Class Code: " << data.classCode2 << endl;
                cout << "New Class Code: " << data.classCode1 << endl;
            }
        }
        cout << "\n";
        cout << "Please wait for it to be reviewed..." << endl;
        cout << "\n";
        cout << "1. [Back]" << endl;
        cout << "2. [Cancel request]" << endl;
        cout << "\n";

        int choice;
        bool validChoice = false;

        while (!validChoice) {
            cout << "Enter your choice: ";
            cin >> choice;
            //go back
            if (choice == 1) {
                return;
            }
            if (choice == 2) {
                validChoice = true; // Set flag to exit the loop
                if (changeRequest.requestType == "SwapClassesRequest") {
                    const SwapClassesRequest& data = get<SwapClassesRequest>(changeRequest.requestData);
                    studentHasPendingRequest[data.student1->StudentCode] = false;
                    studentHasPendingRequest[data.student2->StudentCode] = false;
                }
                changeRequestQueue.pop();
                studentHasPendingRequest[studentCode] = false;
                cout << "\033[1mRequest canceled successfully.\033[0m" << endl;
                cout << "\n";
            } else {
                cerr << "ERROR: Invalid input. Please enter a valid choice." << endl;
                cin.clear();  // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                cout << "\n";
            }
        }
    }
}

void Script::changeClass() {
    ChangeClassRequest request;

    clearScreen();
    int studentCode;
    // Get student code from the user
    cout << "Enter student code: ";
    cin >> studentCode;

    if (studentHasPendingRequest[studentCode]) {
        pendingRequest(studentCode);
    } else {
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
            cout << index << ". [Back]" << endl;
            cout << "\n";

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
                cerr << "ERROR: There are no other classes in UP001." << endl;
                ChangeLogEntry LogEntry = {getCurrentTimestamp(), "Change Class",
                                           studentCode, student->StudentName, request.currentUcCode,
                                           request.currentClassCode, request.currentUcCode,
                                           "-", "-", false};
                backToMenu();
            } else {
                cout << "These are the possible classes and respective number of students in " << request.currentUcCode << " you can choose: " << endl;
                cout << "(Please note that it can be more challenging to switch to a class with a larger number of students compared to one with fewer students.)" << endl;

                index = 1;

                map<string, int> classStudentsCount;
                global.Students.getStudentsCountInClass(selectedClass.UcCode, classStudentsCount);
                map<int, string> correspondingClassCode;
                for (const auto& classes : classStudentsCount) {
                    if (classes.first != request.currentClassCode) {
                        cout << index << ". " << classes.first << ": " << classes.second << endl;
                        correspondingClassCode[index] = classes.first;
                        index++;
                    }
                }

                cout << "\n";
                validChoice = false;

                while (!validChoice) {
                    cout << "Choose the class you'd wish to change to: ";
                    cin >> choice;


                    // Check if user's choice is valid
                    if (choice >= 1 && choice <= classStudentsCount.size()) {
                        request.newClassCode = correspondingClassCode[choice];
                        validChoice = true; // Set flag to exit the loop
                    } else {
                        cerr << "Invalid input. Please enter a valid choice." << endl;
                        cin.clear();  // Clear error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                        cout << "\n";
                    }
                }

                cout << "You've chosen to change to " << request.newClassCode << endl;
                cout << "\n";

                ChangeRequest changeRequest;
                changeRequest.requestType = "ChangeClassRequest";
                changeRequest.requestData = request;

                changeRequestQueue.push(changeRequest);
                studentHasPendingRequest[studentCode] = true;

                cout << "\033[1mChangeClass request enqueued for admin review.\033[0m" << endl << endl;
            }
        } else {
            cerr << "ERROR: Student not found." << endl << endl;
        }
    }
    backToMenu();
}

void Script::changeUC() {
    ChangeUcRequest request;

    clearScreen();
    int studentCode;
    cout << "Enter student code: ";
    cin >> studentCode;

    if (studentHasPendingRequest[studentCode]) {
        pendingRequest(studentCode);
    } else {
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
            cout << index << ". [Back]" << endl;
            cout << "\n";

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
            cout << "(Please be aware that if you change your UC, you will be assigned to a compatible class based on your schedule.)" << endl;

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
            studentHasPendingRequest[studentCode] = true;

            cout << "\033[1mChangeUc request enqueued for admin review.\033[0m" << endl << endl;
        } else {
            cerr << "ERROR: Student not found." << endl << endl;
        }
    }
    backToMenu();
}

void Script::leaveUCAndClass() {
    LeaveUcClassRequest request;

    clearScreen();
    int studentCode;
    cout << "Enter student code: ";
    cin >> studentCode;

    if (studentHasPendingRequest[studentCode]) {
        pendingRequest(studentCode);
    } else {
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
            cout << index << ". [Back]" << endl;
            cout << "\n";

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
            studentHasPendingRequest[studentCode] = true;

            cout << "\033[1mLeaveUcClass request enqueued for admin review.\033[0m" << endl << endl;
        } else {
            cerr << "ERROR: Student not found." << endl << endl;
        }
    }
    backToMenu();
}

void Script::joinUCAndClass() {
    JoinUcClassRequest request;

    clearScreen();
    int studentCode;
    cout << "Enter student code: ";
    cin >> studentCode;

    if (studentHasPendingRequest[studentCode]) {
        pendingRequest(studentCode);
    } else {
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
            cout << index << ". [Back]" << endl;
            cout << "\n";

            cout << "These are the UCs you are not registered in: " << endl;
            cout << "(Please be aware that when you join a new UC, you will be enrolled in a suitable class that aligns with your schedule.)" << endl;

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
                cout << "Choose the UC you'd wish to join: ";
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
            studentHasPendingRequest[studentCode] = true;

            cout << "\033[1mJoinUcClass request enqueued for admin review.\033[0m" << endl << endl;
        } else {
            cerr << "ERROR: Student not found." << endl << endl;
        }
    }
    backToMenu();
}

void Script::swapClassesBetweenStudents() {
    SwapClassesRequest request;

    clearScreen();
    int studentCode1, studentCode2;
    cout << "Enter student code (1): ";
    cin >> studentCode1;

    if (studentHasPendingRequest[studentCode1]) {
        pendingRequest(studentCode1);
    } else {
        cout << "Enter student code (2): ";
        cin >> studentCode2;

        if (studentCode2 == studentCode1) {
            cerr << "ERROR: You've entered the same student code twice." << endl;
            backToMenu();
            return;
        }
    }
    if (studentHasPendingRequest[studentCode2]) {
        pendingRequest(studentCode2);
    } else {
        Student *student1 = global.Students.searchByCode(studentCode1);
        Student *student2 = global.Students.searchByCode(studentCode2);

        if (student1 && student2) {
            request.student1 = student1;
            request.student2 = student2;
            clearScreen();

            cout << endl;
            cout << "Student Code: " << student1->StudentCode << endl;
            cout << "Student Name: " << student1->StudentName << endl;
            cout << "UCs and Classes: " << endl;

            set<string> sameUCs;
            for (const Class& ucToClass1 : student1->UcToClasses) {
                for (const Class& ucToClass2 : student2->UcToClasses) {
                    if (ucToClass1.UcCode == ucToClass2.UcCode) {
                        sameUCs.insert(ucToClass1.UcCode);
                        break;  // Break to the next UC after finding a match
                    }
                }
            }
            if (sameUCs.empty()) {
                cout << "ERROR: Students don't have common UCs." << endl;
                backToMenu();
                return;
            }

            int index = 1;
            map<int, Class> correspondingClass;
            for (const Class &ucToClass: student1->UcToClasses) {
                if (sameUCs.find(ucToClass.UcCode) != sameUCs.end()) {
                    cout << index << ". UcCode: " << ucToClass.UcCode << ", ClassCode: " << ucToClass.ClassCode << endl;
                    correspondingClass[index] = ucToClass;
                    index++;
                }
            }
            cout << "\n";

            cout << "Student Code: " << student2->StudentCode << endl;
            cout << "Student Name: " << student2->StudentName << endl;
            cout << "UCs and Classes: " << endl;

            index = 1;
            for (const Class& ucToClass : student2->UcToClasses) {
                if (sameUCs.find(ucToClass.UcCode) != sameUCs.end()) {
                    cout << index << ". UcCode: " << ucToClass.UcCode  << ", ClassCode: " << ucToClass.ClassCode << endl;
                    index++;
                }
            }
            cout << "\n";
            cout << "0. [Back]" << endl;
            cout << "\n";

            int choice;
            bool validChoice = false;

            while (!validChoice) {
                cout << "Choose the class of the UC you'd wish to swap: ";
                cin >> choice;
                //go back
                if (choice == 0) {
                    return;
                }
                // Check if user's choice is valid
                if (choice >= 1 && choice < index) {
                    const Class& selectedClass = correspondingClass[choice];
                    if (selectedClass.UcCode == " UP001") {
                        cerr << "ERROR: There are no other classes in UP001." << endl;
                        break;
                    }
                    for (const Class& ucToClass : student2->UcToClasses) {
                        if (ucToClass.UcCode == selectedClass.UcCode) {
                            request.ucCode = selectedClass.UcCode;
                            request.classCode1 = selectedClass.ClassCode;
                            request.classCode2 = ucToClass.ClassCode;
                            validChoice = true; // Set flag to exit the loop;
                        }
                    }
                    if (!validChoice) {
                        cerr << "ERROR: Student 2 does not belong to the same UC as Student 1, and therefore, they cannot swap classes." << endl << endl;
                        backToMenu();
                        return;
                    }
                } else {
                    cerr << "ERROR: Invalid input. Please enter a valid choice." << endl;
                    cin.clear();  // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                    cout << "\n";
                }
            }

            cout << "You've chosen " << request.ucCode << ": " << endl;
            cout << request.classCode1 << ", " << student1->StudentName << endl;
            cout << request.classCode2 << ", " << student2->StudentName << endl;
            cout << "\n";

            ChangeRequest changeRequest;
            changeRequest.requestType = "SwapClassesRequest";
            changeRequest.requestData = request;

            changeRequestQueue.push(changeRequest);
            studentHasPendingRequest[studentCode1] = true;
            studentHasPendingRequest[studentCode2] = true;

            cout << "\033[1mSwapClasses request enqueued for admin review.\033[0m" << endl << endl;
        } else {
            cerr << "ERROR: Either one or both students not found." << endl;
        }
    }
    backToMenu();
}

void Script::processRequest() {
    ChangeRequest request = changeRequestQueue.front();
    changeRequestQueue.pop();
    if (request.requestType == "ChangeClassRequest") {
        cout << "\033[1mChange Class\033[0m ";
        ChangeClassRequest changeRequest = get<ChangeClassRequest>(request.requestData);
        Change change(global);
        change.changeClass(*changeRequest.student, changeRequest.currentUcCode, changeRequest.currentClassCode, changeRequest.newClassCode);
        studentHasPendingRequest[changeRequest.student->StudentCode] = false;
        updateData(change.global);
        changeLogs.push_back(change.logEntry);
    }
    else if (request.requestType == "ChangeUcRequest") {
        cout << "\033[1mChange UC\033[0m ";
        ChangeUcRequest changeRequest = get<ChangeUcRequest>(request.requestData);
        Change change(global);
        change.changeUC(*changeRequest.student, changeRequest.currentUcCode, changeRequest.currentClassCode, changeRequest.newUcCode);
        studentHasPendingRequest[changeRequest.student->StudentCode] = false;
        updateData(change.global);
        changeLogs.push_back(change.logEntry);
    }
    else if (request.requestType == "LeaveUcClassRequest") {
        cout << "\033[1mLeave UC and Class\033[0m ";
        LeaveUcClassRequest changeRequest = get<LeaveUcClassRequest>(request.requestData);
        Change change(global);
        change.leaveUCAndClass(*changeRequest.student, changeRequest.currentUcCode, changeRequest.currentClassCode);
        studentHasPendingRequest[changeRequest.student->StudentCode] = false;
        updateData(change.global);
        changeLogs.push_back(change.logEntry);
    }
    else if (request.requestType == "JoinUcClassRequest") {
        cout << "\033[1mJoin UC and Class\033[0m ";
        JoinUcClassRequest changeRequest = get<JoinUcClassRequest>(request.requestData);
        Change change(global);
        change.joinUCAndClass(*changeRequest.student, changeRequest.newUcCode);
        studentHasPendingRequest[changeRequest.student->StudentCode] = false;
        updateData(change.global);
        changeLogs.push_back(change.logEntry);
    }
    else if (request.requestType == "SwapClassesRequest") {
        cout << "\033[1mSwap Classes\033[0m ";
        SwapClassesRequest changeRequest = get<SwapClassesRequest>(request.requestData);
        Change change(global);
        change.swapClassesBetweenStudents(*changeRequest.student1, changeRequest.ucCode, changeRequest.classCode1, *changeRequest.student2, changeRequest.classCode2);
        studentHasPendingRequest[changeRequest.student1->StudentCode] = false;
        studentHasPendingRequest[changeRequest.student2->StudentCode] = false;
        updateData(change.global);
        changeLogs.push_back(change.logEntry);
    }

    cout << endl;
}

void Script::processNextChangeRequest() {
    clearScreen();

    drawBox("Change Requests");

    if (!changeRequestQueue.empty()) {
        cout << "1. ";
        processRequest();
    } else {
        cout << "No requests pending." << endl;
        cout << "\n";
    }
    backToMenu();
}

void Script::processAllChangeRequests() {
    clearScreen();

    drawBox("Change Requests");
    int i = 1;
    while (!changeRequestQueue.empty()) {
        cout << i++ << ". ";
        processRequest();
    }
    if (changeRequestQueue.empty()) {
        cout << "No requests pending." << endl;
        cout << "\n";
    }
    backToMenu();
}

void Script::changeLogsMenu() {
    vector<MenuItem> occupationMenu = {
            {"\033[1mAll Change Logs\033[0m", &Script::allChangeLogs},
            {"\033[1mSuccessful Change Logs\033[0m", &Script::successfulChangeLogs},
            {"\033[1mUnsuccessful Change Logs\033[0m", &Script::failedChangeLogs},
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
            break;
        } else if (choice >= 1 && choice <= occupationMenu.size()) {
            (this->*occupationMenu[choice - 1].action)();
        }
    }
}

void Script::allChangeLogs() {
    clearScreen();
    drawBox("All Change Logs");
    if (changeLogs.empty()) {
        cout << "NO LOGS" << endl;
    } else {
        int index = 1;
        for (const auto &entry: changeLogs) {
            cout << index++ << ". " << entry.requestType << " (" << entry.timestamp << ")" << endl;
            cout << "   Student Code: " << entry.studentCode << endl;
            cout << "   Student Name: " << entry.studentName << endl;
            cout << "   Current UC Code: " << entry.currentUcCode << " , Class Code: " << entry.currentClassCode
                 << endl;
            cout << "   New UC Code: " << entry.newUcCode << " , Class Code: " << entry.newClassCode << endl;
            cout << "   State: ";
            if (entry.accepted) {
                cout << "Accepted" << endl;
            } else {
                cout << "Denied" << endl;
            }
            cout << "   Notes: " << entry.extraNotes << endl << endl;
        }
    }
    backToMenu();
}

void Script::successfulChangeLogs() {
    while (true){
        clearScreen();
        drawBox("Successful Changes Logs");
        if (changeLogs.empty()) {
            cout << "NO SUCCEED CHANGES " << endl;
            break;
        }
        else {
            int index = 1;
            stringstream out;
            for (const auto &entry: changeLogs) {
                if (entry.accepted){
                    out << index++ << ". " << entry.requestType << " (" << entry.timestamp << ")" << endl;
                    out << "   Student: " << entry.studentCode << endl;
                    out << "   Student Name: " << entry.studentName << endl;
                    out << "   Current UC code: " << entry.currentUcCode << " , Class Code: " << entry.currentClassCode
                         << endl;
                    out << "   New UC code: " << entry.newUcCode << " , Class Code: " << entry.newClassCode << endl;
                    out << "   State: Accepted" << endl;
                    out << "   Notes: " << entry.extraNotes << endl << endl;
                }
            }
            string output = out.str();
            if (output.empty()) {
                cout << "NO SUCCEED CHANGES " << endl;
                break;
            }
            cout << output;
        }
        int choice;
        cout << "MENU:" << endl;
        cout << "1. \033[1mUNDO the last change\033[0m" << endl << "2. [Back]"<< endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice == 2) {
            return;
        }
        else if (choice == 1) {
            undoAction();
            for (auto i = changeLogs.size()-1; i >= 0; i--) {
                if (changeLogs[i].accepted) {
                    changeLogs[i].accepted = false;
                    changeLogs[i].extraNotes = "REQUEST RESULT REVERSED BY ADMINISTRATOR";
                    break;
                }
            }
            cout << endl << "Last Change request reversed successfully" << endl;
            break;
        }
    }
    backToMenu();
}

void Script::failedChangeLogs() {
    clearScreen();
    drawBox("Unsuccessful Changes Logs");
    if (changeLogs.empty()) {
        cout << "NO FAILED CHANGES " << endl;
    } else {
        int index = 1;
        stringstream out;
        for (const auto &entry: changeLogs) {
            if (!entry.accepted){
                out << index++ << ". " << entry.requestType << " (" << entry.timestamp << ")" << endl;
                out << "   Student: " << entry.studentCode << endl;
                out << "   Student Name: " << entry.studentName << endl;
                out << "   Current UC code: " << entry.currentUcCode << " , Class Code: " << entry.currentClassCode
                     << endl;
                out << "   New UC code: " << entry.newUcCode << " , Class Code: " << entry.newClassCode << endl;
                out << "   State: Denied" << endl;
                out << "   Notes: " << entry.extraNotes << endl << endl;
            }
        }
        string output = out.str();
        if (output.empty()) {
            cout << "NO SUCCEED CHANGES " << endl;
        }
        else {
            cout << output;
        }
    }
    backToMenu();
}

void Script::printToFile() {
    global.Students.saveToCSV("students_updated.csv");
    cout << "File \"students_updated.csv\" outputted successful" << endl;
    backToMenu();
}
