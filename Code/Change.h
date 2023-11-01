#ifndef PROJETO_AED_CHANGE_H
#define PROJETO_AED_CHANGE_H

#include "ReadData.h"

class Change {
public:
    Global global;
    Change();
    bool checkIfClassCapacityExceeds(const Global& globalCopy, map<string, int> classStudentsCount, const string& newClassCode);
    bool checkIfBalanceBetweenClassesDisturbed(map<string, int> classStudentsCount, const string& oldClassCode, const string& newClassCode);
    bool tryBuildNewSchedule(const Global& globalCopy, const Student& student);
    void getStudentSchedule(const Global& globalCopy, const Student& student, vector<Schedule>& studentSchedule);
    void changeClass(Global& globalCopy);
    bool checkIfCanJoinNewUC(const Student& student);
    map<string, int> classesWithVacancyInNewUC(Global& globalCopy, const Student& student, const string& newUcCode);
    void changeUC(Global& globalCopy);

    void leaveUCAndClass(Global& globalCopy);
    void joinUCAndClass(Global& globalCopy);
};

#endif //PROJETO_AED_CHANGE_H
