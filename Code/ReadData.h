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

struct Global {
    std::vector<Class> Classes;
    std::vector<Schedule> Schedules;
    StudentBST Students;
};

class ReadData{

public:
    Global global;
    ReadData();

    std::vector<Class> ReadClasses(std::string classesPerUcCsv); // function to parse data from classes_per_uc.csv
    std::vector<Schedule> ReadSchedules(std::string classesCsv); // function to parse data from classes.csv
    StudentBST ReadStudents(std::string studentCsv); // function to parse data from students_classes.csv
};

class System {
private:
    std::vector<Class> Classes;
    std::vector<Schedule> Schedules;
    StudentBST Students;
    std::stack<Global> undoStack;

public:
    System();
    System(Global data);

    std::vector<Class> get_Classes();
    std::vector<Schedule> get_Schedules();
    StudentBST get_Students();

    void saveCurrentState();
    void undoAction();

};


#endif //PROJETO_AED_READDATA_H
