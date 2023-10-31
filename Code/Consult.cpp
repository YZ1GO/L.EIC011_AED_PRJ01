#include "Consult.h"
#include <limits>

using namespace std;

Consult::Consult() {}

void Consult::set_data(Global global) {
    globalData = global;
}

void Consult::listStudentsByName() {
    cout << "Enter the student you want to search for: ";
    string searchName;
    cin >> searchName;

    vector<Student> matchingStudents;

    // Search for students with the exact same name using the binary search tree
    globalData.Students.searchAllByName(searchName, matchingStudents);

    // Student not found
    if (matchingStudents.empty()) {
        cout << "Student with name: " << searchName << " not found." << endl;
        return;
    }

    // List all students with "searchName" and allow user to select one
    //system("cls"); // Windows
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
            cout << "Invalid input. Please enter a valid number." << endl;
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
            cout << "Invalid input. Please enter a valid student code." << endl;
            cin.clear();  // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
            cout << "\n";
        }
    }

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
        cout << "Student with code: " << searchCode << " not found." << endl;
    }
}

//auxiliary function that prints the information a schedule
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
        cout << "     Duration: " << schedule.Duration << " hours" << endl;
        cout << "         Type: " << schedule.Type << endl << endl;
    }
    cout << "-----------------END OF THE LIST-----------------" << endl;
}

void Consult::consultTheScheduleOfStudent() {
    cout << "CONSULT A STUDENT SCHEDULE" << endl;
    cout << "Enter the student code for the schedule you want search for: ";
    int studentCode;
    if (!(cin >> studentCode)) {
        // Invalid input (not an integer)
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: invalid student code [press enter]" << endl;
        return;
    }

    Student* student = globalData.Students.searchByCode(studentCode);

    // Find the student with the given student code
    if (student) {
        cout << "Student Code: " << student->StudentCode << endl;
        cout << "Student Name: " << student->StudentName << endl;

        vector<Schedule> schedules;

        // Iterate through the classes for this student
        for (const Class &studentClass: student->UcToClasses) {
            for (const Schedule &schedule: globalData.Schedules) {
                if (checkIfClassCodeEqual(studentClass.ClassCode, schedule.UcToClasses.ClassCode)
                    && checkIfUCCodeEqual(studentClass.UcCode, schedule.UcToClasses.UcCode)) {
                    schedules.push_back(schedule);
                }
            }
        }

        printSchedule(schedules);
    } else {
        cout << "Student with code " << studentCode << " not found." << endl;
    }
}

void Consult::consultTheScheduleOfStudent(const string& studentName) {

}

void Consult::consultTheScheduleOfClass() {
    cout << "CONSULT A CLASS SCHEDULE" << endl;
    cout << "Enter the class code for the schedule you want search for: ";
    string classCode;
    if (!(cin >> classCode)) {
        // Invalid input (not an integer)
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: invalid class code [press enter]" << endl;
        return;
    }

    vector<Schedule> schedules;
    for (const Schedule& schedule : globalData.Schedules){
        if (checkIfClassCodeEqual(classCode, schedule.UcToClasses.ClassCode)){
            schedules.push_back(schedule);
        }
    }

    if (!schedules.empty()) {
        printSchedule(schedules);
    } else {
        cout << "Class with classCode " << classCode << " not found." << endl;
    }
}

