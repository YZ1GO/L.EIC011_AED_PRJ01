#include "Functions_Ricardo.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <typeinfo>

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
    return a[0] == b[0] && a[5] == b[5] && a[6] == b[6];
}

bool Functions_Ricardo::checkIfUCCodeEqual(string a, string b){
    return a[6] == b[6] && a[7] == b[7] && a[8] == b[8];
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

void Functions_Ricardo::consultTheScheduleOfClass(string ucCode, string classCode) {
    vector<Schedule> schedules;
    for (const Schedule& schedule : data.schedules){
        //cout << typeid(schedule.UcToClasses.ClassCode).name() << endl;
        if (classCode == schedule.UcToClasses.ClassCode) {
            cout << "yes" << endl;
            schedules.push_back(schedule);
        }
    }
    sort(schedules.begin(), schedules.end());

    for (const Schedule& schedule : schedules){
        printSchedule(schedule);
    }
}

void Functions_Ricardo::consultTheScheduleOfStudent(int studentCode) {
    // Find the student with the given student code
    for (const Student& student : data.students) {
        if (student.StudentCode == studentCode) {
            cout << "Student Code: " << student.StudentCode << endl;
            cout << "Student Name: " << student.StudentName << endl;

            // Iterate through the classes for this student
            for (const Class& studentClass : student.UcToClasses) {
                //consultTheScheduleOfClass(studentClass);
                cout << studentClass.UcCode << ", " << studentClass.ClassCode << endl;
                //cout << typeid(studentClass.UcCode).name() << ", " << typeid(studentClass.ClassCode).name() << endl;
                consultTheScheduleOfClass(studentClass.ClassCode);
                //consultTheScheduleOfClass(studentClass);
            }
            return;  // Stop searching after finding the student
        }
    }
    cout << "Student with code " << studentCode << " not found." << endl;
}

//Gives the number of students registered in at least N UCs
void Functions_Ricardo::consultNumberOfStudentsInAtLeastNucs(const int n) {
    int result = 0;
    for (auto student : data.students){
        if (student.UcToClasses.size() >= n){
            result++;
        }
    }
    cout << "Number of students registered in at least " << n
    << " UCs: " << result << endl;
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

//Auxiliary Function that given a Class, return the number of students in that Class
int Functions_Ricardo::AUX_numberOfStudentsInClass(const Class& classObj) {
    int result = 0;
    for (const Student& student : data.students){
        for (const Class& Studentclass : student.UcToClasses){
            if (classObj == Studentclass){
                result++;
                break;
            }
        }
    }
    return result;
}

//Auxiliary function that given a ucCode, returns a map<classCode, numberStudentsInThatClass>
map<string, int> Functions_Ricardo::AUX_numberOfStudentsInEachClass(const string &ucCode) {
    //the number of students in each class of the Uc
    map<string, int> occupation_each_class_of_uc;

    for (const Class& classObj : data.classes){
        if (checkIfUCCodeEqual(classObj.UcCode, ucCode)){
            occupation_each_class_of_uc[classObj.ClassCode] = AUX_numberOfStudentsInClass(classObj);
        }
    }

    return occupation_each_class_of_uc;
}

//DO NOT PRINT THE CLASS CODE
//Gives the list of classes Occupation of a UC by ascendingOrder
void Functions_Ricardo::consultOccupationOfUc_ascendingOrder(const string& ucCode) {
    map<string, int> occupation_each_class_of_uc = AUX_numberOfStudentsInEachClass(ucCode);

    if (occupation_each_class_of_uc.empty()){
        cout << "UC CODE not valid" << endl;
        return;
    }

    vector<pair<string, int>> occupationVector(occupation_each_class_of_uc.begin(), occupation_each_class_of_uc.end());

    // Sort the vector in ascending order based on student count
    sort(occupationVector.begin(), occupationVector.end(),
              [](const auto& a, const auto& b) {
                  return a.second < b.second;
              });

    // Print the sorted occupation in ascending order
    cout << "Number of Students registered in " << ucCode << " [ascending order]" << endl;
    for (const auto& entry : occupationVector) {
        cout << "Class Code: " << entry.first << ", Student Count: " << entry.second << endl;
    }
}

//DO NOT PRINT THE CLASS CODE
//Gives the list of classes Occupation of a UC by ascendingOrder
void Functions_Ricardo::consultOccupationOfUc_descendingOrder(const string& ucCode) {
    map<string, int> occupation_each_class_of_uc = AUX_numberOfStudentsInEachClass(ucCode);

    if (occupation_each_class_of_uc.empty()){
        cout << "UC CODE not valid" << endl;
        return;
    }

    vector<pair<string, int>> occupationVector(occupation_each_class_of_uc.begin(), occupation_each_class_of_uc.end());

    // Sort the vector in descending order based on student count
    sort(occupationVector.begin(), occupationVector.end(),
         [](const auto& a, const auto& b) {
             return a.second > b.second; // Compare in descending order
         });

    // Print the sorted occupation in descending order
    cout << "Number of Students registered in " << ucCode << " [descending order]" << endl;
    for (const auto& entry : occupationVector) {
        cout << "Class Code: " << entry.first << ", Student Count: " << entry.second << endl;
    }
}

