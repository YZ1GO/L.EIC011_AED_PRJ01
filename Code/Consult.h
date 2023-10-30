#include "ReadData.h"

#ifndef PROJETO_AED_CONSULT_H
#define PROJETO_AED_CONSULT_H


class Consult {
public:
    Global globalData;

    Consult();
    void set_data(Global global);

    /*void upToData(Global global);
    void upToData()*/

    //auxiliary funcs

    set<string> ucsOfTheYear(int year);

    // consult schedule of a given student or class
    void printSchedule(vector<Schedule> schedules);
    void consultTheScheduleOfStudent();
    void consultTheScheduleOfStudent(const string& studentName);
    void consultTheScheduleOfClass();

    void ListStudentsByName();
    void FindStudentByCode();

    // consult students registered in at least N Ucs, return list of students
    void consultListOfStudentsInAtLeastNUCs();

    // consult class/uc/year occupation, returns list of students in it
    void consultStudentsIn(const string& identifier, const function<bool(const Class&)> searchCriteria);
    void consultStudentsInClass();
    void consultStudentsInUc();
    void consultStudentsInYear();

    void consultOccupationBySortOrder(const string& identifierType, const string& identifier, const map<string, int>& studentsCount);
    //consult uc occupation, returns classes occupation of the uc
    void consultUcOccupation(const string& ucCode);
    //consult year occupation, return ucs occupation of the year
    void consultYearOccupation(const int& year);


    void occupationInClasses();
    void occupationInUcs();
    void occupationInYears();

};


#endif //PROJETO_AED_CONSULT_H
