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
#include <algorithm>

using namespace std;

class Class {
public:
    string UcCode;
    string ClassCode;

    Class(string ucCode, string classCode);
    Class();
    bool operator==(const Class& other) const;
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
    bool operator<(const Schedule& other) const;
};

class Student {
public:
    int StudentCode;
    string StudentName;
    vector<Class> UcToClasses;

    Student(int studentCode, string studentName, vector<Class> ucToClass);
    Student();

};

class Global {
public:
    vector<Class> Classes;
    vector<Schedule> Schedules;
    vector<Student> Students;

    Global(vector<Class> classes, vector<Schedule> schedules, vector<Student> students);
    Global(vector<Class> classes);
    Global(vector<Schedule> schedules);
    Global(vector<Student> students);
    Global();
};

#endif //PROJETO_AED_DATA_H
