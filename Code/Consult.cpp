#include "Consult.h"

using namespace std;

Consult::Consult(Global global) {
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

// Gives list of the students in the Class, in either ascending or descending order
void Consult::consultStudentsInClass(const string& classCode) {
    set<Student> studentsOfTheClass;

    globalData.Students.searchStudentsInClass(classCode, studentsOfTheClass);

    if (studentsOfTheClass.empty()) {
        cout << "Set is empty" << endl;
        return;
    }

    cout << studentsOfTheClass.size() << " students in class " << classCode << endl;
    cout << "\n";

    int orderChoice;
    do {
        cout << "1. Ascending order" << endl;
        cout << "2. Descending order" << endl;
        cout << "\n";
        cout << "Choose the order: ";
        cin >> orderChoice;
    } while (orderChoice != 1 && orderChoice != 2);

    if (orderChoice == 1) {
        cout << " [Ascending order]:" << endl;
        cout << "\n";
        for (const Student& student : studentsOfTheClass) {
            cout << student.StudentCode << " " << student.StudentName << endl;
        }
    } else {
        cout << " [Descending order]:" << endl;
        cout << "\n";
        for (set<Student>::reverse_iterator rit = studentsOfTheClass.rbegin(); rit != studentsOfTheClass.rend(); ++rit) {
            cout << rit->StudentCode << " " << rit->StudentName << endl;
        }
    }
}

/*
bool Consult::sortByStudentCount(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second < b.second;
}

//Gives the list of classes Occupation of a UC by ascendingOrder
vector<pair<string, int>> Consult::getClassesAndStudentCountsAscending(const string& ucCode) {
    map<string, int> classStudentCounts = getCountsForUc(ucCode);
    return sortCounts(classStudentCounts, true);
}

vector<pair<string, int>> Consult::getClassesAndStudentCountsDescending(const string& ucCode) {
    map<string, int> classStudentCounts = getCountsForUc(ucCode);
    return sortCounts(classStudentCounts, false);
}

map<string, int> Consult::getCountsForUc(const string& ucCode) {
    map<string, int> classStudentCounts;

    for (const Student& student : globalData.Students) {
        for (const Class& studentClass : student.UcToClasses) {
            if (studentClass.UcCode == ucCode) {
                string trimmedClassCode = studentClass.ClassCode;
                // Trim leading and trailing white spaces
                trimmedClassCode.erase(trimmedClassCode.begin(), find_if(trimmedClassCode.begin(), trimmedClassCode.end(),
                                                                         [](char c) {
                                                                             return !isspace(c);
                                                                         }));
                trimmedClassCode.erase(find_if(trimmedClassCode.rbegin(), trimmedClassCode.rend(),
                                               [](char c) {
                                                   return !isspace(c);
                                               }).base(), trimmedClassCode.end());

                if (!trimmedClassCode.empty()) {
                    classStudentCounts[trimmedClassCode]++;
                }
            }
        }
    }
    return classStudentCounts;
}


vector<pair<string, int>> Consult::sortCounts(const map<string, int>& classStudentCounts, bool ascending) {
    vector<pair<string, int>> result(classStudentCounts.begin(), classStudentCounts.end());

    // Sort based on the order (ascending or descending)
    sort(result.begin(), result.end(),
         [ascending](const pair<string, int>& a, const pair<string, int>& b) {
             return ascending ? (a.second < b.second) : (a.second > b.second);
         });

    return result;
}

void Consult::consultOccupationOfUc_ascendingOrder(const string& ucCode) {
    vector<pair<string, int>> result = getClassesAndStudentCountsAscending(ucCode);
    if (result.empty()){
        cout << "ERROR: invalid UC Code or no students registered in UC, please Enter a UC from \"L.EIC001\" to \"L.EIC025\"" << endl;
        return;
    }
    cout << "Classes and Student Counts for " << ucCode << " [ascending order]:" << endl;

    for (const auto& entry : result) {
        cout << entry.first << ": " << entry.second << " students" << endl;
    }
}

void Consult::consultOccupationOfUc_descendingOrder(const string& ucCode) {
    vector<pair<string, int>> result = getClassesAndStudentCountsDescending(ucCode);
    if (result.empty()){
        cout << "ERROR: invalid UC Code or no students registered in UC, please Enter a UC from \"L.EIC001\" to \"L.EIC025\"" << endl;
        return;
    }
    cout << "Classes and Student Counts for " << ucCode << " [descending order]:" << endl;

    for (const auto& entry : result) {
        cout << entry.first << ": " << entry.second << " students" << endl;
    }
}

/*
set<string> Consult::ucsOfTheYear(int year){
    set<string> ucsOfTheYear;
    string year_ = to_string(year);
    for (auto classObj : globalData.Classes){
        if (classObj.ClassCode[0] == year_[0]){
            ucsOfTheYear.insert(classObj.UcCode);
        }
    }
    return ucsOfTheYear;
}

//CORRECT
//auxiliary function given a ucCode, returns the number of the students in registered in that uc
using namespace std;  // Add this at the beginning of your functions

map<string, int> Consult::AUX_numberOfStudentsInUC(const string& ucCode) {
    map<string, int> ucStudentCounts;

    for (const auto& student : globalData.Students) {
        for (const auto& studentClass : student.UcToClasses) {
            if (checkIfUCCodeEqual(studentClass.UcCode, ucCode)) {
                ucStudentCounts[ucCode]++;
                break;  // No need to continue checking this student for this UC
            }
        }
    }
    return ucStudentCounts;
}

void Consult::consultOccupationOfYear_ascendingOrder(int year) {
    if (year < 1 || year > 3) {
        cout << "ERROR: invalid year, please ENTER a year from \"1\" to \"3\" " << endl;
        return;
    }

    set<string> ucsOfTheYear_ = ucsOfTheYear(year);

    // Create a map to store UCs and their corresponding student counts
    map<string, int> ucStudentCountsMap;

    for (const auto& uc : ucsOfTheYear_) {
        int studentCount = AUX_numberOfStudentsInUC(uc)[uc];
        ucStudentCountsMap[uc] = studentCount;
    }

    // Sort the map by student counts in ascending order
    multimap<int, string> sortedUcs;
    for (const auto& pair : ucStudentCountsMap) {
        sortedUcs.insert({pair.second, pair.first});
    }

    cout << "Number of students registered in year " << year << " [ascending order]" << endl;
    for (const auto& entry : sortedUcs) {
        cout << entry.second << ": " << entry.first << endl;
    }
}

void Consult::consultOccupationOfYear_descendingOrder(int year) {
    if (year < 1 || year > 3) {
        cout << "ERROR: invalid year, please ENTER a year from \"1\" to \"3\" " << endl;
        return;
    }

    set<string> ucsOfTheYear_ = ucsOfTheYear(year);

    // Create a map to store UCs and their corresponding student counts
    map<string, int> ucStudentCountsMap;

    for (const auto& uc : ucsOfTheYear_) {
        int studentCount = AUX_numberOfStudentsInUC(uc)[uc];
        ucStudentCountsMap[uc] = studentCount;
    }

    // Sort the map by student counts in descending order
    multimap<int, string, greater<int>> sortedUcs;
    for (const auto& pair : ucStudentCountsMap) {
        sortedUcs.insert({pair.second, pair.first});
    }

    cout << "Number of students registered in year " << year << " [descending order]" << endl;
    for (const auto& entry : sortedUcs) {
        cout << entry.second << ": " << entry.first << endl;
    }
}*/

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
    Consult consult(global);

    //consult.consultTheScheduleOfStudent(202066542);
    //consult.ListStudentsByName();
    //consult.FindStudentByCode();
    //consult.consultListOfStudentsInAtLeastNUCs(4);
    //consult.consultStudentsInClass("1LEIC01");
    return 0;
}