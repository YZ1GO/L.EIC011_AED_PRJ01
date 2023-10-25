#include "ReadData.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

#ifndef PROJETO_AED_FUNCTIONS_RICARDO_H
#define PROJETO_AED_FUNCTIONS_RICARDO_H


class Functions_Ricardo {
public:
    ReadData data;
    Functions_Ricardo(ReadData readData);

    string floatToHours(float hours);
    void printSchedule(Schedule schedule);
    void consultTheScheduleOfStudent(int studentCode);
    void consultTheScheduleOfClass(const string& classCode);

    bool checkIfClassCodeEqual(string a, string b);
    bool checkIfUCCodeEqual(string a, string b);
    void consultTheScheduleOfClass(const Class& classObj);

    void consultTheScheduleOfClass(string ucCode, string classCode);

    void consultNumberOfStudentsInAtLeastNucs(const int n);

    set<Student> AUX_listOfStudentsInClass(const string& classCode);
    void consultStudentsInClass_ascendingOrder(const string& classCode);
    void consultStudentsInClass_descendingOrder(const string& classCode);

    int AUX_numberOfStudentsInClass(const Class& classObj);
    map<string, int> AUX_numberOfStudentsInEachClass(const string& ucCode);
    void consultOccupationOfClass(const string& classCode);
    void consultOccupationOfUc_ascendingOrder(const string& ucCode);
    void consultOccupationOfUc_descendingOrder(const string& ucCode);

};


#endif //PROJETO_AED_FUNCTIONS_RICARDO_H
