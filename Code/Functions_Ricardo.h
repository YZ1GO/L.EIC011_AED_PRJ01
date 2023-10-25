#include "ReadData.h"

#ifndef PROJETO_AED_FUNCTIONS_RICARDO_H
#define PROJETO_AED_FUNCTIONS_RICARDO_H


class Functions_Ricardo {
public:
    ReadData data;
    Functions_Ricardo(ReadData readData);

    string floatToHours(float hours);
    void printSchedule(Schedule schedule);
    void consultTheScheduleOfStudent(int studentCode);
    void consultTheScheduleOfClass(string classCode);


    void consultTheScheduleOfClass(string ucCode, string classCode);

};


#endif //PROJETO_AED_FUNCTIONS_RICARDO_H
