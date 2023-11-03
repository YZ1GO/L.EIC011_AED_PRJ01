/**
 * @file Consult.cpp
 *
 * Implementation of the classes and functions defined in Consult.h.
 */

#include "Consult.h"
#include <limits>

/**
 * @brief Default constructor for the Consult class.
 * Initializes the Consult object.
 */
Consult::Consult() {}

/**
 * @brief Parameterized constructor for the Consult class.
 * Initializes the Consult object with the provided Global data.
 *
 * @param global The Global data to initialize the Consult.
 */
Consult::Consult(Global global) {
    globalData = global;
}

/**
 * @brief Updates the Consult's data with new Global data.
 *
 * @param data A Global object containing new data.
 */
void Consult::updateData(Global data) {
    globalData = data;
}

/**
 * @brief Lists students by name.
 */
void Consult::listStudentsByName() {
    cout << "Enter the student you want to search for: ";
    string searchName;
    cin >> searchName;

    vector<Student> matchingStudents;

    // Search for students with the exact same name using the binary search tree
    globalData.Students.searchAllByName(searchName, matchingStudents);

    // Student not found
    if (matchingStudents.empty()) {
        cerr << "ERROR: Student with name: " << searchName << " not found." << endl;
        return;
    }

    // List all students with "searchName" and allow user to select one
    system("clear"); // Unix-like system
    cout << "\033[1mSearch criteria:\033[0m (Name: " << searchName << ")" << endl;
    cout << "\n";
    cout << "\033[1mResults of the search:\033[0m " << endl;
    for (int i = 0; i < matchingStudents.size(); i++) {
        cout << i + 1 << ". " << "Student Code: " << matchingStudents[i].StudentCode
             << "     Name: " << matchingStudents[i].StudentName << endl;
    }
    cout << "\n";

    int choice;
    bool validChoice = false;

    while (!validChoice) {
        cout << "Enter the number of the student you want to view: ";
        cin >> choice;

        // Check if user's choice is valid
        if (choice >= 1 && choice <= matchingStudents.size()) {
            system("clear");
            validChoice = true; // Set flag to exit the loop
        } else {
            cerr << "Invalid input. Please enter a valid number." << endl;
            cin.clear();  // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "\n";
        }
    }

    // Output chosen student's information
    const Student chosenStudent = matchingStudents[choice - 1];
    cout << "\n";
    cout << "\033[1mSelected student information:\033[0m " << endl;
    cout << "Student Code: " << chosenStudent.StudentCode << endl;
    cout << "Student Name: " << chosenStudent.StudentName << endl;
    cout << "UCs and Classes: " << endl;
    for (const Class& ucToClass : chosenStudent.UcToClasses) {
        cout << "UcCode: " << ucToClass.UcCode  << ", ClassCode: " << ucToClass.ClassCode << endl;
    }
    cout << "\n";
}

/**
 * @brief Finds a student by code.
 */
void Consult::findStudentByCode() {
    int searchCode;
    bool validInput = false;

    while (!validInput) {
        cout << "Enter the student code of the student you want to search for: ";
        cin >> searchCode;

        // Check if user input is a 9 digit student code
        if (cin.peek() == '\n' && to_string(searchCode).length() == 9) {
            validInput = true; // Set flag to exit the loop
        } else {
            cerr << "Invalid input. Please enter a valid student code." << endl;
            cin.clear();  // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "\n";
        }
    }

    // Calls searchByCode function defined in Student BST class
    Student* student = globalData.Students.searchByCode(searchCode);

    if (student) {
        system("clear");
        cout << "\033[1mSearch criteria:\033[0m (Code: " << searchCode << ")" << endl;

        // Output chosen student's information
        cout << "\n";
        cout << "\033[1mSelected student information:\033[0m " << endl;
        cout << "Student Code: " << student->StudentCode << endl;
        cout << "Student Name: " << student->StudentName << endl;
        cout << "UCs and Classes: " << endl;
        for (const Class& ucToClass : student->UcToClasses) {
            cout << "UcCode: " << ucToClass.UcCode  << ", ClassCode: " << ucToClass.ClassCode << endl;
        }
        cout << "\n";
    } else {
        cerr << "ERROR: Student with code: " << searchCode << " not found." << endl;
    }
}

