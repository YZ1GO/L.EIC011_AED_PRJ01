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

using namespace std;

class ReadData{

public:
    vector<Student> students;
    vector<Class> classes;
    vector<Schedule> schedules;

    ReadData(string studentCsv, string classesCsv, string classesPerUcCsv);

    // function to parse data from students_classes.csv
    void ReadStudents(const string studentCsv);

    // function to parse data from classes.csv
    void ReadSchedules(const string classesCsv);

    // function to parse data from classes_per_uc.csv
    void ReadClasses(const string classesPerUcCsv);
};

#endif //PROJETO_AED_READDATA_H
