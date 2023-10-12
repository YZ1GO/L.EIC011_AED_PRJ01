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

        while(getline(file, line)){
            stringstream ss(line);
            Student student1;
            string studentCode, ucCode, classCode;

            getline(ss, studentCode, ',');
            getline(ss, student1.StudentName, ',');
            getline(ss, ucCode, ',');
            getline(ss, classCode, ',');

            student1.StudentCode = stoi(studentCode); // Converter para inteiro
            student1.UcToClasses[ucCode].push_back(classCode);

            students.push_back(student1);
        }
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
                stringstream ss(line);

                string studentCodeStr;
                getline(ss, studentCodeStr, ',');
                StudentCode = stoi(studentCodeStr); // Converter para inteiro

                getline(ss, StudentName, ',');
                getline(ss, UcCode, ',');
                getline(ss, ClassCode, ',');
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
                stringstream ss(line);

                getline(ss, ClassCode, ',');
                getline(ss, UcCode, ',');
                getline(ss, WeekDay, ',');

                string startHour;
                getline(ss, startHour, ',');
                StartHour = stof(startHour);

                string classesDurationStr;
                getline(ss, classesDurationStr, ',');
                Duration = stof(classesDurationStr);

                getline(ss, Type, ',');
            }
        }

        //checks if is classes_per_uc.csv
        else if (getine(file, line) == "UcCode,ClassCode"){
            string UcCode;
            string ClassCode;

            while(getline(file, line)){
                stringstream ss(line);

                getline(ss, UcCode, ',');
                getline(ss, ClassCode,',');
            }
        }
    }*/
};

#endif //PROJETO_AED_READDATA_H
