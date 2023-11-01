#ifndef PROJETO_AED_CHANGE_H
#define PROJETO_AED_CHANGE_H

#include "ReadData.h"
#include "Consult.h"

class Change {
public:
    Global global;
    Change(Global& globalCopy);
    bool checkIfClassCapacityExceeds(map<string, int> classStudentsCount, const string& newClassCode);
    bool checkIfBalanceBetweenClassesDisturbed(map<string, int> classStudentsCount, const string& oldClassCode, const string& newClassCode);
    bool tryBuildNewSchedule(const Student& student);
    void changeClass();
    bool checkIfCanJoinNewUC(const Student& student);
    map<string, int> classesWithVacancyInNewUC(const Student& student, const string& newUcCode);
    void changeUC();

    void leaveUCAndClass();
    void joinUCAndClass();
};

#endif //PROJETO_AED_CHANGE_H
