//
// Created by chill on 10-10-2023.
//

#ifndef PROJETO_AED_READDATA_H
#define PROJETO_AED_READDATA_H

#include "Data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include "UtilityFunctions.h"

using namespace std;

struct Global {
    vector<Class> Classes;
    vector<Schedule> Schedules;
    StudentBST Students;
};

class ReadData{

public:
    Global global;
    ReadData();

    vector<Class> ReadClasses(string classesPerUcCsv); // function to parse data from classes_per_uc.csv
    vector<Schedule> ReadSchedules(string classesCsv); // function to parse data from classes.csv
    StudentBST ReadStudents(string studentCsv); // function to parse data from students_classes.csv
};

class System {
private:
    vector<Class> Classes;
    vector<Schedule> Schedules;
    StudentBST Students;
    stack<Global> undoStack;

public:
    System();
    System(Global data);

    vector<Class> get_Classes();
    vector<Schedule> get_Schedules();
    StudentBST get_Students();

    void saveCurrentState();
    void undoAction();

};


#endif //PROJETO_AED_READDATA_H
