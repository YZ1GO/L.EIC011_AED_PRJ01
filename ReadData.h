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
using namespace std;

class ReadData{

public:
    vector<Student> student;
    vector<Classes> classes;
    vector<Classe_per_Uc> classes_per_uc;

    ReadData(string studentCsv, string classesCsv, string classesPerUcCsv){
        ReadStudentCsv(studentCsv);
        ReadClasses(classesCsv);
        ReadClassePerUc(classesPerUcCsv);
    }

    void ReadStudentCsv(const string studentCsv){
        ifstream file(studentCsv);
        string line;
        getline(file, line);

        while(getline(file, line)){
            Student student1;

            stringstream dataStream(line);

            string studentCodeStr;
            getline(dataStream, studentCodeStr, ',');
            student1.StudentCode = stoi(studentCodeStr); // Converter para inteiro

            getline(dataStream, student1.StudentName, ',');
            getline(dataStream, student1.UcCode, ',');
            getline(dataStream, student1.ClassCode, ',');

            student.push_back(student1);
        }
    }

    void ReadClasses(const string classesCsv){
        ifstream file(classesCsv);
        string line;
        getline(file, line);

        while(getline(file, line)){
            Classes classes1;

            stringstream dataStream(line);

            getline(dataStream, classes1.ClassCode, ',');
            getline(dataStream, classes1.UcCode, ',');
            getline(dataStream, classes1.WeekDay, ',');

            string classesStartHourStr;
            getline(dataStream, classesStartHourStr, ',');
            classes1.StartHour = stof(classesStartHourStr);

            string classesDurationStr;
            getline(dataStream, classesDurationStr, ',');
            classes1.Duration = stof(classesDurationStr);

            getline(dataStream, classes1.Type, ',');

            classes.push_back(classes1);
        }
    }

    void ReadClassePerUc(const string classePerUcCsv){
        ifstream file(classePerUcCsv);
        string line;
        getline(file, line);

        while(getline(file, line)){
            Classe_per_Uc classe_per_uc1;

            stringstream dataStream(line);

            getline(dataStream, classe_per_uc1.UcCode, ',');
            getline(dataStream, classe_per_uc1.ClassCode,',');

            classes_per_uc.push_back(classe_per_uc1);
        }
    }




    /*ReadData(const string csvFile){
        ifstream file(csvFile);

        string line;

        //checks if is students.csv
        if (getline(file, line) == "StudentCode,StudentName,UcCode,ClassCode"){ //check the first line
            //variaveis de "Student"
            int StudentCode;
            string StudentName;
            string UcCode;
            string ClassCode;

            while(getline(file, line)){
                stringstream dataStream(line);

                string studentCodeStr;
                getline(dataStream, studentCodeStr, ',');
                StudentCode = stoi(studentCodeStr); // Converter para inteiro

                getline(dataStream, StudentName, ',');
                getline(dataStream, UcCode, ',');
                getline(dataStream, ClassCode, ',');
            }
        }

        //checks if is classes.csv
        else if (getline(file, line) == "ClassCode,UcCode,Weekday,StartHour,Duration,Type"){
            //Classes variables
            string ClassCode;
            string UcCode;
            string WeekDay;
            float StartHour;
            float Duration
            string Type;

            while(getline(file, line)){
                stringstream dataStream(line);

                getline(dataStream, ClassCode, ',');
                getline(dataStream, UcCode, ',');
                getline(dataStream, WeekDay, ',');

                string classesStartHourStr;
                getline(dataStream, classesStartHourStr, ',');
                StartHour = stof(classesStartHourStr);

                string classesDurationStr;
                getline(dataStream, classesDurationStr, ',');
                Duration = stof(classesDurationStr);

                getline(dataStream, Type, ',');
            }
        }

        //checks if is classes_per_uc.csv
        else if (getine(file, line) == "UcCode,ClassCode"){
            string UcCode;
            string ClassCode;

            while(getline(file, line)){
                stringstream dataStream(line);

                getline(dataStream, UcCode, ',');
                getline(dataStream, ClassCode,',');
            }
        }
    }*/
};

#endif //PROJETO_AED_READDATA_H
