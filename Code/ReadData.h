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

    ReadData(string studentCsv, string classesCsv, string classesPerUcCsv){
        ReadStudents(studentCsv);
        ReadSchedules(classesCsv);
        ReadClasses(classesPerUcCsv);
    }

    // function to parse data from students_classes.csv
    void ReadStudents(const string studentCsv){
        ifstream file(studentCsv);
        string line;
        getline(file, line);

        unordered_map<int, Student> studentMap;

        while(getline(file, line)){
            stringstream ss(line);
            string studentCodeStr, ucCode, classCode;

            getline(ss, studentCodeStr, ',');
            int studentCode = stoi(studentCodeStr); // Converter para inteiro

            // Check if this student already exists in the map
            if (studentMap.find(studentCode) == studentMap.end()) {
                // If not found, create a new entry
                Student student1;
                getline(ss, student1.StudentName, ',');
                getline(ss, ucCode, ',');
                getline(ss, classCode, ',');
                student1.UcToClasses[ucCode] = classCode;
                studentMap[studentCode] = student1;
            } else {
                // If found, update the existing entry
                getline(ss, ucCode, ',');
                getline(ss, classCode, ',');
                studentMap[studentCode].UcToClasses[ucCode] = classCode;
            }
        }
        for (const auto& student : studentMap)
            students.push_back(student.second);
    }

    // function to parse data from classes.csv
    void ReadSchedules(const string classesCsv){
        ifstream file(classesCsv);
        string line;
        getline(file, line);

        while(getline(file, line)){
            stringstream ss(line);
            Schedule schedule1;
            string startHour, duration;

            getline(ss, schedule1.ClassCode, ',');
            getline(ss, schedule1.UcCode, ',');
            getline(ss, schedule1.WeekDay, ',');
            getline(ss, startHour, ',');
            getline(ss, duration, ',');
            getline(ss, schedule1.Type, ',');

            schedule1.StartHour = stof(startHour);
            schedule1.Duration = stof(duration);

            schedules.push_back(schedule1);
        }
    }

    // function to parse data from classes_per_uc.csv
    void ReadClasses(const string classesPerUcCsv){
        ifstream file(classesPerUcCsv);
        string line;
        getline(file, line);

        while(getline(file, line)){
            stringstream ss(line);
            Class class1;

            getline(ss, class1.UcCode, ',');
            getline(ss, class1.ClassCode,',');

            classes.push_back(class1);
        }
    }
};

#endif //PROJETO_AED_READDATA_H
