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
    Global global;

    ReadData();

    vector<Class> ReadClasses(string classesPerUcCsv); // function to parse data from classes_per_uc.csv
    vector<Schedule> ReadSchedules(string classesCsv); // function to parse data from classes.csv
    StudentBST ReadStudents(string studentCsv); // function to parse data from students_classes.csv
};

#endif //PROJETO_AED_READDATA_H
