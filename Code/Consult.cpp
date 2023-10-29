#include "Consult.h"

using namespace std;

Consult::Consult() {}

void Consult::set_data(Global global) {
    globalData = global;
}

//auxiliary function that prints the information a schedule
void Consult::printSchedule(Schedule schedule) {
    cout << "     " << schedule.UcToClasses.UcCode << ", " << schedule.UcToClasses.ClassCode << "" << endl;
    cout << "   Start Hour: " << floatToHours(schedule.StartHour) << endl;
    cout << "     End Hour: " << floatToHours(schedule.StartHour + schedule.Duration) << endl;
    cout << "     Duration: " << schedule.Duration << " hours" << endl;
    cout << "         Type: " << schedule.Type << endl << endl;
}

void Consult::consultTheScheduleOfStudent(int studentCode) {
    Student* student = globalData.Students.searchByCode(studentCode);

    // Find the student with the given student code
    if (student) {
        cout << "Student Code: " << student->StudentCode << endl;
        cout << "Student Name: " << student->StudentName << endl;

        vector <Schedule> schedules;

        // Iterate through the classes for this student
        for (const Class &studentClass: student->UcToClasses) {
            for (const Schedule &schedule: globalData.Schedules) {
                if (checkIfClassCodeEqual(studentClass.ClassCode, schedule.UcToClasses.ClassCode)
                    && checkIfUCCodeEqual(studentClass.UcCode, schedule.UcToClasses.UcCode)) {
                    schedules.push_back(schedule);
                }
            }
        }

        sort(schedules.begin(), schedules.end());

        string weekDay;
        for (const Schedule &schedule: schedules) {
            if (weekDay == schedule.WeekDay) {
                printSchedule(schedule);
            } else {
                weekDay = schedule.WeekDay;
                cout << "-------------------------------------------------" << endl;
                cout << weekDay << endl;
                cout << "-------------------------------------------------" << endl;
                printSchedule(schedule);
            }
        }
        cout << "-----------------END OF THE LIST-----------------" << endl;
        return;
    }
    cout << "Student with code " << studentCode << " not found." << endl;
}

