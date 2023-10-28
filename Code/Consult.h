#include "ReadData.h"

#ifndef PROJETO_AED_CONSULT_H
#define PROJETO_AED_CONSULT_H


class Consult {
public:
    Global globalData;

    Consult(Global global);

    //auxiliary funcs
/*
    map<string, int> AUX_numberOfStudentsInUC(const string& ucCode);
    set<string> ucsOfTheYear(int year);
*/


    // consult schedule of a given student or class
    void printSchedule(Schedule schedule);
    void consultTheScheduleOfStudent(int studentCode);
    void consultTheScheduleOfClass(const string& classCode);

    // consult students registered in at least N Ucs, return list of students
    void consultListOfStudentsInAtLeastNUCs(const int n);

    // consult class/uc/year occupation, returns list of students in it
    void consultStudentsInClass(const string& classCode);
    void consultStudentsInUc(const string& ucCode);
    void consultStudentsInYear(const string& year);

    //consult uc occupation, returns classes occupation of the uc
    void consultOccupationOfUc(const string& ucCode);

    //consult year occupation, return ucs occupation of the year
    void consultOccupationOfYear(int year, bool ascending);

    void ListStudentsByName();
    void FindStudentByCode();
};


#endif //PROJETO_AED_CONSULT_H