//Gives the number and a List of students registered in at least N UCs
void Consult::listOfStudentsInAtLeastNUCs() {
    cout << "Enter the number of students registered in at least \n" <<
         "how many UCs you want to search for: ";
    int n;
    if (!(cin >> n)) {
        // Invalid input (not an integer)
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: N should be a integer number [press enter]" << endl;
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

void Consult::listOfStudentsInXBySortOrder(const string& identifier, const function<bool(const Class&)> searchCriteria) {
    set<Student> students;

    globalData.Students.searchStudentsWithin(searchCriteria, students);

    if (students.empty()) {
        cout << "ERROR: " << identifier << " not valid or empty." << endl;
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

void Consult::listOfStudentsInClass() {
    cout << "CONSULT THE LIST OF STUDENTS IN CLASS" << endl;
    cout << "Enter the class code for the class you want search for: ";
    string classCode;
    if (!(cin >> classCode)) {
        // Invalid input (not an integer)
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: invalid class code [press enter]" << endl;
        return;
    }

    auto searchCriteria = [&classCode](const Class& ucClass) {
        return checkIfClassCodeEqual(ucClass.ClassCode, classCode);
    };
    listOfStudentsInXBySortOrder("class " + classCode, searchCriteria);
}

void Consult::listOfStudentsInUc() {
    cout << "CONSULT THE LIST OF STUDENTS IN UC" << endl;
    cout << "Enter the UC code for the UC you want search for: ";
    string ucCode;
    if (!(cin >> ucCode)) {
        // Invalid input (not an integer)
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: invalid UC code [press enter]" << endl;
        return;
    }

    auto searchCriteria = [&ucCode](const Class& ucClass) {
        return checkIfUCCodeEqual(ucClass.UcCode, ucCode);
    };
    listOfStudentsInXBySortOrder("uc " + ucCode, searchCriteria);
}

void Consult::listOfStudentsInYear() {
    cout << "CONSULT THE LIST OF STUDENTS IN YEAR" << endl;
    cout << "Enter the year you want search for: ";
    string year;
    if (!(cin >> year)) {
        // Invalid input (not an integer)
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: invalid UC code [press enter]" << endl;
        return;
    }

    auto searchCriteria = [&year](const Class& ucClass) {
        return (ucClass.ClassCode[0] == year[0]);
    };
    listOfStudentsInXBySortOrder("year " + year, searchCriteria);
}

void Consult::occupationInClasses() {
    StudentBST& studentBST = globalData.Students;
    set<string> processedClassCodes; // Track the processed class codes

    for (const auto& ucClass : globalData.Classes) {
        string classCode = ucClass.ClassCode;

        // Trim leading and trailing white spaces from the class code
        classCode.erase(classCode.begin(), find_if(classCode.begin(), classCode.end(),
                                                   [](char c) { return !isspace(c); }));
        classCode.erase(find_if(classCode.rbegin(), classCode.rend(),
                                [](char c) { return !isspace(c); }).base(), classCode.end());

        // Check if the class code has already been processed
        if (processedClassCodes.find(classCode) == processedClassCodes.end()) {
            int count = studentBST.countStudentsInClass(classCode);
            cout << classCode << ": " << count << " students" << endl;

            // Add the class code to the processed set
            processedClassCodes.insert(classCode);
        }
    }
}

void Consult::occupationInUcs() {
    StudentBST& studentBST = globalData.Students;
    set<string> processedUCCodes; // Track the processed UC codes

    for (const auto& ucClass : globalData.Classes) {
        string ucCode = ucClass.UcCode;

        // Trim leading and trailing white spaces from the UC code
        ucCode.erase(ucCode.begin(), find_if(ucCode.begin(), ucCode.end(),
                                             [](char c) { return !isspace(c); }));
        ucCode.erase(find_if(ucCode.rbegin(), ucCode.rend(),
                             [](char c) { return !isspace(c); }).base(), ucCode.end());

        // Check if the UC code has already been processed
        if (processedUCCodes.find(ucCode) == processedUCCodes.end()) {
            int count = studentBST.countStudentsInUC(ucCode); // Implement a countStudentsInUC function
            cout << ucCode << ": " << count << " students" << endl;

            // Add the UC code to the processed set
            processedUCCodes.insert(ucCode);
        }
    }
}

void Consult::occupationInYears() {
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
                cout << "Year " << year << ": " << count << " students" << endl;

                // Add the year to the processed set
                processedYears.insert(year);
            }
        }
    }
}

void Consult::consultOccupationBySortOrder(const string& identifierType, const string& identifier, const map<string, int>& studentsCount) {
    vector<pair<string, int>> result(studentsCount.begin(), studentsCount.end());

    // Create a map to store the display strings.
    map<int, string> displayOrder;
    displayOrder[1] = "Code ascending order";
    displayOrder[2] = "Code descending order";
    displayOrder[3] = "Occupation ascending order";
    displayOrder[4] = "Occupation descending order";

    cout << "Choose a sorting option: " << endl;
    cout << "1. By " << identifierType << displayOrder[1] << endl;
    cout << "2. By " << identifierType << displayOrder[2] << endl;
    cout << "3. By " << identifierType << displayOrder[3] << endl;
    cout << "4. By " << identifierType << displayOrder[4] << endl;

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
            cout << "Invalid choice. Please choose a valid option (1-4)." << endl;
            return;
    }

    string phrase = (identifierType == "class") ? "Classes and Student Counts for " : "UCs and Student Counts for year ";

    cout << phrase << identifier << " [" << displayOrder[choice] << "]:" << endl;

    for (const auto& entry : result) {
        cout << entry.first << ": " << entry.second << " students" << endl;
    }
}

void Consult::consultUcOccupation(const string& ucCode) {
    map<string, int> classStudentsCount;

    globalData.Students.getStudentsCountInClass(ucCode, classStudentsCount);

    if (classStudentsCount.empty()){
        cout << "ERROR: invalid UC Code or no students registered in UC, please Enter a valid UC (L.EIC001-L.EIC005 / L.EIC011-L.EIC015 / L.EIC021-L.EIC025)" << endl;
        return;
    }

    consultOccupationBySortOrder("class", ucCode, classStudentsCount);
}

set<string> Consult::ucsOfTheYear(int year){
    set<string> ucsOfTheYear;

    for (auto classObj : globalData.Classes){
        if (classObj.ClassCode[0] == '0' + year){
            ucsOfTheYear.insert(classObj.UcCode);
        }
    }
    return ucsOfTheYear;
}

void Consult::consultYearOccupation(const int& year) {
    if (year < 1 || year > 3) {
        cout << "ERROR: invalid year, please ENTER a valid year (1-3) " << endl;
        return;
    }

    set<string> ucsOfTheYear_ = ucsOfTheYear(year);

    if (ucsOfTheYear_.empty()) {
        cout << "No UCs found for the given year." << endl;
        return;
    }

    // Create a map to store UCs and their corresponding student counts
    map<string, int> ucStudentsCount;

    for (const auto& uc : ucsOfTheYear_) {
        globalData.Students.getStudentsCountInUc(uc, ucStudentsCount);
    }

    string year_ = to_string(year);

    consultOccupationBySortOrder("uc", year_, ucStudentsCount);
}




int main() {
    System data;
    Global global = {data.get_Classes(),data.get_Schedules(),data.get_Students()};
    Consult consult;
    consult.set_data(global);

    //consult.consultTheScheduleOfClass();
    //consult.consultTheScheduleOfStudent();
    //consult.listStudentsByName();
    //consult.findStudentByCode();
    //consult.listOfStudentsInAtLeastNUCs();

    //consult.listOfStudentsInClass();
    //consult.listOfStudentsInUc();
    //consult.listOfStudentsInYear();

    //consult.occupationInClasses();
    //consult.occupationInUcs();
    //consult.occupationInYears();

    consult.consultUcOccupation("L.EIC014");
    //consult.consultYearOccupation(1);
    return 0;
}