/**
 * @brief Prints the schedule for a given set of schedules.
 *
 * @param schedules A vector of Schedule objects to print.
 */
void Consult::printSchedule(vector<Schedule> schedules) {
    sort(schedules.begin(), schedules.end());

    string weekDay;
    for (const Schedule& schedule : schedules){
        if (weekDay != schedule.WeekDay){
            weekDay = schedule.WeekDay;
            cout << "-------------------------------------------------" << endl;
            cout << weekDay << endl;
            cout << "-------------------------------------------------" << endl;
        }
        cout << "     " << schedule.UcToClasses.UcCode << ", " << schedule.UcToClasses.ClassCode << "" << endl;
        cout << "   Start Hour: " << floatToHours(schedule.StartHour) << endl;
        cout << "     End Hour: " << floatToHours(schedule.StartHour + schedule.Duration) << endl;
        cout << "     Duration: " << schedule.Duration << "h" << endl;
        cout << "         Type: " << schedule.Type << endl << endl;
    }
    cout << "-----------------END OF THE LIST-----------------" << endl;
}

/**
 * @brief Retrieves the schedule of a given student.
 *
 * @param student The Student for which to retrieve the schedule.
 * @return A vector of Schedule objects representing the student's schedule.
 */
vector<Schedule> Consult::getStudentSchedule(const Student& student) {
    vector<Schedule> studentSchedule;
    // Loops through all classes student is enrolled in
    for (const Class &studentClass: student.UcToClasses) {
        // Loops through all schedules
        for (const Schedule& schedule: globalData.Schedules) {
            // Find student's schedules
            if (studentClass.ClassCode == schedule.UcToClasses.ClassCode && studentClass.UcCode == schedule.UcToClasses.UcCode) {
                // Populate the vector that contains student's schedules
                studentSchedule.push_back(schedule);
            }
        }
    }
    // Sort the vector that contains student's schedules
    sort(studentSchedule.begin(), studentSchedule.end());
    return studentSchedule;
}

/**
 * @brief Consults the schedule of a specific student.
 */
void Consult::consultTheScheduleOfStudent() {
    cout << "CONSULT A STUDENT SCHEDULE" << endl;
    cout << "Enter the student code for the schedule you want search for: ";
    int studentCode;

    if (!(cin >> studentCode) || cin.peek() != '\n' || to_string(studentCode).length() != 9) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "ERROR: Invalid student code [press enter]" << endl;
        return;
    }

    Student* student = globalData.Students.searchByCode(studentCode);

    // Find the student with the given student code
    if (student) {
        cout << "Student Code: " << student->StudentCode << endl;
        cout << "Student Name: " << student->StudentName << endl;
        printSchedule(getStudentSchedule(*student));
    } else {
        cerr << "ERROR: Student with code " << studentCode << " not found." << endl;
    }
}

/**
 * @brief Consults the schedule of a specific class.
 */
void Consult::consultTheScheduleOfClass() {
    cout << "CONSULT A CLASS SCHEDULE" << endl;
    cout << "Enter the class code for the schedule you want search for: ";
    string classCode;
    cin >> classCode;

    if (classCode.length() != 7) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "ERROR: Invalid class code [press enter]" << endl;
        return;
    }

    vector<Schedule> schedules;
    // Loop through all schedules
    for (const Schedule& schedule : globalData.Schedules){
        // Find the given class schedules
        if (classCode == schedule.UcToClasses.ClassCode) {
            // Populate the vector that contains class schedules
            schedules.push_back(schedule);
        }
    }

    if (!schedules.empty()) {
        printSchedule(schedules);
    } else {
        cerr << "ERROR: Class with classCode " << classCode << " not found." << endl;
    }
}

/**
 * @brief Lists students registered in at least N UCs.
 */
