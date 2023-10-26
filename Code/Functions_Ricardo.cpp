#include "Functions_Ricardo.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <typeinfo>
#include <set>
#include <unordered_set>

using namespace std;

Functions_Ricardo::Functions_Ricardo(ReadData readData) {
    data = readData;
}

//auxiliary function converts float to hours
string Functions_Ricardo::floatToHours(float hours) {
    int wholeHours = static_cast<int>(hours);
    int minutes = static_cast<int>((hours - wholeHours) * 60);

    stringstream ss;
    ss << setw(2) << setfill('0') << wholeHours << ":" << setw(2) << setfill('0') << minutes;

    return ss.str();
}

bool Functions_Ricardo::checkIfClassCodeEqual(string a, string b){
    if (a.length()!=b.length()) return false;
    for (auto i = 0; i < a.length(); i++){
        if (a[i]!=b[i]) return false;
    }
    return true;
    return a[0] == b[0] ;
}

bool Functions_Ricardo::checkIfUCCodeEqual(string a, string b){
    if (a.length()!=b.length()) return false;
    for (auto i = 0; i < a.length(); i++){
        if (a[i]!=b[i]) return false;
    }
    return true;
    //return a[a.length()-3,3] == b[b.length()-3,3];
}

//auxiliary function that prints the information a schedule
void Functions_Ricardo::printSchedule(Schedule schedule) {
    cout << "     " << schedule.UcToClasses.UcCode << ", " << schedule.UcToClasses.ClassCode << "" << endl;
    cout << "   Start Hour: " << floatToHours(schedule.StartHour) << endl;
    cout << "     End Hour: " << floatToHours(schedule.StartHour + schedule.Duration) << endl;
    cout << "     Duration: " << schedule.Duration << " hours" << endl;
    cout << "         Type: " << schedule.Type << endl << endl;
}

