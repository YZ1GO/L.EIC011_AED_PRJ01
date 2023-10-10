//
// Created by chill on 10-10-2023.
//

#ifndef PROJETO_AED_DATA_H
#define PROJETO_AED_DATA_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {

public:
    int StudentCode;
    string StudentName;
    string UcCode;
    string ClassCode;

    Student(int code, string name, string ucCode, string classCode)
            : StudentCode(code), StudentName(name), UcCode(ucCode), ClassCode(classCode){};

    Student(){

    }
    /*void setStudentCode(int code){
        StudentCode = code;
    }

    void setStudentName(string name){
        StudentName = name;
    }

    void setUcCode(string ucCode){
        UcCode = ucCode;
    }

    void setClassCode(string classCode){
        ClassCode = classCode;
    }*/

};

class Classes {
public:
    string ClassCode;
    string UcCode;
    string WeekDay;
    float StartHour;
    float Duration;
    string Type;

    Classes(string code, string ucCode, string weekday, float start, float duration, string type)
            : ClassCode(code), UcCode(ucCode), WeekDay(weekday), StartHour(start), Duration(duration), Type(type){}

    Classes(){

    }
};

class Classe_per_Uc {
public:
    string UcCode;
    string ClassCode;

    Classe_per_Uc(string ucCode, string code)
            : UcCode(ucCode), ClassCode(code) {}

    Classe_per_Uc(){

    }
};


#endif //PROJETO_AED_DATA_H
