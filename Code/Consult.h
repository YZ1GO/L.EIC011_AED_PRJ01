#include "ReadData.h"
#include <iostream>
#include <set>
#include <unordered_set>
#include <map>

#ifndef PROJETO_AED_CONSULT_H
#define PROJETO_AED_CONSULT_H


class Consult {
public:
    Global globalData;

    Consult(Global global);
    /*void upToData(Global global);
    void upToData()*/

    //auxiliary funcs
    //done
    int AUX_numberOfUcsRegistered(const int studentCode);
    set<Student> AUX_listOfStudentsInClass(const string& classCode);
/*
    map<string, int> AUX_numberOfStudentsInUC(const string& ucCode);
    set<string> ucsOfTheYear(int year);
    vector<pair<string,int>> getClassesAndStudentCountsAscending(const string& ucCode);
    vector<pair<string,int>> getClassesAndStudentCountsDescending(const string& ucCode);
    map<string, int> getCountsForUc(const string& ucCode);
    vector<pair<string, int>> sortCounts(const map<string, int>& classStudentCounts, bool ascending);
    static bool sortByStudentCount(const pair<string, int>& a, const pair<string, int>& b);
*/
    // consult schedule of a given student or class
    void printSchedule(Schedule schedule);
    void consultTheScheduleOfStudent(int studentCode);
    void consultTheScheduleOfClass(const string& classCode);

    // consult students registered in at least N Ucs, return list of students
    void consultListOfStudentsInAtLeastNucs(const int n);

    //consult class occupation, returns list of students in class
    void consultStudentsInClass_ascendingOrder(const string& classCode);
    void consultStudentsInClass_descendingOrder(const string& classCode);
/*
    //consult uc occupation, returns classes occupation of the uc
    void consultOccupationOfUc_ascendingOrder(const string& ucCode);
    void consultOccupationOfUc_descendingOrder(const string& ucCode);

    //consult year occupation, return ucs occupation of the year
    void consultOccupationOfYear_ascendingOrder(int year);
    void consultOccupationOfYear_descendingOrder(int year); */

    void ListStudentsByName();
    void ListStudentByCode();
};


#endif //PROJETO_AED_CONSULT_H