void Functions_Ricardo::consultTheScheduleOfClass(const string& classCode) {
    vector<Schedule> schedules;
    for (const Schedule& schedule : data.schedules){
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

void Functions_Ricardo::consultTheScheduleOfStudent(int studentCode) {
    vector<Schedule> schedules;

    // Find the student with the given student code
    for (const Student& student : data.students) {
        if (student.StudentCode == studentCode) {
            cout << "Student Code: " << student.StudentCode << endl;
            cout << "Student Name: " << student.StudentName << endl;

            // Iterate through the classes for this student
            for (const Class& studentClass : student.UcToClasses) {
                for (const Schedule& schedule : data.schedules){
                    if (checkIfClassCodeEqual(studentClass.ClassCode, schedule.UcToClasses.ClassCode)
                    && checkIfUCCodeEqual(studentClass.UcCode, schedule.UcToClasses.UcCode)){
                        schedules.push_back(schedule);
                    }
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
            return;
        }
    }
    cout << "Student with code " << studentCode << " not found." << endl;
}

Student Functions_Ricardo::consultStudentGivenStudentNumber(const int studentCode){
    for (const Student& student : data.students){
        if (student.StudentCode == studentCode){
            return student;
        }
    }
    return Student();
}

int Functions_Ricardo::AUX_numberOfUcsRegistered(const int studentCode) {
    Student student = consultStudentGivenStudentNumber(studentCode);
    int result = 0;
    for (const Class& classOfStudent : student.UcToClasses){
        result++;
    }
    return result;
}

//Gives the number and a List of students registered in at least N UCs
void Functions_Ricardo::consultListOfStudentsInAtLeastNucs(const int n) {
    int result = 0;
    set<Student> studentsSet;
    for (auto student : data.students){
        if (student.UcToClasses.size() >= n){
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
set<Student> Functions_Ricardo::AUX_listOfStudentsInClass(const string& classCode) {
    set<Student> studentsOfTheClass;

    for (const Student& student : data.students) {
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
void Functions_Ricardo::consultStudentsInClass_ascendingOrder(const string& classCode) {
    set<Student> studentsOfTheClass = AUX_listOfStudentsInClass(classCode);

    if (studentsOfTheClass.empty()) {
        cout << "Set is empty" << endl;
    }

    cout << "Students in class" << classCode << " [ascending order]:" << endl;
    for (const Student& student : studentsOfTheClass) {
        cout << student.StudentCode << " " << student.StudentName << endl;
    }
}

//GIves list of the students in the Class, in descending order
void Functions_Ricardo::consultStudentsInClass_descendingOrder(const string& classCode) {
    set<Student> studentsOfTheClass = AUX_listOfStudentsInClass(classCode);

    if (studentsOfTheClass.empty()) {
        cout << "Set is empty" << endl;
    }

    cout << "Students in class" << classCode << " [ascending order]:" << endl;
    for (set<Student>::reverse_iterator rit = studentsOfTheClass.rbegin(); rit != studentsOfTheClass.rend(); ++rit) {
        cout << rit->StudentCode << " " << rit->StudentName << endl;
    }
}

bool Functions_Ricardo::sortByStudentCount(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second < b.second;
}

//Gives the list of classes Occupation of a UC by ascendingOrder
vector<pair<string, int>> Functions_Ricardo::getClassesAndStudentCountsAscending(const string& ucCode) {
    map<string, int> classStudentCounts = getCountsForUc(ucCode);
    return sortCounts(classStudentCounts, true);
}

vector<pair<string, int>> Functions_Ricardo::getClassesAndStudentCountsDescending(const string& ucCode) {
    map<string, int> classStudentCounts = getCountsForUc(ucCode);
    return sortCounts(classStudentCounts, false);
}

map<string, int> Functions_Ricardo::getCountsForUc(const string& ucCode) {
    map<string, int> classStudentCounts;

    for (const Student& student : data.students) {
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

vector<pair<string, int>> Functions_Ricardo::sortCounts(const map<string, int>& classStudentCounts, bool ascending) {
    vector<pair<string, int>> result(classStudentCounts.begin(), classStudentCounts.end());

    // Sort based on the order (ascending or descending)
    sort(result.begin(), result.end(),
         [ascending](const pair<string, int>& a, const pair<string, int>& b) {
             return ascending ? (a.second < b.second) : (a.second > b.second);
         });

    return result;
}

void Functions_Ricardo::consultOccupationOfUc_ascendingOrder(const string& ucCode) {
    vector<pair<string, int>> result = getClassesAndStudentCountsAscending(ucCode);
    cout << "Classes and Student Counts for " << ucCode << " [ascending order]:" << endl;

    for (const auto& entry : result) {
        cout << entry.first << ": " << entry.second << " students" << endl;
    }
}

void Functions_Ricardo::consultOccupationOfUc_descendingOrder(const string& ucCode) {
    vector<pair<string, int>> result = getClassesAndStudentCountsDescending(ucCode);
    cout << "Classes and Student Counts for " << ucCode << " [descending order]:" << endl;

    for (const auto& entry : result) {
        cout << entry.first << ": " << entry.second << " students" << endl;
    }
}


set<string> Functions_Ricardo::ucsOfTheYear(int year){
    set<string> ucsOfTheYear;
    string year_ = to_string(year);
    for (auto classObj : data.classes){
        if (classObj.ClassCode[0] == year_[0]){
            ucsOfTheYear.insert(classObj.UcCode);
        }
    }
    return ucsOfTheYear;
}

//CORRECT
//auxiliary function given a ucCode, returns the number of the students in registered in that uc
int Functions_Ricardo::AUX_numberOfStudentsInUC(const string& ucCode){
    int result = 0;
    for (auto student : data.students){
        for (auto studentClass : student.UcToClasses){
            if (checkIfUCCodeEqual(studentClass.UcCode, ucCode)){
                result++;
                break;
            }
        }
    }
    return result;
}

void Functions_Ricardo::consultOccupationOfYear_ascendingOrder(int year) {
    if (year < 1 || year > 3){
        cout << "ERROR: invalid year, please ENTER a year from \"1\" to \"3\" "<< endl;
        return;
    }

    set<string> ucsOfTheYear_ = ucsOfTheYear(year);

    cout << "Number of students registered in year " << year << " [ascending order]" << endl;
    for (auto ucs : ucsOfTheYear_){
        cout << ucs << ": " << AUX_numberOfStudentsInUC(ucs) << endl;
    }
}

void Functions_Ricardo::consultOccupationOfYear_descendingOrder(int year) {
    if (year < 1 || year > 3){
        cout << "ERROR: invalid year, please ENTER a year from \"1\" to \"3\" "<< endl;
        return;
    }

    set<string> ucsOfTheYear_ = ucsOfTheYear(year);

    cout << "Number of students registered in year " << year << " [descending order]" <<endl;
    for (auto rit = ucsOfTheYear_.rbegin(); rit != ucsOfTheYear_.rend(); ++rit){
        cout << *rit << ": " << AUX_numberOfStudentsInUC(*rit) << endl;
    }
}