void Consult::listOfStudentsInAtLeastNUCs() {
    cout << "\033[1mEnter the number of students registered in at least \n" <<
         "how many UCs you want to search for: \033[0m";
    int n;
    if (!(cin >> n)) {
        // Invalid input (not an integer)
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "ERROR: N should be a integer number [press enter]" << endl;
        return;
    }

    int result = 0;
    set<Student> matchingStudents;

    globalData.Students.searchStudentsInAtLeastNUCs(n, matchingStudents);

    cout << "Number of students registered in at least [" << n
         << "] UCs: " << matchingStudents.size() << endl;

    int i = 1;
    for (const Student& student : matchingStudents) {
        cout << i++ << ". [" << student.UcToClasses.size()
             << "] "<< student.StudentCode << " "
             << student.StudentName << endl;
    }
}

/**
 * @brief Lists students in a specific class, UC, or year, and returns the list of students.
 *
 * @param identifier The identifier (class, UC, year) for which to list students.
 * @param searchCriteria A function to filter students based on the identifier.
 */
void Consult::listOfStudentsInXBySortOrder(const string& identifier, const function<bool(const Class&)> searchCriteria) {
    set<Student> students;

    globalData.Students.searchStudentsWithin(searchCriteria, students);

    if (students.empty()) {
        cerr << "ERROR: " << identifier << " not valid or empty." << endl;
        return;
    }

    cout << students.size() << " students in " << identifier << endl;
    cout << "\n";

    int orderChoice;
    do {
        cout << "1. Ascending order" << endl;
        cout << "2. Descending order" << endl;
        cout << "\n";
        cout << "Choose the order: ";
        cin >> orderChoice;
    } while (orderChoice != 1 && orderChoice != 2);

    int index = 1;

    if (orderChoice == 1) {
        cout << " [Ascending order]:" << endl;
        cout << "\n";
        for (const Student& student : students) {
            cout << index << ". " << student.StudentCode << " " << student.StudentName << endl;
            index++;
        }
    } else {
        cout << " [Descending order]:" << endl;
        cout << "\n";
        for (set<Student>::reverse_iterator rit = students.rbegin(); rit != students.rend(); ++rit) {
            cout << index << ". " << rit->StudentCode << " " << rit->StudentName << endl;
            index++;
        }
    }
}

/**
 * @brief Lists students in a specific class.
 */
void Consult::listOfStudentsInClass() {
    cout << "CONSULT THE LIST OF STUDENTS IN CLASS" << endl;
    cout << "Enter the class code you want search for: ";
    string classCode;
    cin >> classCode;

    if (classCode.length() != 7) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "ERROR: Invalid class code [press enter]" << endl;
        return;
    }

    auto searchCriteria = [&classCode](const Class& ucClass) {
        return ucClass.ClassCode == classCode;
    };
    listOfStudentsInXBySortOrder("class " + classCode, searchCriteria);
}

/**
 * @brief Lists students in a specific UC.
 */
void Consult::listOfStudentsInUc() {
    cout << "CONSULT THE LIST OF STUDENTS IN UC" << endl;
    cout << "Enter the UC code you want search for: ";
    string ucCode;
    cin >> ucCode;

    auto searchCriteria = [&ucCode](const Class& ucClass) {
        return ucClass.UcCode == ucCode;
    };
    listOfStudentsInXBySortOrder("UC " + ucCode, searchCriteria);
}

/**
 * @brief Lists students in a specific year.
 */
void Consult::listOfStudentsInYear() {
    cout << "CONSULT THE LIST OF STUDENTS IN YEAR" << endl;
    cout << "Enter the year you want search for: ";
    string year;
    if (!(cin >> year) || (year != "1" && year != "2" && year != "3")) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "ERROR: Invalid year [press enter]" << endl;
        return;
    }

    auto searchCriteria = [&year](const Class& ucClass) {
        return (ucClass.ClassCode[0] == year[0]);
    };
    listOfStudentsInXBySortOrder("year " + year, searchCriteria);
}

/**
 * @brief Shows the sorting menu based on the provided students count and identifier.
 *
 * @param studentsCount A map of identifier (class, UC, year) to the number of students.
 * @param identifier The identifier for which to show the sorting menu.
 */
