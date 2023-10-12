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

class Student {
public:
    int StudentCode;
    string StudentName;
    unordered_map<string, string> UcToClasses;

    Student(int studentCode, string studentName, string ucCode, string classCode) : StudentCode(studentCode), StudentName(studentName){
        UcToClasses[ucCode] = classCode;
    };

    Student(){}
};

class Schedule {
public:
    string ClassCode;
    string UcCode;
    string WeekDay;
    float StartHour;
    float Duration;
    string Type;

    Schedule(string classCode, string ucCode, string weekday, float startHour, float duration, string type)
            : ClassCode(classCode), UcCode(ucCode), WeekDay(weekday), StartHour(startHour), Duration(duration), Type(type){}

    Schedule(){}
};

class Class {
public:
    string UcCode;
    string ClassCode;

    Class(string ucCode, string classCode)
            : UcCode(ucCode), ClassCode(classCode) {}

    Class(){}
};


#endif //PROJETO_AED_DATA_H
