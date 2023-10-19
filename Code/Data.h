//
// Created by chill on 10-10-2023.
//

#ifndef PROJETO_AED_DATA_H
#define PROJETO_AED_DATA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

class Class {
public:
    string UcCode;
    string ClassCode;

    Class(string ucCode, string classCode);
    Class();
    bool operator==(const Class& other) const;
    void printClass();
};

class Schedule {
public:
    Class UcToClasses;
    string WeekDay;
    float StartHour;
    float Duration;
    string Type;

    Schedule(Class ucToClass, string weekday, float startHour, float duration, string type);
    Schedule();
    void printSchedule();
};

class Student {
public:
    int StudentCode;
    string StudentName;
    vector<Class> UcToClasses;

    Student(int studentCode, string studentName, vector<Class> ucToClass);
    Student();
    void printStudentInformation();

};

#endif //PROJETO_AED_DATA_H
