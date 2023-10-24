#include "Functions_Ricardo.h"
#include <iostream>
using namespace std;

Functions_Ricardo::Functions_Ricardo(ReadData readData) {
    data = readData;
}

void Functions_Ricardo::printSchedule(Schedule schedule) {
    cout << schedule.UcToClasses.UcCode << ", " << schedule.UcToClasses.ClassCode << "" << endl;
    cout << "      WeekDay: " << schedule.WeekDay << endl;
    cout << "   Start Hour: " << schedule.StartHour << endl;
    cout << "     Duration: " << schedule.Duration << " hours" << endl;
    cout << "         Type: " << schedule.Type << endl;
    cout << "-------------------------------------------------" << endl;
}

void Functions_Ricardo::consultTheScheduleOfClass(string classCode) {
    for (const Schedule& schedule : data.schedules){
        if (classCode == schedule.UcToClasses.ClassCode){
            printSchedule(schedule);
        }
    }
}

void Functions_Ricardo::consultTheScheduleOfStudent(int studentCode) {
    Student studentToConsult;
    for (const Student& student : data.students){
        if (student.StudentCode == studentCode){
            studentToConsult = student;
            break;
        }
    }

    for (const Class& studentUcClass : studentToConsult.UcToClasses){
        cout << studentUcClass.UcCode << ", " << studentUcClass.ClassCode << endl;

        string classCode = studentUcClass.ClassCode;
        consultTheScheduleOfClass(classCode);
    }
}