void Consult::showSortingMenu(const map<string, int>& studentsCount, const string& identifier) {
    vector<pair<string, int>> result(studentsCount.begin(), studentsCount.end());

    // Create a map to store the display strings.
    map<int, string> displayOrder;
    displayOrder[1] = " code ascending order";
    displayOrder[2] = " code descending order";
    displayOrder[3] = " occupation ascending order";
    displayOrder[4] = " occupation descending order";

    cout << "Choose a sorting option: " << endl;
    cout << "1. by " << identifier << displayOrder[1] << endl;
    cout << "2. by " << identifier << displayOrder[2] << endl;
    cout << "3. by " << identifier << displayOrder[3] << endl;
    cout << "4. by " << identifier << displayOrder[4] << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
        case 2:
            if (identifier == "class") {
                sortClassByYear(result, choice == 1); // Sort classes by code, ascending if choice == 1, otherwise descending
                break;
            }
            if (identifier == "year") {
                if (choice == 1) {
                    sort(result.begin(), result.end()); // Sort years by ascending order
                } else {
                    sort(result.rbegin(), result.rend()); // Sort years by descending order
                }
                break;
            }
            sortByCode(result, choice == 1); // True case 1, False case 2
            break;
        case 3:
        case 4:
            sortByOccupation(result, choice == 3); // True case 3, False case 4
            break;
        default:
            cerr << "ERROR: Invalid choice. Please choose a valid option (1-4)." << endl;
            return;
    }

    cout << "[" << displayOrder[choice] << " ]:" << endl;

    if (identifier == "year") {
        for (const auto& entry : result) {
            cout << "Year " << entry.first << ": " << entry.second << " students" << endl;
        }
    } else {
        for (const auto& entry : result) {
            cout << entry.first << ": " << entry.second << " students" << endl;
        }
    }
}

/**
 * @brief Consults the occupation in classes.
 */
void Consult::occupationInClasses() {
    map<string, int> studentsCount;
    StudentBST& studentBST = globalData.Students;
    set<string> processedClassCodes; // Track the processed class codes

    for (const auto& ucClass : globalData.Classes) {
        string classCode = ucClass.ClassCode;
        // Check if the class code has already been processed
        if (processedClassCodes.find(classCode) == processedClassCodes.end()) {
            int count = studentBST.countStudentsInClass(classCode);
            studentsCount[classCode] = count;

            // Add the class code to the processed set
            processedClassCodes.insert(classCode);
        }
    }

    showSortingMenu(studentsCount, "class");
}

/**
 * @brief Consults the occupation in UCs.
 */
void Consult::occupationInUcs() {
    map<string, int> studentsCount;
    StudentBST& studentBST = globalData.Students;
    set<string> processedUCCodes; // Track the processed UC codes

    for (const auto& ucClass : globalData.Classes) {
        string ucCode = ucClass.UcCode;
        // Check if the UC code has already been processed
        if (processedUCCodes.find(ucCode) == processedUCCodes.end()) {
            int count = studentBST.countStudentsInUC(ucCode); // Implement a countStudentsInUC function
            studentsCount[ucCode] = count;

            // Add the UC code to the processed set
            processedUCCodes.insert(ucCode);
        }
    }

    showSortingMenu(studentsCount, "UC");
}

/**
 * @brief Consults the occupation in years.
 */
void Consult::occupationInYears() {
    map<string, int> studentsCount;
    StudentBST& studentBST = globalData.Students;
    set<string> processedYears; // Track the processed years

    for (const auto& ucClass : globalData.Classes) {
        string classCode = ucClass.ClassCode;

        // Extract the year from the first character of the class code
        if (!classCode.empty() && classCode[0] >= '1' && classCode[0] <= '3') {
            string year(1, classCode[0]); // Extract the year as a string

            // Check if the year has not already been processed
            if (processedYears.find(year) == processedYears.end()) {
                int count = studentBST.countStudentsInYear(year); // Implement a countStudentsInYear function that accepts a string
                studentsCount[year] = count;

                // Add the year to the processed set
                processedYears.insert(year);
            }
        }
    }

    showSortingMenu(studentsCount, "year");
}

