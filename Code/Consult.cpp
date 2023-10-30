#include "Consult.h"
#include <limits>

using namespace std;

Consult::Consult() {}

void Consult::set_data(Global global) {
    globalData = global;
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

void Consult::consultTheScheduleOfStudent(int studentCode) {
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

void Consult::consultTheScheduleOfClass(const string& classCode) {
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
void Consult::consultListOfStudentsInAtLeastNUCs(const int n) {
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

void Consult::consultStudentsIn(const string& identifier, const function<bool(const Class&)> searchCriteria) {
    set<Student> students;

    globalData.Students.searchStudentsWithin(searchCriteria, students);

    if (students.empty()) {
        cout << "ERROR: " << identifier << " not valid." << endl;
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

void Consult::consultStudentsInClass(const string& classCode) {
    auto searchCriteria = [&classCode](const Class& ucClass) {
        return checkIfClassCodeEqual(ucClass.ClassCode, classCode);
    };
    consultStudentsIn("class " + classCode, searchCriteria);
}

void Consult::consultStudentsInUc(const string& ucCode) {
    auto searchCriteria = [&ucCode](const Class& ucClass) {
        return checkIfUCCodeEqual(ucClass.UcCode, ucCode);
    };
    consultStudentsIn("uc " + ucCode, searchCriteria);
}

void Consult::consultStudentsInYear(const string& year) {
    auto searchCriteria = [&year](const Class& ucClass) {
        return (ucClass.ClassCode[0] == year[0]);
    };
    consultStudentsIn("year " + year, searchCriteria);
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
    cout << "Total of " << result.size() << " students." << endl;

    for (const auto& entry : result) {
        cout << entry.first << ": " << entry.second << " students" << endl;
    }
}

void Consult::consultUcOccupation(const string& ucCode) {
    map<string, int> classStudentsCount;

    globalData.Students.getStudentsCountInClass(ucCode, classStudentsCount);

    if (classStudentsCount.empty()){
        cout << "ERROR: invalid UC Code or no students registered in UC, please Enter a UC from \"L.EIC001\" to \"L.EIC025\"" << endl;
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


void Consult::ListStudentsByName() {
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

void Consult::FindStudentByCode() {
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

/*
int main() {
    System data;
    Global global = {data.get_Classes(),data.get_Schedules(),data.get_Students()};
    Consult consult;
    consult.set_data(global);

    //consult.consultTheScheduleOfClass("1LEIC0");
    //consult.consultTheScheduleOfStudent(20206654);
    //consult.ListStudentsByName();
    consult.FindStudentByCode();
    //consult.consultListOfStudentsInAtLeastNUCs(4);

    //consult.consultStudentsInClass("1LEIC01");
    //consult.consultStudentsInUc("L.EIC001");
    //consult.consultStudentsInYear("3");

    //consult.consultUcOccupation("L.EIC002");


    //consult.consultYearOccupation(3);

    return 0;
}*/