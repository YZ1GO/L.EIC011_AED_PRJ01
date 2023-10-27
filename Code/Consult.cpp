#include "Consult.h"

Consult::Consult(Global global) {
    globalData = global;
}

//auxiliary function converts float to hours
string Consult::floatToHours(float hours) {
    int wholeHours = static_cast<int>(hours);
    int minutes = static_cast<int>((hours - wholeHours) * 60);

    stringstream ss;
    ss << setw(2) << setfill('0') << wholeHours << ":" << setw(2) << setfill('0') << minutes;

    return ss.str();
}

bool Consult::checkIfClassCodeEqual(string a, string b){
    return a[0]==b[0] && a[5]==b[5] && a[6]==b[6];
}

bool Consult::checkIfUCCodeEqual(string a, string b){
    return a[5]==b[5] && a[6]==b[6] && a[7]==b[7];
}

//auxiliary function that prints the information a schedule
void Consult::printSchedule(Schedule schedule) {
    cout << "     " << schedule.UcToClasses.UcCode << ", " << schedule.UcToClasses.ClassCode << "" << endl;
    cout << "   Start Hour: " << floatToHours(schedule.StartHour) << endl;
    cout << "     End Hour: " << floatToHours(schedule.StartHour + schedule.Duration) << endl;
    cout << "     Duration: " << schedule.Duration << " hours" << endl;
    cout << "         Type: " << schedule.Type << endl << endl;
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

/*Student Consult::consultStudentGivenStudentNumber(const int studentCode){
    for (const Student& student : globalData.Students){
        if (student.StudentCode == studentCode){
            return student;
        }
    }
    return Student();
}

int Consult::AUX_numberOfUcsRegistered(const int studentCode) {
    Student student = consultStudentGivenStudentNumber(studentCode);
    return student.UcToClasses.size();
}

//Gives the number and a List of students registered in at least N UCs
void Consult::consultListOfStudentsInAtLeastNucs(const int n) {
    int result = 0;
    set<Student> studentsSet;
    for (auto student : globalData.Students){
        if (student.UcToClasses.size() >= static_cast<vector<Class>::size_type>(n)){
            result++;
            studentsSet.insert(student);
        }
    }
    cout << "Number of students registered in at least " << n
         << " UCs: " << result << endl;

    int i = 1;
    for (const Student& student : studentsSet) {
        cout << i++ << ". [" << AUX_numberOfUcsRegistered(student.StudentCode)
             << "] "<< student.StudentCode << " "
             << student.StudentName << endl;
    }
}

//Auxiliary function given a classCode, return set of Students in that Class
set<Student> Consult::AUX_listOfStudentsInClass(const string& classCode) {
    set<Student> studentsOfTheClass;

    for (const Student& student : globalData.Students) {
        for (auto classObj : student.UcToClasses) {
            // Issue with the comparison
            if (checkIfClassCodeEqual(classObj.ClassCode, classCode)) {
                studentsOfTheClass.insert(student);
                break;
            }
        }
    }
    return studentsOfTheClass;
}

//Gives list of the students in the Class, in ascending order
void Consult::consultStudentsInClass_ascendingOrder(const string& classCode) {
    set<Student> studentsOfTheClass = AUX_listOfStudentsInClass(classCode);

    if (studentsOfTheClass.empty()) {
        cout << "Set is empty" << endl;
    }

    cout << "Students in class " << classCode << " [ascending order]:" << endl;
    for (const Student& student : studentsOfTheClass) {
        cout << student.StudentCode << " " << student.StudentName << endl;
    }
}

//GIves list of the students in the Class, in descending order
void Consult::consultStudentsInClass_descendingOrder(const string& classCode) {
    set<Student> studentsOfTheClass = AUX_listOfStudentsInClass(classCode);

    if (studentsOfTheClass.empty()) {
        cout << "Set is empty" << endl;
    }

    cout << "Students in class " << classCode << " [ascending order]:" << endl;
    for (set<Student>::reverse_iterator rit = studentsOfTheClass.rbegin(); rit != studentsOfTheClass.rend(); ++rit) {
        cout << rit->StudentCode << " " << rit->StudentName << endl;
    }
}

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

//
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

int main() {
    ReadData data;
    Consult consult(data.global);
    consult.consultTheScheduleOfStudent(202071557);
    return 0;
}