/**
 * @brief Consults the occupation by sorting order based on the provided identifier type and identifier.
 *
 * @param identifierType The type of identifier (UC, year) for sorting.
 * @param identifier The specific identifier to sort by.
 * @param studentsCount A map of identifier (UC, year) to the number of students.
 */
void Consult::consultOccupationBySortOrder(const string& identifierType, const string& identifier, const map<string, int>& studentsCount) {
    vector<pair<string, int>> result(studentsCount.begin(), studentsCount.end());

    // Create a map to store the display strings.
    map<int, string> displayOrder;
    displayOrder[1] = " code ascending order";
    displayOrder[2] = " code descending order";
    displayOrder[3] = " occupation ascending order";
    displayOrder[4] = " occupation descending order";

    cout << "Choose a sorting option: " << endl;
    cout << "1. by " << identifierType << displayOrder[1] << endl;
    cout << "2. by " << identifierType << displayOrder[2] << endl;
    cout << "3. by " << identifierType << displayOrder[3] << endl;
    cout << "4. by " << identifierType << displayOrder[4] << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
        case 2:
            sortByCode(result, choice == 1); // True case 1, False case 2
            break;
        case 3:
        case 4:
            sortByOccupation(result, choice == 3); // True case 3, False case 4
            break;
        default:
            cerr << "ERROR: Invalid choice. Please choose a valid option (1-4)." << endl;
            return;
    }

    string phrase = (identifierType == "class") ? "Classes and Student Counts for " : "UCs and Student Counts for year ";

    cout << phrase << identifier << " [" << displayOrder[choice] << " ]:" << endl;

    for (const auto& entry : result) {
        cout << entry.first << ": " << entry.second << " students" << endl;
    }
}

/**
 * @brief Consults all classes occupation for a specific UC.
 */
void Consult::consultUcOccupation() {
    string ucCode;
    cout << "Enter the UC code (L.EIC001-L.EIC005, L.EIC011-L.EIC015, L.EIC021-L.EIC025, UP001): ";
    if (!(cin >> ucCode)) {
        // Invalid input (not an integer)
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    map<string, int> classStudentsCount;

    globalData.Students.getStudentsCountInClass(ucCode, classStudentsCount);

    if (classStudentsCount.empty()){
        cerr << "ERROR: Invalid UC Code or no students registered in UC, please Enter a valid UC (L.EIC001-L.EIC005 / L.EIC011-L.EIC015 / L.EIC021-L.EIC025 / UP001)" << endl;
        return;
    }

    consultOccupationBySortOrder("class", ucCode, classStudentsCount);
}

/**
 * @brief Retrieves a set of UCs for a given year.
 *
 * @param year The year for which to retrieve UCs.
 * @return A set of UC codes for the specified year.
 */
set<string> Consult::ucsOfTheYear(int year){
    set<string> ucsOfTheYear;

    for (auto classObj : globalData.Classes){
        if (classObj.ClassCode[0] == '0' + year){
            ucsOfTheYear.insert(classObj.UcCode);
        }
    }
    return ucsOfTheYear;
}

/**
 * @brief Consults the year occupation.
 */
void Consult::consultYearOccupation() {
    int year;
    cout << "Enter the year (1-3) you want to consult: ";
    cin >> year;

    if (year < 1 || year > 3) {
        cerr << "ERROR: Invalid year, please ENTER a valid year (1-3) " << endl;
        return;
    }

    set<string> ucsOfTheYear_ = ucsOfTheYear(year);

    if (ucsOfTheYear_.empty()) {
        cerr << "ERROR: No UCs found for the given year." << endl;
        return;
    }

    // Create a map to store UCs and their corresponding student counts
    map<string, int> ucStudentsCount;

    for (const auto& uc : ucsOfTheYear_) {
        globalData.Students.getStudentsCountInUc(uc, ucStudentsCount);
    }

    string year_ = to_string(year);

    consultOccupationBySortOrder("UC", year_, ucStudentsCount);
}