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

    Class(string ucCode, string classCode)
            : UcCode(ucCode), ClassCode(classCode) {}

    Class(){}

    void printClass(){
        cout << UcCode << " , "<< ClassCode << endl;
    }
};


class Student {
public:
    int StudentCode;
    string StudentName;
    vector<Class> UcToClasses;

    Student(int studentCode, string studentName, vector<Class> ucToClass) : StudentCode(studentCode), StudentName(studentName), UcToClasses(ucToClass){};

    Student(){}

    void printStundetInformation(){
        cout << "  INFORMAÇÕES RELATIVAS AO ESTUDANTE  " << endl;
        cout << "Número mecanografico: " << StudentCode << endl;
        cout << "Nome do Estudante: " << StudentName << endl;
        cout << "Código da UC e código da respetiva turma: ";
        for (Class ucToClass : UcToClasses){
            ucToClass.printClass();
        }
    }
};

class Schedule {
public:
    Class UcToClasses;
    string WeekDay;
    float StartHour;
    float Duration;
    string Type;

    Schedule(Class ucToClass, string weekday, float startHour, float duration, string type)
            : UcToClasses(ucToClass), WeekDay(weekday), StartHour(startHour), Duration(duration), Type(type){}

    Schedule(){}
};



#endif //PROJETO_AED_DATA_H
