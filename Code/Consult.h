#include "ReadData.h"

#ifndef PROJETO_AED_CONSULT_H
#define PROJETO_AED_CONSULT_H


class Consult {
public:
    Global globalData;

    Consult();
    Consult(Global global);
    void updateData(Global data);

    /*void upToData(Global global);
    void upToData()*/

    //auxiliary func
    set<string> ucsOfTheYear(int year);


    void listStudentsByName();
    void findStudentByCode();

    // consult schedule of a given student or class
    void printSchedule(vector<Schedule> schedules);
    vector<Schedule> getStudentSchedule(const Student& student);
    void consultTheScheduleOfStudent();
    void consultTheScheduleOfClass();

    // consult students registered in at least N Ucs, return list of students
    void listOfStudentsInAtLeastNUCs();

    // consult class/uc/year occupation, returns list of students in it
    void listOfStudentsInXBySortOrder(const string& identifier, const function<bool(const Class&)> searchCriteria);
    void listOfStudentsInClass();
    void listOfStudentsInUc();
    void listOfStudentsInYear();

    void showSortingMenu(const map<string, int>& studentsCount, const string& identifier);
    void occupationInClasses();
    void occupationInUcs();
    void occupationInYears();

    void consultOccupationBySortOrder(const string& identifierType, const string& identifier, const map<string, int>& studentsCount);
    void consultUcOccupation();
    void consultYearOccupation();

};


#endif //PROJETO_AED_CONSULT_H