void Consult::consultTheScheduleOfClass(const string& classCode) {
    vector<Schedule> schedules;
    for (const Schedule& schedule : globalData.Schedules){
        if (checkIfClassCodeEqual(classCode, schedule.UcToClasses.ClassCode)){
            schedules.push_back(schedule);
        }
    }
    sort(schedules.begin(), schedules.end());

    string weekDay;
    for (const Schedule& schedule : schedules){
        if (weekDay == schedule.WeekDay){
            printSchedule(schedule);
        }
        else {
            weekDay = schedule.WeekDay;
            cout << "-------------------------------------------------" << endl;
            cout << weekDay << endl;
            cout << "-------------------------------------------------" << endl;
            printSchedule(schedule);
        }
    }
    cout << "-----------------END OF THE LIST-----------------" << endl;
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
        cout << "Set is empty" << endl;
        return;
    }

    cout << students.size() << " students in " << identifier << endl;
    cout << "\n";

    int orderChoice;
    do {
        std::cout << "1. Ascending order" << std::endl;
        std::cout << "2. Descending order" << std::endl;
        std::cout << "\n";
        std::cout << "Choose the order: ";
        std::cin >> orderChoice;
    } while (orderChoice != 1 && orderChoice != 2);

    int index = 1;

    if (orderChoice == 1) {
        std::cout << " [Ascending order]:" << std::endl;
        std::cout << "\n";
        for (const Student& student : students) {
            std::cout << index << ". " << student.StudentCode << " " << student.StudentName << std::endl;
            index++;
        }
    } else {
        std::cout << " [Descending order]:" << std::endl;
        std::cout << "\n";
        for (std::set<Student>::reverse_iterator rit = students.rbegin(); rit != students.rend(); ++rit) {
            std::cout << index << ". " << rit->StudentCode << " " << rit->StudentName << std::endl;
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
    consultStudentsIn("UC " + ucCode, searchCriteria);
}

void Consult::consultStudentsInYear(const string& year) {
    auto searchCriteria = [&year](const Class& ucClass) {
        return checkIfYearEqual(ucClass.ClassCode, year);
    };
    consultStudentsIn("year " + year, searchCriteria);
}

void Consult::consultOccupationOfUc(const string& ucCode) {
    map<string, int> classStudentCounts;

    globalData.Students.getCountsForYear(ucCode, classStudentCounts);

    if (classStudentCounts.empty()){
        cout << "ERROR: invalid UC Code or no students registered in UC, please Enter a UC from \"L.EIC001\" to \"L.EIC025\"" << endl;
        return;
    }

    vector<pair<string, int>> result(classStudentCounts.begin(), classStudentCounts.end());

    cout << "Choose a sorting option: " << endl;
    cout << "1. By classCode ascending order" << endl;
    cout << "2. By classCode descending order" << endl;
    cout << "3. By classOccupation ascending order" << endl;
    cout << "4. By classOccupation descending order" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            sortByClassCode(result, true);
            cout << "Classes and Student Counts for " << ucCode << " [classCode ascending order]:" << endl;
            break;
        case 2:
            sortByClassCode(result, false);
            cout << "Classes and Student Counts for " << ucCode << " [classCode descending order]:" << endl;
            break;
        case 3:
            sortByClassOccupation(result, true);
            cout << "Classes and Student Counts for " << ucCode << " [students in class ascending order]:" << endl;
            break;
        case 4:
            sortByClassOccupation(result, false);
            cout << "Classes and Student Counts for " << ucCode << " [students in class descending order]:" << endl;
            break;
        default:
            cout << "Invalid choice. Please choose a valid option (1-4)." << endl;
            return;
    }

    for (const auto& entry : result) {
        cout << entry.first << ": " << entry.second << " students" << endl;
    }
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


void Consult::consultOccupationOfYear(int year, bool ascending) {
    if (year < 1 || year > 3) {
        cout << "ERROR: invalid year, please ENTER a year from \"1\" to \"3\" " << endl;
        return;
    }

    set<string> ucsOfTheYear_ = ucsOfTheYear(year);

    // Create a map to store UCs and their corresponding student counts
    map<string, int> ucStudentCounts;

    for (const auto& uc : ucsOfTheYear_) {
        globalData.Students.getCountsForYear(uc, ucStudentCounts);
    }

    // Sort the map by student counts in ascending order
    multimap<int, string> sortedUcs;

    for (const auto& pair : ucStudentCounts) {
        sortedUcs.insert(ascending ? make_pair(pair.second, pair.first) : make_pair(pair.second, pair.first));
    }

    cout << "Number of students registered in year " << year << " [" << (ascending ? "ascending" : "descending") << " order]" << endl;

    for (const auto& entry : sortedUcs) {
        cout << entry.second << ": " << entry.first << endl;
    }
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
    while (true) {
        cout << "Enter the number of the student you want to view: ";
        cin >> choice;

        // Check if user's choice is valid
        if (choice >= 1 && choice <= matchingStudents.size()) {
            system("clear");
            break;
        }

        cout << "Invalid choice. PLease enter a valid number. " << endl << flush;
        cout << "\n";
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
    cout << "Enter the student code of the student you want to search for: ";
    int searchCode;
    cin >> searchCode;

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


int main() {
    System data;
    Global global = {data.get_Classes(),data.get_Schedules(),data.get_Students()};
    Consult consult;
    consult.set_data(global);

    //consult.consultTheScheduleOfStudent(202066542);
    //consult.ListStudentsByName();
    //consult.FindStudentByCode();
    //consult.consultListOfStudentsInAtLeastNUCs(4);

    //consult.consultStudentsInClass("1LEIC01");
    //consult.consultStudentsInUc("L.EIC001");
    //consult.consultStudentsInYear("2");

    consult.consultOccupationOfUc("L.EIC002");


    consult.consultOccupationOfYear(1, true);

    return 0;
}